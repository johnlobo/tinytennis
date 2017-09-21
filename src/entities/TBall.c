#include <cpctelera.h>
#include "TBall.h"
#include "../defines.h"
#include "../sprites/ball.h"
#include "../util/video.h"
#include "../util/util.h"
#include "../levels/court01.h"

const i16 trajetoriesX[10] = {0, -64, 64, 0, -128, 128, -172, 172, -240, 240};

void eraseBall(TBall *ball)
{
    i32 posx, posy;
    //Shadow
    posx = ball->e.x[1] / SCALE;
    posy = ball->e.y[1] / SCALE;
    if (((posx + SHADOW_BALL_WIDTH) < 80) && ((posy + SHADOW_BALL_HEIGHT) < 200))
    {
        cpct_etm_drawTileBox2x4 (posx / 2, posy / 4, (SHADOW_BALL_WIDTH / 2) + 1, (SHADOW_BALL_HEIGHT / 4) +
                                 1, MAP_WIDTH, g_scrbuffers[0], court);
    }
    //Ball
    posx = ball->e.x[1] / SCALE;
    posy = ball->e.y[1] / SCALE - (ball->e.z[1] / SCALE / 2);
    if (((posx + BALL_WIDTH) < 80) && ((posy >= 0) && ((posy + BALL_HEIGHT) < 200)))
    {
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
    u8 t;
    t = - (2 * ball->vz) / GRAVITY;
    ball->bouncex = (ball->e.x[0] + (ball->vx * t)) / SCALE;
    ball->bouncey = (ball->e.y[0] + (ball->vy * t)) / SCALE;
}


void updateBall(TBall *ball)
{
    u8 x, y, z, py;

    ball->vz += GRAVITY;
    ball->e.x[0] += ball->vx;
    ball->e.y[0] += ball->vy;
    ball->e.z[0] += ball->vz;
    ball->e.draw = 2;

    x = ball->e.x[0] / SCALE;
    y = ball->e.y[0] / SCALE;
    z = ball->e.z[0] / SCALE;
    py = ball->e.y[1] / SCALE;


    // Check net
    if ((z < 20) && ((x > 10) && (x < 70 )) &&
            ((py >= 90) && (y < 90) && (ball->vy < 0)) ||
            ((py <= 90) && (y > 90) && (ball->vy > 0)))
    {
        ball->vx = ball->vx * FRICTION;
        ball->vy = -ball->vy * FRICTION;
        ball->vz = ball->vz * FRICTION;
        calcBounce(ball);
    }

    // Check bounce
    if (z > 210)
    {
        ball->vx = ball->vx * FRICTION;
        ball->vy = ball->vy * FRICTION;
        ball->vz = -ball->vz * FRICTION;
        ball->e.z[0] = 0;
        calcBounce(ball);
    }

    // Check boundaries
    if (x > 210)
    {
        ball->e.x[0] = 0;
        ball->vx = -ball->vx;
        calcBounce(ball);
        ball->e.draw = 2;
    }
    else if ((x + BALL_WIDTH) > 80)
    {
        ball->e.x[0] = (80 * SCALE) - (BALL_WIDTH * SCALE);
        ball->vx = -ball->vx;
        calcBounce(ball);
    }
    if (y > 210)
    {
        ball->e.y[0] = 0;
        ball->vy = -ball->vy;
        calcBounce(ball);
    }
    else if ((y + BALL_HEIGHT) > 200)
    {
        ball->e.y[0] = (200 * SCALE) - (BALL_HEIGHT * SCALE);
        ball->vy = -ball->vy;
        calcBounce(ball);
    }

    //Deactivate ball
    if ((ball->vx < 16) && (ball->vy < 16) && (ball->vz < 16))
    {
        eraseBall(ball);
        ball->active = 0;
        ball->e.draw = 0;
    }
}

void initBall(TBall *ball)
{
    cpct_memset(ball, 0, sizeof(TBall));
}

void newBall(i32 x, i32 y, TBall *ball)
{
    ball->e.x[0] = ball->e.x[1] = x;
    ball->e.y[0] = ball->e.y[1] = y;
    ball->e.z[0] = ball->e.z[1] = ((cpct_rand8() % 3) + 3) * SCALE;
    ball->e.draw = 1;
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (((cpct_rand8() % 4) * -1.1) - 1) * SCALE;
    ball->vz = (((cpct_rand8() % 4) * 1) + 5)  * SCALE;
    ball->sprite = (u8 *) sp_ball_0;
    ball->active = 1;
    calcBounce(ball);

}