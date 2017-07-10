#ifndef _TBALL_H_
#define _TBALL_H_

#include <types.h>
#include "../defines.h"

#define BALL_WIDTH SP_BALL_0_W
#define BALL_HEIGHT SP_BALL_0_H
#define SHADOW_BALL_WIDTH SP_BALL_1_W
#define SHADOW_BALL_HEIGHT SP_BALL_1_H


typedef struct {
	TEntity e;
    i32 vx, vy, vz;
    u8* sprite;
    u8 bouncex, bouncey;
    u8 active;
} TBall;

extern TBall ball;

void eraseBall(TBall *ball);
void drawBall(TBall *ball);
void updateBall(TBall *ball);
void initBall(TBall *ball);
void newBall(i32 x, i32 y, TBall *ball);

#endif