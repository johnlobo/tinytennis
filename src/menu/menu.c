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

void initIcon(TIcon *icon){
	icon->selectedOption = 1;
	icon->height = MAX_HEIGHT;
	icon->vy = -1;
	icon->sprite = sp_ball_0;
	icon->shadowSprite = sp_ball_1;
}

void deleteIcon(TIcon *icon){
  u8 *pvideo;

  //Shadow
  pvideo = cpct_getScreenPtr(SCR_VMEM, 24, 36 + (icon->selectedOption * 15));
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 53, 36 + (icon->selectedOption * 15));
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);

  pvideo = cpct_getScreenPtr(SCR_VMEM, 24, 36 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSolidBox(pvideo, 0, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 53, 36 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSolidBox(pvideo, 0,ICON_W, ICON_H);
}

void drawIcon(TIcon *icon) {
  u8 *pvideo;
  //Shadow
  pvideo = cpct_getScreenPtr(SCR_VMEM, 24, 36 + (icon->selectedOption * 15));
  cpct_drawSprite((u8*) *icon->shadowSprite, pvideo, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 53, 36 + (icon->selectedOption * 15));
  cpct_drawSprite((u8*) *icon->shadowSprite, pvideo, ICON_W, ICON_W);
  //Ball
  pvideo = cpct_getScreenPtr(SCR_VMEM, 24, 36 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSprite((u8*) *icon->sprite, pvideo, ICON_W, ICON_H);
  pvideo = cpct_getScreenPtr(SCR_VMEM, 53, 36 + (icon->selectedOption * 15) - icon->height);
  cpct_drawSprite((u8*) *icon->sprite, pvideo, ICON_W, ICON_H);
}

void updateIcon(TIcon *icon){
	deleteIcon(icon);
	if ((icon->height == 0) && (icon->vy == -1)){
		icon->vy = 1;
	} else if ((icon->height == MAX_HEIGHT) && (icon->vy == 1)){
		icon->vy = -1;
	}

	icon->height += icon->vy;

	drawIcon(icon);
}

void drawMenu(){

	cpct_memset(g_scrbuffers[0], 0, 0x4000);

	drawText("TINY TENNIS", 0,0,1);

	drawText("1 KEYBOARD", 0,50,1);
	drawText("2 JOYSTICK", 0,65,1);
	drawText("3 PLAY    ", 0,80,1);


	drawText("CODE GRAPHICS AND MUSIC", 0,145,1);
	drawText("JOHN LOBO", 0,160,1);

	drawText("@2017 GLASNOST CORP.", 0,175,1);

} 