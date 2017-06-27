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


// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

const i16 trajetoriesX[10] = {0, -64, 64, 0, -128, 128, -172, 172, -240, 240};

TKeys keys;
TBall ball;
TPlayer player;

void myInterruptHandler() {
    static u8 i; // Static variable to be preserved from call to call

    // Set the color of the border differently for each interrupt
    //cpct_setBorder(i+1);

    // Count one more interrupt. There are 6 interrupts in total (0-5)
    //if (++i > 5) i=0;
    i++;
    switch (i) {
    case 4:
        cpct_scanKeyboard_if();
        break;
    case 6:
        i = 0;
    }
}


void init() {
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(CPCT_VMEM_START, 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLUE);

    keys.up    = Key_CursorUp;
    keys.down  = Key_CursorDown;
    keys.left  = Key_CursorLeft;
    keys.right = Key_CursorRight;
    keys.fire  = Key_Space;
    keys.pause = Key_Del;
    keys.abort = Key_Esc;
    keys.music = Key_M;

    initPlayer(&player);
    initBall(&ball);
}

void game() {
    u32 c;

    init();

    c = 0;
    // Loop forever
    while (1) {
        c++;
        delay(5);
        // Player1 block
        executeState(&player, &ball, &keys);
        if (player.moved) {
            selectSpritePlayer(&player);
            erasePlayer(&player);
            drawPlayer(&player);
            player.px = player.x;
            player.py = player.y;
            player.moved = 0;
        }
        //Ball block
        if (ball.active) {
            updateBall(&ball);
            eraseBall(&ball);
            drawBall(&ball);
        }
    }
}

void main(void) {
    cpct_disableFirmware();
    cpct_setInterruptHandler( myInterruptHandler );
    cpct_setStackLocation(NEW_STACK_LOCATION);
    game();
}
