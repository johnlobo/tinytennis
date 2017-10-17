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

#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <cpctelera.h>

#define DEBUG 0

#define SCALE 256L
#define FRICTION 0.8
#define GRAVITY -48 // in an interval of -256 to 0

// Pointers to the hardware backbuffer, placed in bank 1
// of the memory (0x8000-0xBFFF)
#define SCR_VMEM  (u8*)0xC000
#define SCR_BUFF  (u8*)0x8000

// Program Stack locations
#define NEW_STACK_LOCATION (void*)0xC000

#define YES 1
#define NO 0

#define WIDTH  79
#define HEIGHT  199

#define MAP_WIDTH  40
#define MAP_HEIGHT  50

#define PLAYER_WIDTH   SP_PLAYER1_00_W
#define PLAYER_HEIGHT   SP_PLAYER1_00_H

#define VERTICAL_STEP 2

//Sprites Size
#define FONT_H 5
#define FONT_W 2

#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) (X > Y ? X : Y)

#define HIT_RANGE 512

// Declare am_tablatrans, which is defined in game.c, and used in more places
cpctm_declareMaskTable(g_tablatrans);

// Looking to
typedef enum { M_right, M_left, M_up, M_down } ELook;
// Player States
typedef enum { ST_stopped, ST_walking, ST_hitting, ST_hitting_back, ST_preparing, ST_serving, ST_AIstopped, ST_AImovingToTarget, ST_AIhitting } EStates;

// Game phases
typedef enum { GM_serve, GM_rest, GM_play } EGamePhases;
//Sides
typedef enum { SD_up, SD_down } ESides;

typedef struct
{
    ELook look;
    u8 *sprite;
} TFrame;

typedef struct
{
    u8 id;
    u16 x[2], y[2], z[2];
    u8 w, h;
    TFrame *frame;
    u8 draw;
} TEntity;

extern const i16 trajetoriesX[11];

#endif