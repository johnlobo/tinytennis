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
#include "TBallMachine.h"
#include "../spriteList/spriteList.h"
#include "../defines.h"
#include "../sprites/machine.h"
#include "../sprites/cannon.h"
#include "../entities/TBall.h"

const i8 bmAngles[5] = {-127, -64,  0, 64,  127};
const TFrame bm_frame = { sp_machine };
const u8 *cannon_frame[5] = {sp_cannon_0, sp_cannon_1, sp_cannon_2, sp_cannon_3, sp_cannon_4 };

TBallMachine ballMachine;
static u32 c;

void initBallMachine(){
    cpct_memset(&ballMachine, 0, sizeof(TBallMachine));
    c = 0;
}
void createBallMachine(u8 x, u8 y){
    u8 *pvideo;
    
    ballMachine.x = x;
    ballMachine.y = y;
    ballMachine.w = SP_MACHINE_W;
    ballMachine.h = SP_MACHINE_H;
    ballMachine.c.x = x + (SP_MACHINE_W / 2);
    ballMachine.c.y = y + (SP_MACHINE_H / 2);
    ballMachine.c.w = SP_CANNON_0_W;
    ballMachine.c.h = SP_CANNON_0_H;
    ballMachine.c.angle = 5;
    ballMachine.c.speed = 3;
    ballMachine.c. dir= 1;
    ballMachine.ballSpped = 1;
    ballMachine.active = 1; 

    
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x, y);
    cpct_drawSprite(sp_machine, pvideo, SP_MACHINE_W, SP_MACHINE_H);
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x + (SP_MACHINE_W / 2), y + (SP_MACHINE_H / 2));
    cpct_drawSprite(sp_cannon_2, pvideo, SP_CANNON_0_W, SP_CANNON_0_H);
}

void activateBallMachine(){
    ballMachine.active = 1; 
}

void deActivateBallMachine(){
    ballMachine.active = 0; 
}

void updateBallMachine(TBall *ball){
    u8 *pvideo;
    
    c++;
    if (ballMachine.active){
        if ((ballMachine.c.dir == 1) && (ballMachine.c.angle == 5)){
            ballMachine.c.dir = -1;
        } else if ((ballMachine.c.dir == -1) && (ballMachine.c.angle == 0)){
            ballMachine.c.dir = 1;
        }
        ballMachine.c.angle += ballMachine.c.dir;
        
        pvideo = cpct_getScreenPtr(CPCT_VMEM_START, ballMachine.x + (SP_MACHINE_W / 2), ballMachine.y + (SP_MACHINE_H / 2));
        cpct_drawSprite(&(*cannon_frame[ballMachine.c.angle]), pvideo, SP_CANNON_0_W, SP_CANNON_0_H);   
        
        if (((c % ballMachine.c.speed) == 0) && (ball->active == 0)){
             newBall(ballMachine.x + (SP_MACHINE_W / 2), ballMachine.y + (SP_MACHINE_H), ball);
        }
    }
    
}