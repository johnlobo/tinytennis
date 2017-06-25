//////////////////////////////////////////////////////////////////
// delay
//
//    Wait for an specific number of cycles
//
//
// Returns:
//    void
//
#include <cpctelera.h>
#include "../main.h"

void delay(u32 cycles) {
    u32 i;
    for (i = 0; i < cycles; i++) {
        __asm
        halt
        __endasm;
    }
}

u8 checkKeys(const cpct_keyID* k, u8 numk) {
    u8 i;
//   cpct_scanKeyboard_if();
    if (cpct_isAnyKeyPressed()) {
        for (i = 1; i <= numk; i++, k++) {
            if (cpct_isKeyPressed(*k))
                return i;
        }
    }
    return 0;
}
