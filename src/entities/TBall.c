#include "TBall.h"

#include <cpctelera.h>
#include "../defines.h"
#include "../sprites/ball.h"

const i16 trajetoriesX[10] = {0, -64, 64, 0, -128, 128, -172, 172, -240, 240};

u8 t;

void eraseBall(TBall *ball) {
    i32 posx, posy;
    u8* pvmem;
    //Shadow
    posx = ball->px / SCALE;
    posy = ball->py / SCALE;
    if (((posx + SHADOW_BALL_WIDTH) < 80) && ((posy + SHADOW_BALL_HEIGHT) < 200)) {
        pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
        cpct_drawSolidBox(pvmem, #0,SHADOW_BALL_WIDTH,SHADOW_BALL_HEIGHT);
    }
    //Ball
    posx = ball->px / SCALE;
    posy = ball->py / SCALE - (ball->pz / SCALE / 2);
    if (((posx + BALL_WIDTH) < 80) && ((posy >= 0) && ((posy + BALL_HEIGHT) < 200))) {
        pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
        cpct_drawSolidBox(pvmem, #0,BALL_WIDTH,BALL_HEIGHT);
    }
}

void drawBall(TBall *ball) {
    i32 posx, posy;
    u8* pvmem;
    //Shadow
    posx = ball->x / SCALE;
    posy = ball->y / SCALE;
    if (((posx + SHADOW_BALL_WIDTH) < 80) && ((posy + SHADOW_BALL_HEIGHT) < 200)) {
        pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
        cpct_drawSpriteMaskedAlignedTable(sp_ball_1, pvmem, SHADOW_BALL_WIDTH, SHADOW_BALL_HEIGHT, g_tablatrans);
    }
    //Ball
    posx = ball->x / SCALE;
    posy = (ball->y / SCALE) - (ball->z / SCALE / 2);
    if (((posx + BALL_WIDTH) < 80) && ((posy >= 0) && ((posy + BALL_HEIGHT) < 200))) {
        pvmem = cpct_getScreenPtr((u8*) CPCT_VMEM_START, posx, posy);
        cpct_drawSpriteMaskedAlignedTable((u8*) ball->sprite, pvmem, BALL_WIDTH, BALL_HEIGHT, g_tablatrans);
    }
}

void calcBounce(TBall *ball){

    //t = - ((2 * ball->vz) / (-0.4 * SCALE));
    t = - (2 * ball->vz) / GRAVITY;
    ball->bouncex = (ball->x + (ball->vx * t)) / SCALE;
    ball->bouncey = (ball->y + (ball->vy * t)) / SCALE;
}

void updateBall(TBall *ball) {

    ball->px = ball->x;
    ball->py = ball->y;
    ball->pz = ball->z;
    ball->vz += GRAVITY;
    ball->x += ball->vx;
    ball->y += ball->vy;
    ball->z += ball->vz;

    // Check bounce
    if (ball->z < 0) {
        ball->vx = ball->vx * FRICTION;
        ball->vy = ball->vy * FRICTION;
        ball->vz = -ball->vz * FRICTION;
        ball->z = 0;
        calcBounce(ball);
    }
    // Check boundaries
    if (ball->x < 0) {
        ball->x = 0;
        ball->vx = -ball->vx;
        calcBounce(ball);
    } else if ((ball->x + (BALL_WIDTH * SCALE)) > (80 * SCALE)) {
        ball->x = (80 * SCALE) - (BALL_WIDTH * SCALE);
        ball->vx = -ball->vx;
        calcBounce(ball);
    }
    if (ball->y < 0) {
        ball->y = 0;
        ball->vy = -ball->vy;
        calcBounce(ball);
    } else if ((ball->y + (BALL_HEIGHT * SCALE)) > (200 * SCALE)) {
        ball->y = (200 * SCALE) - (BALL_HEIGHT * SCALE);
        ball->vy = -ball->vy;
        calcBounce(ball);
    }

    //Deactivate ball
    //if ((ball->vx < (0.1 * SCALE)) && (ball->vy < (0.1 * SCALE)) && (ball->vz < (0.1 * SCALE))){
    //    ball->active = 0;
    //}
}

void initBall(TBall *ball) {
    cpct_memset(ball, 0, sizeof(TBall));
}

void newBall(i32 x, i32 y, TBall *ball) {
    ball->x = ball->px = x;
    ball->y = ball->py = y;
    ball->z = ball->pz = ((cpct_rand8() % 3) + 3) * SCALE;
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (((cpct_rand8() % 4) * -1.6) - 1) * SCALE;
    ball->vz = (((cpct_rand8() % 4) * 1) + 5)  * SCALE;
    ball->sprite = (u8*) sp_ball_0;
    ball->active = 1;
    calcBounce(ball);
}