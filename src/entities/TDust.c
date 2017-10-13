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

#include "TDust.h"
#include "../sprites/dust.h"
#include "../spriteList/spriteList.h"
#include "../defines.h"
#include "../util/video.h"
#include "../levels/court01.h"

const TFrame d_frames[3] = {
    { M_up, sp_dust_0 }  
    ,   { M_up, sp_dust_1 }
    ,   { M_up, sp_dust_2 }
};

TDustList dusts;

void initDustList(){
    cpct_memset(&dusts, 0, sizeof(TDustList));
}

void createDust(u8 x, u8 y){
    u8 i;
    if (dusts.nDusts<5){
        i = 0;
        while ((i<5) && (dusts.dustList[i].active)){
            i++;
        }
        if (i<5){
            dusts.dustList[i].e.id = i+20;
            dusts.dustList[i].e.x[0] = dusts.dustList[i].e.x[1] = x;
            dusts.dustList[i].e.y[0] = dusts.dustList[i].e.y[1] = y;
            dusts.dustList[i].e.z[0] = dusts.dustList[i].e.z[1] = 0;
            dusts.dustList[i].e.frame = &d_frames[2];
            dusts.dustList[i].e.w = DUST_WIDTH;
            dusts.dustList[i].e.h = DUST_HEIGHT;
            dusts.dustList[i].e.draw = 1;
            dusts.dustList[i].nFrame = DUST_FRAMES * DUST_PAUSE;
            dusts.dustList[i].active = 1;
            dusts.nDusts++;
            addSprite(&dusts.dustList[i].e);
        }
    }
}

void removeDust(u8 i){
    dusts.dustList[i].active = 0;
    deleteSprite(dusts.dustList[i].e.id,1);
    dusts.nDusts--;
}

void updateDusts(){
    u8 i;
    
    if (dusts.nDusts > 0){
        for (i=0; i<5; i++) {
            if (dusts.dustList[i].active){
                if (dusts.dustList[i].nFrame > 1)
                {
                    dusts.dustList[i].nFrame--;
                    dusts.dustList[i].e.frame = &d_frames[dusts.dustList[i].nFrame / DUST_PAUSE];
                    }
                }
                else
                {
                    removeDust(i);
                }
            }
        }
    }
