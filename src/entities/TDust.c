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
#include "../defines.h"
#include "../util/video.h"
#include "../levels/court01.h"


u8 *const *anim_dust[DUST_FRAMES] = {&sp_dust_2, &sp_dust_1, &sp_dust_0};

TDustList dusts;

void initDustList(){
    u8 i;

    for (i = 0; i < 5; i++) {
        dusts.dustList[i].x = 0;
        dusts.dustList[i].y = 0;
        dusts.dustList[i].nFrame = 0;
        dusts.dustList[i].active = 0;
    }
    dusts.nDusts = 0;
}

void eraseDust(u8 i)
{
    if (((dusts.dustList[i].x + DUST_WIDTH) <= WIDTH) && ((dusts.dustList[i].y + DUST_HEIGHT) <= HEIGHT))
    {
        cpct_etm_drawTileBox2x4 (dusts.dustList[i].x / 2, dusts.dustList[i].y / 4, (DUST_WIDTH / 2) + 1, 
                                 (DUST_HEIGHT / 4) + 1, MAP_WIDTH, g_scrbuffers[0], court);
    }

}

void drawDust(u8 i)
{
    u8 *pvmem;
    pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], dusts.dustList[i].x, dusts.dustList[i].y);
    cpct_drawSpriteMaskedAlignedTable(anim_dust[dusts.dustList[i].nFrame / DUST_PAUSE], pvmem, DUST_WIDTH, DUST_HEIGHT, g_tablatrans);
}

void createDust(u8 x, u8 y){
    u8 i;
    if (dusts.nDusts<5){
        i = 0;
        while ((i<5) && (dusts.dustList[i].active)){
            i++;
        }
        if (i<5){
            dusts.dustList[i].x = x;
            dusts.dustList[i].y = y;
            dusts.dustList[i].nFrame = DUST_FRAMES * DUST_PAUSE - 1;
            dusts.dustList[i].active = 1;
            dusts.nDusts++;
            drawDust(i);
        }
    }
}

void removeDust(u8 i){
    eraseDust(i);
    dusts.dustList[i].active = 0;
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
                    //if (dusts.dustList[i].nFrame%DUST_PAUSE == 0){
                        eraseDust(i);
                        drawDust(i);
                    //}
                }
                else
                {
                    removeDust(i);
                }
            }
        }
    }
}
