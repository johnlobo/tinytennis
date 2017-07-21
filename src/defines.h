#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <cpctelera.h>

#define DEBUG 0

#define SCALE 256
#define FRICTION 0.8
#define GRAVITY (-0.4 * SCALE)

// Pointers to the hardware backbuffer, placed in bank 1
// of the memory (0x8000-0xBFFF)
#define SCR_VMEM  (u8*)0xC000
#define SCR_BUFF  (u8*)0x8000

// Program Stack locations
#define NEW_STACK_LOCATION (void*)0x8000

#define YES 1
#define NO 0

#define WIDTH  80
#define HEIGHT  200

#define MAP_WIDTH  40
#define MAP_HEIGHT  50

#define PLAYER_WIDTH   SP_PLAYER1_00_W
#define PLAYER_HEIGHT   SP_PLAYER1_00_H

#define VERTICAL_STEP 2

//Sprites Size
#define FONT_H 11
#define FONT_W 3

// Declare am_tablatrans, which is defined in game.c, and used in more places
cpctm_declareMaskTable(g_tablatrans);

// Looking to
typedef enum { M_right, M_left, M_up, M_down } ELook;
// Player States
typedef enum { ST_stopped, ST_walking, ST_hitting, ST_preparing, ST_serving } EStates;

// Game phases
typedef enum{ GM_serve, GM_rest, GM_play } EGamePhases;
//Sides
typedef enum{ SD_up, SD_down } ESides;

typedef struct {
    u8 look;
    u8* sprite;
} TFrame;

typedef struct{
	u16 x[2], y[2], z[2]
	u8 w, h;
	i16 hstep, vstep;
	TFrame* frame;
    u8 nframe;
    ELook look;
	u8 draw;
} TEntity;

#endif