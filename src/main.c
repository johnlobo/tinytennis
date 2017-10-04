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
#include "entities/TBall.h"
#include "entities/TPlayer.h"
#include "text/text.h"
#include "sprites/court01.h"
#include "levels/court01.h"
#include "util/video.h"
#include "ai/ai.h"
#include "entities/TDust.h"

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

const u8 sp_palette[16] = { 0x54, 0x44, 0x4e, 0x53, 0x4c, 0x55, 0x4d, 0x56, 0x5e, 0x5f, 0x5d, 0x52, 0x5c, 0x4a, 0x57, 0x4b };

const TKeys tempKeys = {    Key_CursorUp, Key_CursorDown, Key_CursorLeft, Key_CursorRight,
                            Key_Space, Key_Return, Key_Esc, Key_H, Key_M
                       };

TKeys keys;
TBall ball;
TPlayer player1;
TPlayer player2;
EGamePhases phase;
u8 pauseGame;


void myInterruptHandler()
{
    static u8 i; // Static variable to be preserved from call to call

    i++;
    switch (i)
    {
    case 4:
        cpct_scanKeyboard_if();
        break;
    case 6:
        i = 0;
    }
}


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
    if (player->e.look == M_up){
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

    px = player->e.x[0] / SCALE;
    py = player->e.y[0] / SCALE;
    bx = ball->e.x[0] / SCALE;
    by = ball->e.y[0] / SCALE;

    hit = fast_collision(px, py, player->e.w, player->e.h, bx, by, ball->e.w, ball->e.h);

    if (hit){
        if (player->hit > 0){
            shot(ball, player);
        } else {
            bodyTouch(ball);
        }
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

    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, g_scrbuffers[0], court);

    pauseGame = 0;
}

void printPlayer(TPlayer *player){
    if (player->e.draw)
        {
            erasePlayer(player);
            drawPlayer(player);
            entityDrawUpdate(&(player->e));
            //    pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], 67, 0);
            //    cpct_drawSolidBox(pvmem, #0, 12, 60);
            //    drawNumber((u32) (player2.e.x[0] / SCALE), 4, 67, 0);
            //    drawNumber((u32) (player2.e.y[0] / SCALE), 4, 67, 12);
            //    drawNumber((u8) (player2.targetX), 4, 67, 24);
            //    drawNumber((u8) (player2.targetY), 4, 67, 36);
            //    drawNumber((i16) (player2.stepX), 4, 67, 48);
            //    drawNumber((i16) (player2.stepY), 4, 67, 60);
        }   
}

void printBall(TBall *ball){
    if (ball->e.draw)
        {
            eraseBall(ball);
            drawBall(ball);
            entityDrawUpdate(&(ball->e));
           //pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[1], 67, 0);
           //cpct_drawSolidBox(pvmem, #0, 12, 60);
           //drawNumber((i16) (ball.e.x[0] / SCALE), 4, 67, 0);
           //drawNumber((i16) (ball.e.y[0] / SCALE), 4, 67, 12);
           //drawNumber((i16) (ball.e.z[0] / SCALE), 4, 67, 24);
           //drawNumber((i16) (ball.vy / SCALE), 4, 67, 36);
        }   
}

// Game Loop
void game()
{
    u8 *pvmem;
    TPlayer *playerAux;
    //u32 c;

    drawText("TINY TENNIS IS READY", 0, 82, 1);
    drawText("PRESS ANY KEY", 0, 97, 1);

    cpct_srand8(wait4UserKeypress())

    initGame();

    // Loop forever
    while (1)
    {
        if (cpct_isKeyPressed(keys.pause)){
                pauseGame = 1;
            }
        while (pauseGame){
            if (cpct_isKeyPressed(keys.pause)){
                pauseGame = 0;
            }
        }
        // Player1 block
        executeState(&player1, &player2, &ball, &keys);
        //executeStateAI(&player2, &ball);
        selectSpritePlayer(&player1, 0);
        //selectSpritePlayer(&player2, 1);

        updateBall(&ball);

        // Check collision with players 
        if ((ball.active) && (ball.e.z[0] < (22 * SCALE))){
            if ((ball.vy>0) && (player1.side == SD_down)){
                playerAux = &player1;
            } else{
                playerAux = &player2;
            }
            checkPlayerCollision(&ball, playerAux);
        }

        // Draw actors
        
        cpct_waitVSYNC();

        // Updates dusts if any
        updateDusts();
        
        if (ball.e.y[0] < player1.e.y[0]){
            printBall(&ball);
            printPlayer(&player1);
        } else {
            printPlayer(&player1);
            printBall(&ball);
        }

    }
}


void initMain()
{
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(g_scrbuffers[0], 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLACK);

    //Inicializar teclas
    cpct_memcpy((void *) &keys, &tempKeys, sizeof(TKeys));
}

void main(void)
{
    cpct_setStackLocation(NEW_STACK_LOCATION);
    cpct_disableFirmware();
    cpct_setInterruptHandler( myInterruptHandler );
    initMain();
    game();
}
