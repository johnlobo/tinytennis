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
#include "spriteList/spriteList.h"

TBall ball;
TPlayer player1;
TPlayer player2;
EGamePhases phase;
u8 pauseGame;


//
// Body touch
//
void bodyTouch(TBall *ball){
    ball->vx = ball->vx * (FRICTION / 4);
    ball->vy = -ball->vy * (FRICTION / 4);
    ball->vz = ball->vz * (FRICTION / 4);
    calcBounce(ball);
}

//
// Player Shot
//
void shot(TBall *ball, TPlayer *player){
    ball->vx = 0;
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

void checkPlayerCollision(TBall *ball, TPlayer *player, TKeys *keys){
    u8 bx, by, px, py;
    u8 hit;

    px = player->e.x[0] / SCALE;
    py = player->e.y[0] / SCALE;
    bx = ball->e.x[0] / SCALE;
    by = ball->e.y[0] / SCALE;

    //hit = fast_collision(px, py, player->e.w, player->e.h, bx, by, ball->e.w, ball->e.h);
    hit = collision(px, py, player->e.w, player->e.h, bx, by, ball->e.w, ball->e.h);

    if (hit){
        
        
        while (1){
            if (cpct_isKeyPressed(keys->pause)){
                waitKeyUp(keys->pause);
                break;
            }
        }
        
        
        drawText("HIT", 0,0,0);
        player->e.draw = 1;
        if (player->hit > 0){
            shot(ball, player);
        } else {
            bodyTouch(ball);
        }
    }else{
        cpct_drawSolidBox(SCR_VMEM, #0, 12, 5);
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

//void printPlayer(TPlayer *player){
//    u8 *pvmem;
//    if (player->e.draw)
//        {
//            erasePlayer(player);
//            drawPlayer(player);
//            entityDrawUpdate(&(player->e));
//            pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], 40, 0);
//            cpct_drawSolidBox(pvmem, #0, 23, 48);
//            drawNumber((i16) (player->e.x[0] / SCALE), 6, 40, 0);
//            drawNumber((i16) (player->e.y[0] / SCALE), 6, 40, 8);
//            drawNumber((i16) (player->e.z[0] / SCALE), 6, 40, 16);
//            //drawNumber((i16) player->vx, 6, 40, 24);
//            //drawNumber((i16) player->vy, 6, 40, 32);
//            //drawNumber((i16) player->vz, 6, 40, 40);
//        }   
//}

void printBall(TBall *ball){
    u8 *pvmem;
    if (ball->e.draw)
        {
            eraseBall(ball);
            drawBall(ball);
            entityDrawUpdate(&(ball->e));
            pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], 60, 0);
            cpct_drawSolidBox(pvmem, #0, 23, 48);
            drawNumber((i16) (ball->e.x[0] / SCALE), 6, 60, 0);
            drawNumber((i16) (ball->e.y[0] / SCALE), 6, 60, 8);
            drawNumber((i16) (ball->e.z[0] / SCALE), 6, 60, 16);
            drawNumber((i16) ball->vx, 6, 60, 24);
            drawNumber((i16) ball->vy, 6, 60, 32);
            drawNumber((i16) ball->vz, 6, 60, 40);
        
        }   
}

// Game Loop
void game(TMatch *match, TKeys *keys)
{
    TPlayer *playerAux;
    //u32 c;

    initGame();

    // Loop forever
    while (1)
    {
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
        if (ball.active){
         
            updateBall(&ball);

            // Check collision with players 
            if (ball.e.z[0] < (24 * SCALE)){
                if ((ball.vy>0) && (player1.side == SD_down)){
                    playerAux = &player1;
                } else{
                    playerAux = &player2;
                }
                checkPlayerCollision(&ball, playerAux, keys);
            }
        }

        // Draw actors
        
        cpct_waitVSYNC();

        // Updates dusts if any
        updateDusts();
        
        printSprites();

        //printBall();

        //if (ball.e.z[0] > (24 * SCALE)){
        //    printBall(&ball);
        //    printPlayer(&player1);
        //} else {
        //    printPlayer(&player1);
        //    printBall(&ball);
        //}
//
    }
}