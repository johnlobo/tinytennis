//-----------------------------LICENSE NOTICE------------------------------------
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


#include "keyboard.h"
#include "../text/text.h"

//////////////////////////////////////////////////////////////////
// wait4UserKeypress
//    Waits till the user presses a key, counting the number of
// loop iterations passed.
//
// Returns:
//    <u32> Number of iterations passed
//
u32 wait4UserKeypress() {
    u32 c = 0;     // Count the number of cycles passed till user k

    // Wait 'till the user presses a key, counting loop iterations
    do {
        c++;                       // One more cycle
        cpct_scanKeyboard_f();     // Scan the scan the keyboard
    } while ( ! cpct_isAnyKeyPressed_f() );

    return c;
}

//Función proporcionada por ronaldo para redefinición de teclas
cpct_keyID esperaUnaTecla() {
    // Recorreremos el vector de teclas desde el final hacia el principio,
    // para poder hacer que el bucle acabe en 0 (así el compilador podrá optimizarlo)
    u8 i = 10, *keys = cpct_keyboardStatusBuffer + 9;
    u16 keypressed;

    // Esperamos hasta que se pulse una tecla
    do { cpct_scanKeyboard(); } while ( ! cpct_isAnyKeyPressed() );

    // Detectamos cuál tecla ha sido pulsada
    do {
        // Si en este grupo de 8 teclas hay una pulsada, alguno de los bits estará a 0
        // En caso contrario, todos estarán a 1, y un XOR con 0xFF dará 0 (false) como resultado
        keypressed = *keys ^ 0xFF;
        if (keypressed)
            return (keypressed << 8) + (i - 1);  // Formato cpct_keyID: 8 primeros bits = máscara de tecla, 8 siguientes fila del teclado (0-9)
        keys--;
    } while (--i);
    return (keypressed << 8) + (i - 1);
}

void waitKeyUp(cpct_keyID key){

    while (cpct_isKeyPressed(key)) {
        cpct_scanKeyboard_f();
    }
}

void wait4Key(cpct_keyID key){
    do
        cpct_scanKeyboard_f();
    while ( ! cpct_isKeyPressed(key) );
    do
        cpct_scanKeyboard_f();
    while ( cpct_isKeyPressed(key) );
}

cpct_keyID redefineKey(u8 text[]){
    u8 x;

    cpct_keyID key;

    u8* pvideo = cpct_getScreenPtr(CPCT_VMEM_START, 8, 154);
    cpct_drawSolidBox(pvideo, cpct_px2byteM0(0,0), 64, FONT_H);

    x = strlen(text);

    drawText(text, 8, 154,1);

    key = esperaUnaTecla();
    waitKeyUp(key);

    return key;

}