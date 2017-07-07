#ifndef _TPLAYER_H_
#define _TPLAYER_H_

#include <types.h>
#include "TBall.h"
#include "../util/util.h"

// Looking to
typedef enum { M_right, M_left, M_up, M_down } ELook;
// Player States
typedef enum { ST_stopped, ST_walking, ST_hitting, ST_preparing, ST_serving } EStates;


typedef struct {
    u8 look;
    u8* sprite;
} TFrame;

typedef struct {
    i32 x, y;
    i32 px, py;
    u8 phase;
    EStates state;
    ESides side;
    TFrame* frame;
    u8 nframe;
    ELook look;
    u8 hit;
    u8 moved;
} TPlayer;


// Sprites States
#define PLAYER_FRAMES  15
// Animaciones
#define ANIM_PAUSE        8
#define WALKING_FRAMES    4
#define UP_FRAMES    4
#define DOWN_FRAMES    4
#define HITTING_FRAMES    5

extern const TFrame g_frames[PLAYER_FRAMES];
extern TFrame* const anim_walking[WALKING_FRAMES];
extern TFrame* const anim_hitting[HITTING_FRAMES];

extern TPlayer player;

void initPlayer(TPlayer *player) __z88dk_fastcall;
void initCom(TPlayer *player) __z88dk_fastcall;
void assignFrame(TFrame **animation, TPlayer *player);
void turnFrame(TPlayer *player) __z88dk_fastcall;
void selectSpritePlayer(TPlayer *player) __z88dk_fastcall;
void moveRight(TPlayer *player) __z88dk_fastcall;
void moveLeft(TPlayer *player) __z88dk_fastcall;
void moveUp(TPlayer *player) __z88dk_fastcall;
void moveDown(TPlayer *player) __z88dk_fastcall;
void drawPlayer(TPlayer *player) __z88dk_fastcall;
void erasePlayer(TPlayer *player) __z88dk_fastcall;
void redrawPlayer(TPlayer *player) __z88dk_fastcall;
void hitting_enter(TPlayer *player, TBall *ball);
void walking_enter(u8 look, TPlayer *player);
void stopped_enter(TPlayer *player) __z88dk_fastcall;
void hitting_animate(TPlayer *player) __z88dk_fastcall;
void hitting(TPlayer *player) __z88dk_fastcall;
void stopped(TPlayer *player, TBall *ball, TKeys *keys);
void walking_animate(u8 look, TPlayer *player);
void walking(TPlayer *player, TBall *ball, TKeys *keys);
void executeState(TPlayer *player, TBall *ball, TKeys *keys);

#endif