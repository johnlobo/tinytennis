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
#include "entities/TMatch.h"
#include "music/song02-2.h"
#include "music/song00.h"


// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x500, M0, 0);

u8 playing;
TKeys keys;
TIcon icon;
TMatch match;
u32 seed;

const u8 sp_palette[16] = { 0x54, 0x44, 0x4e, 0x53, 0x4c, 0x55, 0x4d, 0x56, 0x5e, 0x5f, 0x5d, 0x52, 0x5c, 0x4a, 0x57, 0x4b };

const i16 trajetoriesX[11] = {-150, -128, -96, -64, -32, 0, 32, 64, 96, 128, 150};

//////////////////////////////////////////////////////////////////
// playmusic
//
//  Function to play music saving the registers
//
// Returns: void.
//
//

void playMusic() {
    __asm
    exx
    .db #0x08
    push af
    push bc
    push de
    push hl
    call _cpct_akp_musicPlay
    pop hl
    pop de
    pop bc
    pop af
    .db #0x08
    exx
    __endasm;
}

//////////////////////////////////////////////////////////////////
// activateMusic
//
//  Activate music
//
// Returns:
//  void
//

void activateMusic() {
    playing = 1;
    cpct_akp_stop();
    cpct_akp_musicInit(song02);
    cpct_akp_SFXInit(song02);
    cpct_akp_musicPlay();
}

//////////////////////////////////////////////////////////////////
// deActivateMusic
//
//  deActivate music
//
// Returns:
//  void
//

void deActivateMusic() {
    playing = 0;
    cpct_akp_stop();
    cpct_akp_musicInit(song00);
    cpct_akp_SFXInit(song00);
    cpct_akp_musicPlay();

}

//////////////////////////////////////////////////////////////////
// myInterruptHandler
//
//  Interruphandler that subsitutes the default one. Includes calls for reading the keyboard and playing music, if activated
//
// Returns:
//  void
//
void myInterruptHandler()
{
    static u8 i; // Static variable to be preserved from call to call

    i++;
    switch (i)
    {
    case 4:
        cpct_scanKeyboard_if();
        break;
    case 5:
        playMusic();
    case 6:
        i = 0;
    }
}

void playPracticeMenuOption() {
    practice(&keys);
}


void playGameMenuOption() {
    //fadeOut(&sp_palette[0]);
    if (!seed)
        seed++;
    cpct_srand(seed)
    //deActivateMusic();
    
    initMatch(&match);
    
    createMatch(3, "DAVID\0", "AI\0", &match);
    
    game(&match, &keys);
    //decompress((u8*)EXO_outlaws, (u8*)EXOBUFFER_ADDRESS);
    //loopMusic = TRUE
    //cpct_akp_musicInit(G_outlaws);
    //activateMusic();
}


void redefineMenuOption() {
    keys.up    = redefineKey("UP");
    keys.down  = redefineKey("DOWN");
    keys.left  = redefineKey("LEFT");
    keys.right = redefineKey("RIGHT");
    keys.fire1  = redefineKey("FIRE1");
    keys.fire2  = redefineKey("FIRE2");
    keys.pause = redefineKey("PAUSE");
    keys.abort = redefineKey("END");
}

void checkKeyboardMenu(TIcon *icon) {

    if (cpct_isKeyPressed(Joy0_Up) || cpct_isKeyPressed(keys.up)) {
        deleteIcon(icon);
        if (icon->selectedOption > 1)
            icon->selectedOption--;
        else
            icon->selectedOption = 3;
        drawIcon(icon);
        delay(30);
    }
    if (cpct_isKeyPressed(Joy0_Down) || cpct_isKeyPressed(keys.down)) {
        deleteIcon(icon);
        if (icon->selectedOption < 3)
            icon->selectedOption++;
        else
            icon->selectedOption = 1;
        drawIcon(icon);
        delay(30);
    }

    if (cpct_isKeyPressed(Joy0_Fire1) || cpct_isKeyPressed(Joy0_Fire2) || cpct_isKeyPressed(keys.fire1) || cpct_isKeyPressed(keys.fire2)) {

        switch (icon->selectedOption) {
        case 1:
            icon->selectedOption = 1;
            redefineMenuOption();
            break;
        case 2:
            icon->selectedOption = 2;
            playPracticeMenuOption();
            drawMenu();
            break;
        case 3:
            icon->selectedOption = 3;
            playGameMenuOption();
            drawMenu();
            break;
        }
    }

    if (cpct_isKeyPressed(Key_1)) {

        waitKeyUp(Key_1);
        icon->selectedOption = 1;
        redefineMenuOption();
    }
    else if (cpct_isKeyPressed(Key_2)) {

        waitKeyUp(Key_2);
        icon->selectedOption = 2;
        playPracticeMenuOption();
        drawMenu();
    }
    else if (cpct_isKeyPressed(Key_3)) {

        waitKeyUp(Key_3);
        icon->selectedOption = 3;
        playGameMenuOption();
        drawMenu();
    }

}


void tennis() {

    initIcon(&icon);
    drawMenu();
    drawIcon(&icon);

    while (1) {
        seed++;
        checkKeyboardMenu(&icon);
        delay(10);
        cpct_waitVSYNC();
        updateIcon(&icon);
    }

}


void initMain()
{
    cpct_setVideoMode(0);
    // Clean up Screen and BackBuffer filling them up with 0's
    cpct_memset(g_scrbuffers[0], 0x00, 0x4000);
    cpct_setPalette(sp_palette, 16);
    cpct_setBorder(HW_BLACK);

    // Music on
    //activateMusic();

    // Initilize Keys
    initKeys(&keys);
}

void main(void)
{
    cpct_setStackLocation(NEW_STACK_LOCATION);
    cpct_disableFirmware();
    cpct_setInterruptHandler( myInterruptHandler );
    initMain();

    tennis();

}
