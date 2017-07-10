#ifndef _DEFINES_H_
#define _DEFINES_H_

#define DEBUG 0

#define SCALE 256U
#define FRICTION 0.8
#define GRAVITY (-0.4 * SCALE)

// Pointers to the hardware backbuffer, placed in bank 1
// of the memory (0x8000-0xBFFF)
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

// Game phases
typedef enum{ GM_serve, GM_rest, GM_play } EGamePhases;
//Sides
typedef enum{ SD_up, SD_down } ESides;

typedef struct {
    u8 look;
    u8* sprite;
} TFrame;

typedef struct{
	u32 x[3];
	u32 y[3];
	u32 z[3];
	u8 w, h;
	i32 hstep, vstep;
	TFrame* frame;
    u8 nframe;
    ELook look;
	u8 draw;
} TEntity;

#endif