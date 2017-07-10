//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
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

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

TKeys keys;
TBall ball;
TPlayer player, com;
EGamePhases phase;

void myInterruptHandler()
{
    static u8 i; // Static variable to be preserved from call to call

    // Set the color of the border differently for each interrupt
    //cpct_setBorder(i+1);

    // Count one more interrupt. There are 6 interrupts in total (0-5)
    //if (++i > 5) i=0;
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

void entityDrawUpdate(TEntity *e){
    u32* x = e->x + 2;
    u32* y = e->y + 2;
    u32* z = e->z + 2;
    *x = *(x-1); --x; *x = *(x-1);
    *y = *(y-1); --x; *y = *(y-1);
    *z = *(z-1); --x; *z = *(z-1);
    --e->draw;
}

// Main init
void initGame()
{
    u8 *pvmem;

    cpct_etm_setTileset2x4(tile_tileset);
    initPlayer(&player);
    initCom(&com);
    initBall(&ball);

    pvmem = cpct_getScreenPtr(g_scrbuffers[0], 0, 0);
    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, pvmem, court);
    pvmem = cpct_getScreenPtr(g_scrbuffers[1], 0, 0);
    cpct_etm_drawTilemap2x4_f(MAP_WIDTH, MAP_HEIGHT, pvmem, court);
}


void game()
{
    //u32 c;
    u8 *pvmem;

    initGame();

    //c = 0;
    // Loop forever
    while (1)
    {
        //c++;
#ifdef DEBUG
        delay(15);
#endif
        // Player1 block
        executeState(&player, &ball, &keys);
        if (player.e.draw)
        {
            erasePlayer(&player);
            selectSpritePlayer(&player);
            drawPlayer(&player);
            entityDrawUpdate(&player.e);
#ifdef DEBUG
            pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[1], 0, 0);
            cpct_drawSolidBox(pvmem, #0, 12, 24);
            drawNumber((u16) (player.e.x[0] / SCALE), 4, 0, 0);
            drawNumber((u16) (player.e.y[0] / SCALE), 4, 0, 12);
#endif
        }

        if (com.e.draw)
        {
            erasePlayer(&com);
            selectSpritePlayer(&com);
            drawPlayer(&com);
            entityDrawUpdate(&com.e);
        }

        //Ball block
        if (ball.active && ball.e.draw)
        {
            updateBall(&ball);
            eraseBall(&ball);
            drawBall(&ball);
            entityDrawUpdate(&ball.e);
#ifdef DEBUG
            pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[1], 67, 0);
            cpct_drawSolidBox(pvmem, #0, 12, 60);
            drawNumber((i32) (ball.vx), 4, 67, 0);
            drawNumber((i32) (ball.vy / SCALE), 4, 67, 12);
            drawNumber((i32) (ball.vz / SCALE), 4, 67, 24);
            drawNumber((u8) ball.bouncex, 4, 67, 36);
            drawNumber((u8) ball.bouncey, 4, 67, 48);
#endif
        }

        cpct_waitVSYNC();
        swapBuffers(g_scrbuffers);
    }
}

//Begin of recycled area
CPCT_ABSOLUTE_LOCATION_AREA(0x8000);

// Data created with Img2CPC - (c) Retroworks - 2007-2015
// Palette uses hardware values.
const u8 sp_palette[16] = { 0x54, 0x44, 0x4e, 0x53, 0x4c, 0x55, 0x4d, 0x56, 0x5e, 0x5f, 0x5d, 0x52, 0x5c, 0x4a, 0x57, 0x4b };

const TKeys tempKeys = {    Key_CursorUp, Key_CursorDown, Key_CursorLeft, Key_CursorRight,
                            Key_Space, Key_Enter, Key_Del, Key_Esc, Key_M };

void initMain()
{
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(g_scrbuffers[0], 0x00, 0x4000);
    cpct_memset(g_scrbuffers[1], 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLUE);

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

//End of Absolut area
CPCT_RELOCATABLE_AREA();
