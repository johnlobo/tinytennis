//-----------------------------LICENSE NOTICE------------------------------------
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------


#include "menu.h"
#include "../text/text.h"
#include "../util/video.h"
#include "../sprites/ball.h"

const i8 jumpTable[10] = {4, 2, 1, 1, 0, 0, -1, -1, -2, -4};

void initIcon(TIcon *icon){
	icon->selectedOption = 1;
	icon->height = 0;
	icon->vy = -1;
	icon->sprite = (u8*) sp_ball_0;
	icon->shadowSprite = (u8*) sp_ball_1;
}

void deleteIcon(TIcon *icon){
  u8 *pvideo;

  //Shadow
  pvideo = cpct_getScreenPtr(SCR_VMEM, 19, 37 + (icon->selectedOption * 15));
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 59, 37 + (icon->selectedOption * 15));
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);

  pvideo = cpct_getScreenPtr(SCR_VMEM, 19, 37 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 59, 37 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSolidBox(pvideo, 0,ICON_W, ICON_H);
}

void drawIcon(TIcon *icon) {
  u8 *pvideo;
  //Shadow
  pvideo = cpct_getScreenPtr(SCR_VMEM, 19, 37 + (icon->selectedOption * 15));
  cpct_drawSprite((u8*) icon->shadowSprite, pvideo, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 59, 37 + (icon->selectedOption * 15));
  cpct_drawSprite((u8*) icon->shadowSprite, pvideo, ICON_W, ICON_H);
  //Ball
  pvideo = cpct_getScreenPtr(SCR_VMEM, 19, 37 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSprite((u8*) icon->sprite, pvideo, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 59, 37 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSprite((u8*) icon->sprite, pvideo, ICON_W, ICON_H);
}

void updateIcon(TIcon *icon){
	
	deleteIcon(icon);
	
	if (icon->vy == 9){
		icon->vy = 0;
	} else {
		icon->vy++;
	}

	icon->height += jumpTable[icon->vy];

	drawIcon(icon);
}

void drawMenu(){

	cpct_memset(g_scrbuffers[0], 0, 0x4000);

	drawText("TINY TENNIS", 0,0,1);

	drawText("1 REDEFINE KEYS", 0,50,1);
	drawText("2 PRACTICE     ", 0,65,1);
	drawText("3 PLAY         ", 0,80,1);


	drawText("CODE GRAPHICS AND MUSIC", 0,145,1);
	drawText("JOHN LOBO", 0,160,1);

	drawText("@2017 GLASNOST CORP.", 0,175,1);

} 