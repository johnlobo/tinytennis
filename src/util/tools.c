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
#include "../defines.h"

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) {
    
    int tmp_value;
    char* ptr = result, *ptr1 = result, tmp_char;
    
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }
    
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );
    
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

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

u8 hasReachedTarget(TEntity *e, u8 x, u8 y){
    u8 posX0, posY0;
    u8 posX1, posY1;

    posX0 = e->x[0] / SCALE;
    posY0 = e->y[0] / SCALE;
    posX1 = (e->x[0] + e->hstep) / SCALE;
    posY1 = (e->y[0] + e->vstep) / SCALE;

    return (((posX0 <= x <= posX1 ) || (posX0 >= x >= posX1)) && ((posY0 <= y <= posY1) || (posY0 >= y >= posY1)));
}

u8 distance (u8 x1, u8 y1, u8 x2, u8 y2){
  u8 x = abs( x2 - x1 );  // x = valor absoluto de x2 – x1, es decir, la distancia entre las x
  u8 y = abs( y2 - y1 );  // y = valor absoluto de y2 – y1, es decir, la distancia entre las y

  u8 min = x < y ? x : y; // Si x < y min = x, si no, vale y. Es decir, el menor de los 2

  return ( x+y - (min>>1) - (min>>2) + (min>>4) );
}
