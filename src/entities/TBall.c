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
#include "../defines.h"
#include "TBall.h"
#include "TDust.h"
#include "../util/video.h"
#include "../util/util.h"
#include "../levels/court01.h"
#include "../spriteList/spriteList.h"
#include "../sprites/ball.h"
#include "../text/text.h"

const TFrame b1_frame = { sp_ball_0 };
const TFrame b2_frame = { sp_ball_1 };


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

u8 checkBoundaries(TBall *ball) {
    u8 result = 0;
    if (ball->e.x[0] > 210) {
        // Shadow entity
        ball->e.rx = 0;
        // Ball entity
        ball->e_ball.rx = 0;
        // Common
        ball->vx = -ball->vx * (FRICTION / 4);
        result = 1;
    } else if ((ball->e.x[0] + BALL_WIDTH) > 80) {
        // Shadow entity
        ball->e.rx = (80 * SCALE) - (BALL_WIDTH * SCALE);
        // Ball entity
        ball->e_ball.rx = ball->e.rx;
        // Common
        ball->vx = -ball->vx * (FRICTION / 4);
        result = 1;
    }
    if (ball->e.y[0] > 210) {
        // Shadow entity
        ball->e.ry = 0;
        // Ball entity
        ball->e_ball.ry = 0;
        // Common
        ball->vy = -ball->vy * (FRICTION / 4);
        result = 1;
    } else if ((ball->e.y[0] + BALL_HEIGHT) > 200) {
        // Shadow entity
        ball->e.ry = (200 * SCALE) - (BALL_HEIGHT * SCALE);
        // Ball entity
        ball->e_ball.ry =  ball->e.ry - (ball->e.rz  / 2);
        // Common
        ball->vy = -ball->vy * (FRICTION / 4);
        result = 1;
    }
    
    if (result) {
        ball->e.x[0] = ball->e.rx / 256;
        ball->e.y[0] = ball->e.ry / 256;
        ball->e_ball.x[0] = ball->e_ball.rx / 256;
        ball->e_ball.y[0] = ball->e_ball.ry / 256;
        calcBounce(ball);
    }
    return result;
}


//
//  checkNet
//

u8 checkNet(TBall *ball) {
    u8 result = 0;
    if (
        (((ball->e.x[0] > 10) && (ball->e.x[0] < 70 ))) &&
        (((ball->e.y[1] >= 90) && (ball->e.y[0] < 90) && (ball->vy < 0)) ||
        ((ball->e.y[1] <= 90) && (ball->e.y[0] > 90) && (ball->vy > 0))))
    //if (ball->e.x[0], ball->e.y[0], ball->e.w, ball->e.h, 10,90,60,)
    {
        drawText("NET!!", 0,95,1);
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


u8 insideCourt(TBall *ball){
    return (
        (ball->e.x[0]>10) &&
        (ball->e.x[0]<70) &&
        (ball->e.y[0]>20) &&
        (ball->e.y[0]<180) 
    );
}

void updateBall(TBall *ball)
{
    // Shadow entity
    ball->vz += GRAVITY;
    ball->e.rx += ball->vx;
    ball->e.ry += ball->vy;
    ball->e.rz += ball->vz;
    if (ball->e.rz > (240 * SCALE)) {
        ball->e.rz = 0;
    }
    ball->e.x[0] = ball->e.rx / SCALE;
    ball->e.y[0] = ball->e.ry / SCALE;
    ball->e.draw = 1;
    // Ball entity
    ball->e_ball.rx = ball->e.rx;
    ball->e_ball.ry = ball->e.ry - (ball->e.rz  / 2);
    ball->e_ball.draw = 1;
    ball->e_ball.x[0] = ball->e_ball.rx / SCALE;
    ball->e_ball.y[0] = ball->e_ball.ry / SCALE;
    // If ball is in the limits of the court, check collision with the net
    if ((ball->active) && (!checkBoundaries(ball))) {
        if (ball->e.rz < (8 * SCALE)){
            checkNet(ball);
        }
        // Check bounce
        if (((ball->e.rz / SCALE) == 0) && (ball->vz < 0))
        {
            if (ball->nBounces<4){
                ball->nBounces++;
                if (ball->nBounces == 1){
                    if (insideCourt(ball) == 0){  //BALL OUT
                        drawText("OUT!!", 0,95,1);
                        ball->live = 0;
                        ball->winner = ball->turn;
                    }
                } else if (ball->live == 1) {  // POINT
                    drawText("POINT!!", 0,95,1);
                    ball->live = 0;
                    if (ball->turn == 2){
                        ball->winner = 1;
                    } else {
                        ball->winner = 2;
                    }
                }
                createDust(ball->e.x[0], ball->e.y[0]);
                ball->vx = ball->vx * FRICTION;
                ball->vy = ball->vy * FRICTION;
                ball->vz = -ball->vz * (3 * FRICTION / 4);
                ball->e.rz = 0;
                ball->e_ball.rz = 0;
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

void newBall(u8 x, u8 y, TBall *ball)
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
    ball->e.rx = x * SCALE;
    ball->e.ry = y * SCALE;
    ball->e.rz = ((cpct_rand8() % 2) + 4) * SCALE;
    ball->e.x[0] = ball->e.x[1] = x;
    ball->e.y[0] = ball->e.y[1] = y;
    ball->e.frame = &b2_frame;
    ball->e.w = BALL_WIDTH;
    ball->e.h = BALL_HEIGHT;
    ball->e.draw = 1;
    //Ball entity
    ball->e_ball.id = 4;
    ball->e_ball.rx = ball->e.rx;
    ball->e_ball.ry = ball->e.ry - (ball->e.rz  / 2);
    ball->e_ball.rz = 0;
    ball->e_ball.x[0] = ball->e_ball.x[1] = x;
    ball->e_ball.y[0] = ball->e_ball.y[1] = ball->e_ball.ry / SCALE;
    ball->e_ball.frame = &b1_frame;
    ball->e_ball.w = BALL_WIDTH;
    ball->e_ball.h = BALL_HEIGHT;
    ball->e_ball.draw = 1;
    //common
    ball->vx = trajetoriesX[cpct_rand8() % 10];
    ball->vy = (2 + (cpct_rand8() % 2)) * SCALE;
    ball->vz = (2 + (cpct_rand8() % 5)) * SCALE;
    ball->turn = 1;
    ball->live = 1;
    ball->active = 1;
    ball->nBounces = 0;
    calcBounce(ball);
    addSprite(&ball->e);
    addSprite(&ball->e_ball);
}