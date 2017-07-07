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


void game()
{
    //u32 c;
    u8 *pvmem;

    //c = 0;
    // Loop forever
    while (1)
    {
        //c++;
        if (DEBUG)
        {
            delay(15);
        }
        // Player1 block
        executeState(&player, &ball, &keys);
        if (player.moved)
        {
            selectSpritePlayer(&player);
            erasePlayer(&player);
            drawPlayer(&player);
            player.px = player.x;
            player.py = player.y;
            player.moved = 0;
            if (DEBUG)
            {
                pvmem = cpct_getScreenPtr((u8 *) CPCT_VMEM_START, 0, 0);
                cpct_drawSolidBox(pvmem, #0, 12, 24);
                drawNumber((u16) (player.x / SCALE), 4, 0, 0);
                drawNumber((u16) (player.y / SCALE), 4, 0, 12);
            }
        }

        if (com.moved)
        {
            selectSpritePlayer(&com);
            erasePlayer(&com);
            drawPlayer(&com);
            com.px = com.x;
            com.py = com.y;
            com.moved = 0;
            pvmem = cpct_getScreenPtr((u8 *) CPCT_VMEM_START, 0, 0);
        }

        //Ball block
        if (ball.active)
        {
            updateBall(&ball);
            eraseBall(&ball);
            drawBall(&ball);
            if (DEBUG)
            {
                pvmem = cpct_getScreenPtr((u8 *) CPCT_VMEM_START, 67, 0);
                cpct_drawSolidBox(pvmem, #0, 12, 60);
                drawNumber((i32) (ball.vx), 4, 67, 0);
                drawNumber((i32) (ball.vy / SCALE), 4, 67, 12);
                drawNumber((i32) (ball.vz / SCALE), 4, 67, 24);
                drawNumber((u8) ball.bouncex, 4, 67, 36);
                drawNumber((u8) ball.bouncey, 4, 67, 48);
            }
        }
    }
}

//Begin of recycled area
CPCT_ABSOLUTE_LOCATION_AREA(0x8000);

// Data created with Img2CPC - (c) Retroworks - 2007-2015
// Palette uses hardware values.
const u8 sp_palette[16] = { 0x54, 0x44, 0x4e, 0x53, 0x4c, 0x55, 0x4d, 0x56, 0x5e, 0x5f, 0x5d, 0x52, 0x5c, 0x4a, 0x57, 0x4b };

const TKeys tempKeys =
{
    Key_CursorUp,   Key_CursorDown, Key_CursorLeft
    ,   Key_CursorRight, Key_Space,      Key_Del
    ,   Key_Esc,        Key_M
}

// Main init
void init()
{
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(CPCT_VMEM_START, 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLUE);

    //keys.up    = Key_CursorUp;
    //keys.down  = Key_CursorDown;
    //keys.left  = Key_CursorLeft;
    //keys.right = Key_CursorRight;
    //keys.fire  = Key_Space;
    //keys.pause = Key_Del;
    //keys.abort = Key_Esc;
    //keys.music = Key_M;

    //Inicializar teclas
    cpct_memcpy((void *) &keys, &tempKeys, sizeof(TKeys));

    initPlayer(&player);
    initCom(&com);
    initBall(&ball);
}

void main(void)
{
    cpct_disableFirmware();
    cpct_setInterruptHandler( myInterruptHandler );
    cpct_setStackLocation(NEW_STACK_LOCATION);
    init();
    game();
}

//End of Absolut area
CPCT_RELOCATABLE_AREA();
