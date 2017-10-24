//-----------------------------LICENSE NOTICE------------------------------------
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include "TBall.h"
#include "../defines.h"
#include "../sprites/ball.h"
#include "../util/video.h"
#include "../util/util.h"
#include "../levels/court01.h"
#include "TDust.h"
#include "../spriteList/spriteList.h"

const TFrame b1_frame = { M_up, sp_ball_0 };
const TFrame b2_frame = { M_up, sp_ball_1 };


void calcBounce(TBall *ball)
{
    u8 t;
    t = - (2 * ball->vz) / GRAVITY;
    ball->bouncex = ball->e.x[0] + ((ball->vx * t) / SCALE);
    if (ball->bouncex > 200) { //Negative number -> Left side
        ball->bouncex = 0;
    } else if (ball->bouncex > 79) {
        ball->bouncex = 79;      //Right side
    }
    if (ball->bouncey > 220) { //Negative number -> Upper side
        ball->bouncey = 0;
    } else if (ball->bouncex > 199) {
        ball->bouncex = 199;      //Down side
    }
    ball->bouncey = ball->e.y[0] + ((ball->vy * t) / SCALE);
}

//
//  checkBoundaries
//

u8 checkBoundaries(u8 x, u8 y, TBall *ball) {
    u8 result = 0;
    if (x > 210) {
        // Shadow entity
        ball->e.x[0] = 0;
        // Ball entity
        ball->e_ball.x[0] = 0;
        // Common
        ball->vx = -ball->vx * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    } else if ((x + BALL_WIDTH) > 80) {
        // Shadow entity
        ball->e.x[0] = (80 * SCALE) - (BALL_WIDTH * SCALE);
        // Ball entity
        ball->e_ball.x[0] = ball->e.x[0];
        // Common
        ball->vx = -ball->vx * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    }
    if (y > 210) {
        // Shadow entity
        ball->e.y[0] = 0;
        // Ball entity
        ball->e_ball.y[0] = 0;
        // Common
        ball->vy = -ball->vy * (FRICTION / 4);
        calcBounce(ball);
    } else if ((y + BALL_HEIGHT) > 200) {
        // Shadow entity
        ball->e.y[0] = (200 * SCALE) - (BALL_HEIGHT * SCALE);
        // Ball entity
        ball->e_ball.y[0] =  ball->e.y[0] - (ball->e.z[0]  / 2);
        // Common
        ball->vy = -ball->vy * (FRICTION / 4);
        calcBounce(ball);
        result = 1;
    }
    return result;
}

//
//  checkNet
//

u8 checkNet(u8 x, u8 y, u8 z, u8 py, TBall *ball) {
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

void deactivateBall(TBall *ball) {
    //eraseBall(ball);
    // Shadow Entity
    ball->e.draw = 0;
    deleteSprite(ball->e.id, 1);
    // Shadow Entity
    ball->e_ball.draw = 0;
    deleteSprite(ball->e_ball.id, 0);
    // Common
    ball->active = 0;
}

void updateBall(TBall *ball)
{
    u8 x, y, z, py;
    // Shadow entity
    ball->vz += GRAVITY;
    ball->e.x[0] += ball->vx;
    ball->e.y[0] += ball->vy;
    ball->e.z[0] += ball->vz;
    if (ball->e.z[0] > 240 * SCALE) {
        ball->e.z[0] = 0;
    }
    ball->e.draw = 1;
    // Ball entity
    ball->e_ball.x[0] = ball->e.x[0];
    ball->e_ball.y[0] = ball->e.y[0] - (ball->e.z[0]  / 2);
    ball->e_ball.draw = 1;
    x = ball->e.x[0] / SCALE;
    y = ball->e.y[0] / SCALE;
    z = ball->e.z[0] / SCALE;
    py = ball->e.y[1] / SCALE;
    // If ball is in the limits of the court, check collision with the net
    if ((ball->active) && (!checkBoundaries(x, y, ball))) {
        checkNet(x, y, z, py, ball);
        // Check bounce
        if ((z == 0) && (ball->vz < 0))
        {
            if (ball->nBounces<4){
                ball->nBounces++;
                createDust(x, y);
                ball->vx = ball->vx * FRICTION;
                ball->vy = ball->vy * FRICTION;
                ball->vz = -ball->vz * (3 * FRICTION / 4);
                ball->e.z[0] = 0;
                calcBounce(ball);
            } else {
                //Deactivate ball
                deactivateBall(ball);
            }
        }
    }
}

void initBall(TBall *ball)
{
    cpct_memset(ball, 0, sizeof(TBall));
}

void newBall(i32 x, i32 y, TBall *ball)
{
    if (ball->active) {
        // Shadow Entity
        ball->e.draw = 0;
        deleteSprite(ball->e.id, 0);
        // Shadow Entity
        ball->e_ball.draw = 0;
        deleteSprite(ball->e_ball.id, 0);
    }
    // Shadow entity
    ball->e.id = 3;
    ball->e.rx = x;
    ball->e.ry = y;
    ball->e.rz = ((cpct_rand8() % 2) + 4) * SCALE;
    ball->e.x[0] = ball->e.x[1] = x / SCALE;
    ball->e.y[0] = ball->e.y[1] = y / SCALE;
    ball->e.z[0] = ball->e.z[1] = z / SCALE;
    ball->e.frame = &b2_frame;
    ball->e.w = BALL_WIDTH;
    ball->e.h = BALL_HEIGHT;
    ball->e.draw = 1;
    //Ball entity
    ball->e_ball.id = 4;
    ball->e_ball.rx = x;
    ball->e_ball.ry = y - (ball->e.rz  / 2);
    ball->e.rz = 0;
    ball->e_ball.x[0] = ball->e_ball.x[1] = ball->e.x[0];
    ball->e_ball.y[0] = ball->e_ball.y[1] = ball->e_ball.ry / SCALE;
    ball->e_ball.z[0] = ball->e_ball.z[1] = 0;
    ball->e_ball.frame = &b1_frame;
    ball->e_ball.w = BALL_WIDTH;
    ball->e_ball.h = BALL_HEIGHT;
    ball->e_ball.draw = 1;
    //common
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (2 + (cpct_rand8() % 2)) * SCALE;
    ball->vz = (2 + (cpct_rand8() % 5)) * SCALE;
    ball->turn = 1;
    ball->active = 1;
    ball->nBounces = 0;
    calcBounce(ball);
    addSprite(&ball->e);
    addSprite(&ball->e_ball);
}