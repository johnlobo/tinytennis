#include "TBall.h"

#include <cpctelera.h>
#include "../defines.h"
#include "../sprites/ball.h"
#include "../util/video.h"
#include "../levels/court01.h"

const i16 trajetoriesX[10] = {0, -64, 64, 0, -128, 128, -172, 172, -240, 240};

u8 t;

void eraseBall(TBall *ball)
{
    i32 posx, posy;
    u8 *pvmem;
    //Shadow
    posx = ball->e.x[1] / SCALE;
    posy = ball->e.y[1] / SCALE;
    if (((posx + SHADOW_BALL_WIDTH) < 80) && ((posy + SHADOW_BALL_HEIGHT) < 200))
    {
        //pvmem = cpct_getScreenPtr((u8*) g_scrbuffers[1], posx, posy);
        //cpct_drawSolidBox(pvmem, #0,SHADOW_BALL_WIDTH,SHADOW_BALL_HEIGHT);
        cpct_etm_drawTileBox2x4 (posx / 2, posy / 4, (SHADOW_BALL_WIDTH / 2) + 1, (SHADOW_BALL_HEIGHT / 4) +
                                 1, MAP_WIDTH, g_scrbuffers[0], court);
    }
    //Ball
    posx = ball->e.x[1] / SCALE;
    posy = ball->e.y[1] / SCALE - (ball->e.z[2] / SCALE / 2);
    if (((posx + BALL_WIDTH) < 80) && ((posy >= 0) && ((posy + BALL_HEIGHT) < 200)))
    {
        //pvmem = cpct_getScreenPtr((u8*) g_scrbuffers[1], posx, posy);
        //cpct_drawSolidBox(pvmem, #0,BALL_WIDTH,BALL_HEIGHT);
        cpct_etm_drawTileBox2x4 (posx / 2, posy / 4, (BALL_WIDTH / 2) + 1, (BALL_HEIGHT / 4) +
                                 1, MAP_WIDTH, g_scrbuffers[0], court);
    }
}

void drawBall(TBall *ball)
{
    i32 posx, posy;
    u8 *pvmem;
    //Shadow
    posx = ball->e.x[0] / SCALE;
    posy = ball->e.y[0] / SCALE;
    if (((posx + SHADOW_BALL_WIDTH) < 80) && ((posy + SHADOW_BALL_HEIGHT) < 200))
    {
        pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], posx, posy);
        cpct_drawSpriteMaskedAlignedTable(sp_ball_1, pvmem, SHADOW_BALL_WIDTH, SHADOW_BALL_HEIGHT, g_tablatrans);
    }
    //Ball
    posx = ball->e.x[0] / SCALE;
    posy = (ball->e.y[0] / SCALE) - (ball->e.z[0] / SCALE / 2);
    if (((posx + BALL_WIDTH) < 80) && ((posy >= 0) && ((posy + BALL_HEIGHT) < 200)))
    {
        pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], posx, posy);
        cpct_drawSpriteMaskedAlignedTable((u8 *) ball->sprite, pvmem, BALL_WIDTH, BALL_HEIGHT, g_tablatrans);
    }
}

void calcBounce(TBall *ball)
{

    //t = - ((2 * ball->vz) / (-0.4 * SCALE));
    t = - (2 * ball->vz) / GRAVITY;
    ball->bouncex = (ball->e.x[0] + (ball->vx * t)) / SCALE;
    ball->bouncey = (ball->e.y[0] + (ball->vy * t)) / SCALE;
}

void updateBall(TBall *ball)
{

    if (ball->active)
    {
        ball->vz += GRAVITY;
        ball->e.x[0] += ball->vx;
        ball->e.y[0] += ball->vy;
        ball->e.z[0] += ball->vz;
        ball->e.draw = 1;

        // Check bounce
        if (ball->e.z[0] > (210 * SCALE))
        {
            ball->vx = ball->vx * FRICTION;
            ball->vy = ball->vy * FRICTION;
            ball->vz = -ball->vz * FRICTION;
            ball->e.z[0] = 0;
            calcBounce(ball);
            //ball->e.draw = 1;
        }
        // Check boundaries
        if (ball->e.x[0] > (210 * SCALE))
        {
            ball->e.x[0] = 0;
            ball->vx = -ball->vx;
            calcBounce(ball);
            ball->e.draw = 1;
        }
        else if ((ball->e.x[0] + (BALL_WIDTH * SCALE)) > (80 * SCALE))
        {
            ball->e.x[0] = (80 * SCALE) - (BALL_WIDTH * SCALE);
            ball->vx = -ball->vx;
            calcBounce(ball);
            //ball->e.draw = 1;
        }
        if (ball->e.y[0] > (210 * SCALE))
        {
            ball->e.y[0] = 0;
            ball->vy = -ball->vy;
            calcBounce(ball);
            //ball->e.draw = 1;
        }
        else if ((ball->e.y[0] + (BALL_HEIGHT * SCALE)) > (200 * SCALE))
        {
            ball->e.y[0] = (200 * SCALE) - (BALL_HEIGHT * SCALE);
            ball->vy = -ball->vy;
            calcBounce(ball);
            //ball->e.draw = 1;
        }

        //Deactivate ball
        //if ((ball->vx < (0.1 * SCALE)) && (ball->vy < (0.1 * SCALE)) && (ball->vz < (0.1 * SCALE))){
        //    ball->active = 0;
        //}
    }
}

void initBall(TBall *ball)
{
    cpct_memset(ball, 0, sizeof(TBall));
}

void newBall(i32 x, i32 y, TBall *ball)
{
    ball->e.x[0] = ball->e.x[1] = ball->e.x[2] = x;
    ball->e.y[0] = ball->e.y[1] = ball->e.y[2] = y;
    ball->e.z[0] = ball->e.z[1] = ball->e.z[2] = ((cpct_rand8() % 3) + 3) * SCALE;
    ball->e.draw = 1;
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (((cpct_rand8() % 4) * -1.6) - 1) * SCALE;
    ball->vz = (((cpct_rand8() % 4) * 1) + 5)  * SCALE;
    ball->sprite = (u8 *) sp_ball_0;
    ball->active = 1;
    calcBounce(ball);
}