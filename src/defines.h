#ifndef _DEFINES_H_
#define _DEFINES_H_

#define SCALE 256U
#define FRICTION 0.8
#define GRAVITY -0.4 * SCALE

// Pointers to the hardware backbuffer, placed in bank 1
// of the memory (0x8000-0xBFFF)
#define SCR_BUFF  (u8*)0x8000

// Program Stack locations
#define NEW_STACK_LOCATION (void*)0x1000

#define YES 1
#define NO 0

#define WIDTH  80
#define HEIGHT  200

#define PLAYER_WIDTH   SP_PLAYER1_00_W
#define PLAYER_HEIGHT   SP_PLAYER1_00_H

#define VERTICAL_STEP 2

//Sprites Size
#define FONT_H 11
#define FONT_W 3

// Declare am_tablatrans, which is defined in game.c, and used in more places
cpctm_declareMaskTable(g_tablatrans);

// Game phases
typedef enum{ GM_serve, GM_rest, GM_play } EGamePhases
//Sides
typedef enum{ SD_up, SD_down } ESides

#endif