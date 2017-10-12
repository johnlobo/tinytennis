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
#include "spriteList.h"
#include "../util/video.h"
#include "../levels/court01.h"

TSpriteList spriteList;

void initSpriteList(){
    cpct_memset(&spriteList, 0, sizeof(TSpriteList));
}

void addSprite(TEntity *e){
    u8 i;
    
    if (spriteList.count<MAX_SPRITE_LIST){
        i = 0;
        while ((i<MAX_SPRITE_LIST) && (spriteList.list[i] !=0x0000 )){
            i++;
        }
        if (i<MAX_SPRITE_LIST){
            spriteList.count++;
            spriteList.list[i] = e;
        }
    }
    
}

void deleteSprite(u8 id){
    u8 i = 0;
    
    while ((i<MAX_SPRITE_LIST) && (spriteList.list[i]->id != id )){
        i++;
    }
    if (i<MAX_SPRITE_LIST){
        spriteList.count--;
        cpct_memset(&spriteList.list[i], 0, sizeof(TEntity));
    }
}

void orderList(){
    u8 i = 1;  // Begin with one to avoid to overflow the array
    TEntity *aux;
    
    if (spriteList.count > 1){
        while ((i<spriteList.count) && (spriteList.list[i]->y[0] > spriteList.list[i-1]->y[0])){
            i++;
        }
        if (i<spriteList.count){
            aux = spriteList.list[i];
            spriteList.list[i] = spriteList.list[i+1];
            spriteList.list[i+1] = aux;
        }
    }
}

void eraseEntity(TEntity *e)
{
    //u8 *pvmem;
    u8 posx, posy;
    posx = e->x[1] / SCALE;
    posy = e->y[1] / SCALE;
    if (((posx + e->w) <= WIDTH) && ((posy + e->h) <= HEIGHT))
    {
        cpct_etm_drawTileBox2x4 (posx / 2, posy / 4, (e->w / 2) + 1, (e->h / 4) + 1, MAP_WIDTH, g_scrbuffers[0], court);
    }

}

void drawEntity(TEntity *e)
{
    u8 *pvmem;
    u8 posx, posy;
    posx = e->x[0] / SCALE;
    posy = e->y[0] / SCALE;
    pvmem = cpct_getScreenPtr((u8 *) g_scrbuffers[0], posx, posy);
    cpct_drawSpriteMaskedAlignedTable(e->frame->sprite, pvmem, e->w, e->h, g_tablatrans);
}


void entityUpdate(TEntity *e)
{
    e->x[1] = e->x[0];
    e->y[1] = e->y[0];
    e->z[1] = e->z[0];
    e->draw = 0;
}

void printSprites(){
    u8 i;
    
    for (i=0;i<MAX_SPRITE_LIST;i++){
        if ((spriteList.list[i] != 0x0000) && (spriteList.list[i]->draw)){
            eraseEntity((TEntity*) &(*spriteList.list[i]));
            drawEntity((TEntity*) &(*spriteList.list[i]));
            entityUpdate((TEntity*) &(*spriteList.list[i]));
        }
    }
    
    
}
