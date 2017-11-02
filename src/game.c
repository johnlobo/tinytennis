//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------


#include <cpctelera.h>
#include "defines.h"
#include "menu/menu.h"
#include "ai/ai.h"
#include "entities/TDust.h"
#include "entities/TBall.h"
#include "entities/TPlayer.h"
#include "entities/TMatch.h"
#include "entities/TScoreboard.h"
#include "entities/TBallMachine.h"
#include "spriteList/spriteList.h"
#include "util/util.h"
#include "util/video.h"
#include "keyboard/keyboard.h"
#include "text/text.h"
#include "sprites/ball.h"
#include "sprites/player1.h"
#include "sprites/palette.h"
#include "sprites/court01.h"
#include "levels/court01.h"

TBall ball;
TPlayer player1;
TPlayer player2;
TPlayer *playerAux;
EGamePhases phase;

//
// Body touch
//
void bodyTouch(TBall *ball) {
    ball->vx = ball->vx * (FRICTION / 6);
    ball->vy = -ball->vy * (FRICTION / 6);
    ball->vz = ball->vz * (FRICTION / 6);
    calcBounce(ball);
}

//
// Player Shot
//
void shot(TBall *ball, TPlayer *player) {
    if (ball->live){
        ball->nBounces = 0;
    }
    ball->vx = trajetoriesX[(player->hitDirH / 2) + 5];
    ball->vz = 3 * SCALE;
    if (player->look == M_up) {
        ball->vy = -3 * SCALE;
    } else {
        ball->vy = 3 * SCALE;
    }
    calcBounce(ball);
    if (player->e.id == 1){
        ball->turn = 2;
        setAITarget(ball->bouncex - (player->e.w / 2), ball->bouncey - player->e.h, &player2);
    } else {
        ball->turn = 1;
    }
}

//
//  checkPlayerCollision
//

void checkPlayerCollision(TBall *ball, TPlayer *player) {
    u8 hit;
    //hit = fast_collision(px, py, player->e.w, player->e.h, bx, by, ball->e.w, ball->e.h);
    hit = entityCollision(&player->e, &ball->e);
    if (hit) {
        player->e.draw = 1;
        if ((player->e.id == ball->turn) && (player->hit > 0)) {
            shot(ball, player);
        } else {
            bodyTouch(ball);
        }
    } else {
        //cpct_etm_drawTileBox2x4 (11, 19, 21, 3, MAP_WIDTH, g_scrbuffers[0], court);
    }
}

//
// Init Practice
//

void initPractice()
{
    cpct_etm_setTileset2x4(tile_tileset);
    initPlayer1(&player1);
    initAIPlayer(&player2);
    initBallMachine();
    initBall(&ball);
    initDustList();
    initSpriteList();
    addSprite(&player1.e);
    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, g_scrbuffers[0], court);
    createBallMachine(36,6);
}

//
// Practice Loop
//

void practice(TKeys *keys)
{
    u8 pauseGame = 0;
    u8 abortGame = 0;
    
    initPractice();
    
     while (1)
    {
        //Abort Game
        if (cpct_isKeyPressed(keys->abort)) {
            break;
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause)) {
            pauseGame = 1;
            waitKeyUp(keys->pause);
        }
        while (pauseGame) {
            if (cpct_isKeyPressed(keys->pause)) {
                pauseGame = 0;
                waitKeyUp(keys->pause);
            }
        }
        // Players block
        executeState(&player1, &player2, &ball, keys);
        selectSpritePlayer(&player1, 0);
        // Ball block
        //if ((ball.active) && (c % 2 == 0)) {
        updateBallMachine(&ball);
        if (ball.active) {
            updateBall(&ball);
            // Check collision with players
            if (ball.e.rz < (24 * SCALE))
            {
                checkPlayerCollision(&ball, &player1);
            }
        }
        updateDusts();

        //orderSpriteList();
        // Draw actors
        cpct_waitVSYNC();
        printSprites();
    }
}


//
// Init Point
//

void initPoint()
{
    initPlayer1(&player1);
    initAIPlayer(&player2);
    initBall(&ball);
    initDustList();
    initSpriteList();
    addSprite(&player1.e);
    addSprite(&player2.e);
    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, g_scrbuffers[0], court);
}

//
// playPoint
//

u8 playPoint(TKeys *keys)
{
    u32 c = 0;
    u8 pointLive = 1;
    u8 winner = 0;
    u8 pauseGame = 0;
    u8 abortGame = 0;
    //u8 *pvideo;

    initPoint();

    // Loop forever
    while ((pointLive == 1)  && (abortGame == 0))
    {
        c++;
        //Abort Game
        if (cpct_isKeyPressed(keys->abort)) {
            abortGame = 1;
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause)) {
            pauseGame = 1;
            waitKeyUp(keys->pause);
        }
        while (pauseGame) {
            if (cpct_isKeyPressed(keys->pause)) {
                pauseGame = 0;
                waitKeyUp(keys->pause);
            }
        }
        // Players block
        executeState(&player1, &player2, &ball, keys);
        executeStateAI(&player2, &ball);
        selectSpritePlayer(&player1, 0);
        selectSpritePlayer(&player2, 1);
        // Ball block
        //if ((ball.active) && (c % 2 == 0)) {
        if (ball.active) {
            updateBall(&ball);
            // Check collision with players
            if (ball.e.rz < (24 * SCALE))
            {
                if (ball.e.y[0] > 100)
                {
                    if (player1.side == SD_down)
                    {
                        playerAux = &player1;
                    } else
                    {
                        playerAux = &player2;
                    }
                } else
                {
                    if (player1.side == SD_up)
                    {
                        playerAux = &player1;
                    } else
                    {
                        playerAux = &player2;
                    }
                }
                checkPlayerCollision(&ball, playerAux);
            }
        }
        updateDusts();
        //orderSpriteList();
        // Draw actors
        //cpct_waitVSYNC();
        
        //print_sprites();
        
        printSprites();
        
        if ((ball.winner!=0) && (ball.active == 0)){
            pointLive = 0;
        }
    }
    
    if (abortGame){
        return 3;
    } else {
        return ball.winner;
    }
}

//
// Init Game
//

void initGame()
{
    cpct_etm_setTileset2x4(tile_tileset);
    initPoint();
}

//
// Game
//

void game(TMatch *match, TKeys *keys)
{
    u8 pointResult;
    initGame();
    
    printScoreBoard(20,80,match);
    wait4UserKeypress();
    
    while (match->finished == 0){
        pointResult = playPoint(keys);
        if (pointResult < 3){
            addPoint(pointResult - 1, match);
            printScoreBoard(20,80,match);
            wait4UserKeypress();
        }else{
            break;
        }
    }
    
    if (match->finished){
        drawText("MATCH FINISHED", 0,40,1);
        drawText((u8*) &match->playersName[match->winner], 0,60,1);
    }
}