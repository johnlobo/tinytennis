#ifndef _TPLAYER_H_
#define _TPLAYER_H_

#include <types.h>

typedef struct {
    u8 look;
    u8* sprite;
} TFrame;

typedef struct {
    i32 x, y;
    i32 px, py;
    u8 state;
    TFrame* frame;
    u8 nframe;
    u8 look;
    u8 hit;
    u8 moved;
} TPlayer;

// Looking to
enum {
    M_right   = 0
    ,  M_left
} ELook;

// Player States
enum {
    ST_stopped  = 0
    ,  ST_walking
    ,  ST_hitting
} EStates;
// Sprites States
#define PLAYER_FRAMES  10
// Animaciones
#define ANIM_PAUSE        8
#define WALKING_FRAMES    4
#define HITTING_FRAMES    5

extern const TFrame g_frames[PLAYER_FRAMES];
extern TFrame* const anim_walking[WALKING_FRAMES];
extern TFrame* const anim_hitting[HITTING_FRAMES];
extern const i16 trajetoriesX[10];

extern TPlayer player;

void assignFrame(TFrame **animation);
void turnFrame(TPlayer player);
void selectSpritePlayer();
void moveRight();
void moveLeft();
void moveUp();
void moveDown();
void drawPlayer();
void erasePlayer();
void redrawPlayer();
void hitting_enter();
void walking_enter(u8 look);
void stopped_enter();
void hitting_animate();
void hitting();
void stopped();
void walking_animate(u8 look);
void walking();
void executeState();

#endif