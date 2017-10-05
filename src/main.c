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
#include "defines.h"
#include "sprites/palette.h"
#include "util/video.h"
#include "keyboard/keyboard.h"
#include "menu/menu.h"
#include "game.h"
#include "util/util.h"

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

const u8 sp_palette[16] = { 0x54, 0x44, 0x4e, 0x53, 0x4c, 0x55, 0x4d, 0x56, 0x5e, 0x5f, 0x5d, 0x52, 0x5c, 0x4a, 0x57, 0x4b };


void myInterruptHandler()
{
    static u8 i; // Static variable to be preserved from call to call

    i++;
    switch (i)
    {
    case 4:
        cpct_scanKeyboard_if();
        break;
    case 6:
        i = 0;
    }
}

void playGameMenuOption(){
    static u32 seed;
    
    seed = wait4Key(Key_3);
	if(!seed) 
        seed++;
	cpct_srand(seed)
	game();
	//decompress((u8*)EXO_outlaws, (u8*)EXOBUFFER_ADDRESS);
	//loopMusic = TRUE
	//cpct_akp_musicInit(G_outlaws);
}

void joystickMenuOption(){
    keys.up    = Joy0_Up;
    keys.down  = Joy0_Down;
    keys.left  = Joy0_Left;
    keys.right = Joy0_Right;
    keys.fire1  = Joy0_Fire1;
    keys.fire2  = Joy0_Fire2;  
}
    
void redefineMenuOption(){
    keys.up    = redefineKey("UP");
    keys.down  = redefineKey("DOWN");
    keys.left  = redefineKey("LEFT");
    keys.right = redefineKey("RIGHT");
    keys.fire1  = redefineKey("FIRE1");
    keys.fire2  = redefineKey("FIRE2");
    keys.pause = redefineKey("PAUSE");
    keys.abort = redefineKey("END");
}

void checkKeyboardMenu() {
    u8 *pvideo;
    u8 selectedOption = 1;
    
    if(cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(Key_CursorUp)){
         deleteIcon(selectedOption);
         if (selectedOption > 0)
            selectedOption--;
        else
            selectedOption = 3;
        drawIcon(selectedOption);
        delay(40);
    }
    if(cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(Key_CursorDown)){
         deleteIcon(selectedOption);
         if (selectedOption < 3)
            selectedOption++;
        else
            selectedOption = 0;
        drawIcon(selectedOption);
        delay(40);
    }
    
    if (cpct_isKeyPressed(Joy0_Fire1) || cpct_isKeyPressed(Key_Space)) {
      
        switch (selectedOption) {
            case 1:
                selectedOption = 1;
                redefineMenuOption();
                break;
            case 2:
                selectedOption = 2;
                joystickMenuOption();
                break;
            case 3:
                selectedOption = 3;
                playGameMenuOption();
		        drawMenu();
                break;
        }
    }

    if(cpct_isKeyPressed(Key_1)){

        selectedOption = 1;
        waitKeyUp(Key_1);
        redefineMenuOption();
    }
    else if(cpct_isKeyPressed(Key_2)){

        selectedOption = 2;
        waitKeyUp(Key_2);
        joystickMenuOption();


    }
	else if(cpct_isKeyPressed(Key_3)){
            
        playGameMenuOption();
		drawMenu();
	}

}


void tennis(){
    
    drawMenu();

    while (1){
        
        checkKeyboardMenu();

    }
    
}


void initMain()
{
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(g_scrbuffers[0], 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLACK);

    // Initilize Keys
    initKeys();
}

void main(void)
{
    cpct_setStackLocation(NEW_STACK_LOCATION);
    cpct_disableFirmware();
    cpct_setInterruptHandler( myInterruptHandler );
    initMain();

    tennis(); 
    
}
