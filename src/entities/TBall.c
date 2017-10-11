#include <cpctelera.h>
#include "TBall.h"
#include "../defines.h"
#include "../sprites/ball.h"
#include "../util/video.h"
#include "../util/util.h"
#include "../levels/court01.h"
#include "TDust.h"

const i16 trajetoriesX[10] = {-128, -96, -64, -32, 0 , 0, 32, 64, 96, 128};

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
    if (ball->bouncex > 200){  //Negative number -> Left side 
        ball->bouncex = 0;
    }else if (ball->bouncex> 79){
        ball->bouncex = 79;      //Right side
    }
    if (ball->bouncey > 220){  //Negative number -> Upper side 
        ball->bouncey = 0;
    }else if (ball->bouncex> 199){
        ball->bouncex = 199;      //Down side
    }
    ball->bouncey = (ball->e.y[0] + (ball->vy * t)) / SCALE;
}

//
//  checkBoundaries
//

u8 checkBoundaries(u8 x, u8 y, TBall *ball){
    u8 result = 0;

    if (x > 210){
        ball->e.x[0] = 0;
        ball->vx = -ball->vx * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    } else if ((x + BALL_WIDTH) > 80) {
        ball->e.x[0] = (80 * SCALE) - (BALL_WIDTH * SCALE);
        ball->vx = -ball->vx * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    }

    if (y > 210){
        ball->e.y[0] = 0;
        ball->vy = -ball->vy * (FRICTION / 4);
        calcBounce(ball);
    } else if ((y + BALL_HEIGHT) > 200) {
        ball->e.y[0] = (200 * SCALE) - (BALL_HEIGHT * SCALE);
        ball->vy = -ball->vy * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    } 

    return result;
}

//
//  checkNet
//

u8 checkNet(u8 x, u8 y, u8 z, u8 py, TBall *ball){
    u8 result = 0;

    if (((z < 8) && ((x > 10) && (x < 70 ))) &&
            (((py >= 90) && (y < 90) && (ball->vy < 0)) ||
            ((py <= 90) && (y > 90) && (ball->vy > 0))))
    {
        ball->vx = ball->vx * (FRICTION / 4);
        ball->vy = -ball->vy * (FRICTION / 4);
        ball->vz = ball->vz * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    }

    return result;
}


void updateBall(TBall *ball)
{
    u8 x, y, z, py;

    ball->vz += GRAVITY;
    ball->e.x[0] += ball->vx;
    ball->e.y[0] += ball->vy;
    ball->e.z[0] += ball->vz;
    ball->e.draw = 1;

    x = ball->e.x[0] / SCALE;
    y = ball->e.y[0] / SCALE;
    z = ball->e.z[0] / SCALE;
    py = ball->e.y[1] / SCALE;

    //Deactivate ball
    if ((fast_abs(ball->vx) < 25) && (fast_abs(ball->vy) < 25) && (fast_abs(ball->vz) < 25))
    {
        //eraseBall(ball);
        ball->active = 0;
        ball->e.draw = 0;
    }

    // If ball is in the limits of the court, check collision with the net
    if ((ball->active) && (!checkBoundaries(x,y,ball))) {
        
        checkNet(x,y,z,py,ball);

        // Check bounce
        if (z > 210)
        {
            createDust(x,y);
            ball->vx = ball->vx * FRICTION;
            ball->vy = ball->vy * FRICTION;
            ball->vz = -ball->vz * FRICTION;
            ball->e.z[0] = 0;
            calcBounce(ball);
        }
    }

}

void initBall(TBall *ball)
{
    cpct_memset(ball, 0, sizeof(TBall));
}

void newBall(i32 x, i32 y, TBall *ball)
{
    ball->e.id = 3;
    ball->e.x[0] = ball->e.x[1] = x;
    ball->e.y[0] = ball->e.y[1] = y;
    ball->e.z[0] = ball->e.z[1] = ((cpct_rand8() % 3) + 3) * SCALE;
    ball->e.draw = 1;
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (2 + (cpct_rand8() % 2)) * SCALE;
    ball->vz = (2 + (cpct_rand8() % 5)) * SCALE;
    ball->sprite = (u8 *) sp_ball_0;
    ball->e.w = BALL_WIDTH;
    ball->e.h = BALL_HEIGHT;
    ball->active = 1;
    calcBounce(ball);

}