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


void deleteIcon(u8 option) {
  u8 *pvideo;
  pvideo = cpct_getScreenPtr(SCR_VMEM, 18, 35 + (option * 15));
  cpct_drawSolidBox(pvideo, 0, 2, 4);
}

void drawIcon(u8 option) {
  u8 *pvideo;
  u8 counter = 0;
  pvideo = cpct_getScreenPtr(SCR_VMEM, 18, 35 + (option * 15));
  cpct_drawSprite((u8*) sp_ball_0, pvideo, 2, 4);
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

    drawIcon(1);

} 