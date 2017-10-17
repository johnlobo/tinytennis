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
#include "sprites/ball.h"
#include "sprites/player1.h"
#include "sprites/palette.h"
#include "util/util.h"
#include "util/video.h"
#include "keyboard/keyboard.h"
#include "entities/TBall.h"
#include "entities/TPlayer.h"
#include "text/text.h"
#include "sprites/court01.h"
#include "levels/court01.h"
#include "ai/ai.h"
#include "entities/TDust.h"
#include "menu/menu.h"
#include "entities/TMatch.h"
#include "entities/TScoreboard.h"
#include "spriteList/spriteList.h"

//const i16 trajetoriesX[10] = {-128, -96, -64, -32, 0 , 0, 32, 64, 96, 128};

TBall ball;
TPlayer player1;
TPlayer player2;
TPlayer *playerAux;
EGamePhases phase;
u8 pauseGame;


//
// Body touch
//
void bodyTouch(TBall *ball){
    ball->vx = ball->vx * (FRICTION / 6);
    ball->vy = -ball->vy * (FRICTION / 6);
    ball->vz = ball->vz * (FRICTION / 6);
    calcBounce(ball);
    
    //pvideo = cpct_getScreenPtr(SCR_VMEM, 22, 76);
    //cpct_drawSolidBox(pvideo, #0, 22, 10);
    //drawText("   HIT   ", 24,80,0);
    //delay(340);
    //cpct_etm_drawTileBox2x4 (11, 19, 21, 3, MAP_WIDTH, g_scrbuffers[0], court);
}

//
// Player Shot
//
void shot(TBall *ball, TPlayer *player){
    ball->vx = trajetoriesX[(player->hitDir/2) + 5];
    ball->vz = 3 * SCALE;
    if (player->look == M_up){
        ball->vy = -3 * SCALE;
    } else {
        ball->vy = 3 * SCALE;
    }
    calcBounce(ball);
}

//
//  checkPlayerCollision
//

void checkPlayerCollision(TBall *ball, TPlayer *player){
    u8 bx, by, px, py;
    u8 hit;
    u8 *pvideo; 


    px = player->e.x[0] / SCALE;
    py = player->e.y[0] / SCALE;
    bx = ball->e.x[0] / SCALE;
    by = ball->e.y[0] / SCALE;

    //hit = fast_collision(px, py, player->e.w, player->e.h, bx, by, ball->e.w, ball->e.h);
    hit = collision(px-1, py-1, player->e.w+1, player->e.h+1, bx, by, ball->e.w, ball->e.h);

    if (hit){
        player->e.draw = 1;
        if (player->hit > 0){
            pvideo = cpct_getScreenPtr(SCR_VMEM, 22, 76);
            cpct_drawSolidBox(pvideo, #0, 22, 10);
            drawText("   SHOT   ", 24,80,0); 
            shot(ball, player);
        } else {
            pvideo = cpct_getScreenPtr(SCR_VMEM, 22, 76);
            cpct_drawSolidBox(pvideo, #0, 22, 10);
            drawText("BODY TOUCH", 24,80,0); 
            bodyTouch(ball);
        }
    } else {
        cpct_etm_drawTileBox2x4 (11, 19, 21, 3, MAP_WIDTH, g_scrbuffers[0], court); 
    }
}

void entityDrawUpdate(TEntity *e)
{
    e->x[1] = e->x[0];
    e->y[1] = e->y[0];
    e->z[1] = e->z[0];
    e->draw = 0;
}

// Main init
void initGame()
{
    cpct_etm_setTileset2x4(tile_tileset);
    initPlayer1(&player1);
    initAIPlayer(&player2);
    initBall(&ball);
    initDustList();
    initSpriteList();
    addSprite(&player1.e);

    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, g_scrbuffers[0], court);

    pauseGame = 0;
}


// Game Loop
void game(TMatch *match, TKeys *keys)
{

    u32 c;

    initGame();
    
    //fadeIn(&sp_palette[0]);

    c = 0;

    // Loop forever
    while (1)
    {
        c++;
        //Abort Game
        if (cpct_isKeyPressed(keys->abort)){
            break;
        }
        // Pause Game
        if (cpct_isKeyPressed(keys->pause)){
            pauseGame = 1;
            waitKeyUp(keys->pause);
        }
        while (pauseGame){
            if (cpct_isKeyPressed(keys->pause)){
                pauseGame = 0;
                waitKeyUp(keys->pause);
            }
        }
        
        // Players block
        executeState(&player1, &player2, &ball, keys);
        //executeStateAI(&player2, &ball);
        selectSpritePlayer(&player1, 0);
        //selectSpritePlayer(&player2, 1);

        // Ball block
        if ((ball.active) && (c%2 == 0)){

            updateBall(&ball);

            // Check collision with players 
            if (ball.e.z[0] < (24 * SCALE))
            {
                if (ball.e.y[0] > (100 * SCALE))
                {
                    if (player1.side == SD_down)
                    {
                        playerAux = &player1;
                        //checkPlayerCollision(&ball, &player1);

                    } else
                    {
                        //checkPlayerCollision(&ball, &player2);
                        //playerAux = &player2;
                    } 
                }else 
                {
                    if (player1.side == SD_up)
                    {
                        //checkPlayerCollision(&ball, &player1);
                        playerAux = &player1;
                    } else
                    {
                        //checkPlayerCollision(&ball, &player2);
                        //playerAux = &player2;
                    }
                }
                checkPlayerCollision(&ball, playerAux);
                //checkPlayerCollision(&ball, &player1);
            }
        }

        updateDusts();

        // Draw actors
        cpct_waitVSYNC();

        orderSpriteList();        
        printSprites();
        //printScoreBoard(0,0, match);
        
    }
}