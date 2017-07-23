#ifndef _TPLAYER_H_
#define _TPLAYER_H_

#include <types.h>
#include "../defines.h"
#include "TBall.h"
#include "../util/util.h"

typedef enum { ST_IAstopped, ST_IAmovingToTarget, ST_IAhitting } EIAStates;

typedef struct {
	i16 speedX, speedY;
	i16 accuracy;
	i16 offense;
} TCharacter;

typedef struct {
    TEntity e;
    u8 phase;
    EStates state;
    ESides side;
    u8 hit;
    EIAStates iaState;
    TCharacter car;
    u8 targetX;
    u8 targetY;
} TPlayer;


// Sprites States
#define PLAYER_FRAMES  	15
// Animaciones
#define ANIM_PAUSE      8
#define ANIM_HIT_PAUSE  16
#define WALKING_FRAMES  4
#define UP_FRAMES    	4
#define DOWN_FRAMES    	4
#define HITTING_FRAMES  5

extern const TFrame g_frames[PLAYER_FRAMES];
extern TFrame* const anim_walking[WALKING_FRAMES];
extern TFrame* const anim_hitting[HITTING_FRAMES];

extern TPlayer player;

void initPlayer1(TPlayer *player);
void initPlayer2(TPlayer *player);
void selectSpritePlayer(TPlayer *player);
void drawPlayer(TPlayer *player);
void erasePlayer(TPlayer *player);
void executeState(TPlayer *player, TBall *ball, TKeys *keys);

#endif