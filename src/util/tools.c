#include <cpctelera.h>
#include "../defines.h"
#include "util.h"
#include "../sprites/border.h"

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char *itoa(int value, char *result, int base)
{

    int tmp_value;
    char *ptr = result, *ptr1 = result, tmp_char;

    // check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    }
    while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

//////////////////////////////////////////////////////////////////
// delay
//
//    Wait for an specific number of cycles
//
//
// Returns:
//    void
//
void delay(u32 cycles)
{
    u32 i;
    for (i = 0; i < cycles; i++)
    {
        __asm
        halt
        __endasm;
    }
}

//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    

u8 hasReachedTarget(TEntity *e, u8 x, u8 y, i16 stepX, i16 stepY)
{
    return (fast_abs(e->x[0] - x) <= fast_abs(stepX / SCALE)) && (fast_abs(e->y[0] - y) <= fast_abs(stepY / SCALE));
}
//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    

u16 distance (u16 x1, u16 y1, u16 x2, u16 y2)
{
    u16 x = fast_abs( x2 - x1 );  // x = valor absoluto de x2 – x1, es decir, la distancia entre las x
    u16 y = fast_abs( y2 - y1 );  // y = valor absoluto de y2 – y1, es decir, la distancia entre las y

    u16 min = x < y ? x : y; // Si x < y min = x, si no, vale y. Es decir, el menor de los 2

    return ( x + y - (min >> 1) - (min >> 2) + (min >> 4) );
}
//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    

i16 sign(i16 x)
{
    return  (x > 0) - (x < 0);
}


//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    

u8 collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2)
{
    return  ((x1 < x2 + w2) && (x1 + w1 > x2) &&  (y1 < y2 + h2) && (h1 + y1 > y2));
}

//////////////////////////////////////////////////////////////////
// Name
//
//    Descriptio
//
//
// Returns:
//    
i16 abs(i16 j)
{
    return (j < 0) ? -j : j;
}

//////////////////////////////////////////////////////////////////
// clearScreen
//
//
//
// Returns:
//    void
//

void clearScreen() {
    // Clear Screen
    cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(0,0), 0x4000);
}

//////////////////////////////////////////////////////////////////
// clearWindow
//
//
//
// Returns:
//    void
//

void clearWindow(u8 xPos, u8 yPos, u8 width, u8 height) {

    u8* pvideo = cpct_getScreenPtr(CPCT_VMEM_START, xPos, yPos);
    cpct_drawSolidBox(pvideo, cpct_px2byteM0(0,0), width, height);

}

/////////////////////////////////////////////////////////////////
// drawFrame
//
//
//
// Returns:
//    void
//

void drawFrame(u8 x1, u8 y1, u8 x2, u8 y2) {
    u8 *pvideo;
    u8 x, frame_w, frame_h;

    frame_w = x2 - x1;
    frame_h = y2 - y1;

    clearWindow(x1, y1, x2 - x1, y2 - y1);

    //UPLEFTCORNER
    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x1, y1);
    cpct_drawSprite(g_border_0,  pvideo, 2, 4);

    //UPPER BAR
    for (x = x1 + 2; x < (x2 - 2); x = x + 2) {
        cpct_drawSprite(g_border_4,  pvideo + (x - x1), 2, 4);
    }

    //UPRIGHTCORNER
    cpct_drawSprite(g_border_1,  pvideo + (frame_w - 2), 2, 4);

    //LEFT & RIGHT BARS
    for (x = y1 + 4; x < (y2 - 4); x = x + 4) {
        pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x1, x);
        cpct_drawSprite(g_border_5,  pvideo, 2, 4);
        cpct_drawSprite(g_border_6,  pvideo + (frame_w - 2), 2, 4);
    }

    pvideo = cpct_getScreenPtr(CPCT_VMEM_START, x1, y2 - 4);

    //DOWNLEFTCORNER
    cpct_drawSprite(g_border_2,  pvideo, 2, 4);

    //LOWER BAR
    for (x = x1 + 2; x < (x2 - 2); x = x + 2) {
        cpct_drawSprite(g_border_7,  pvideo + (x - x1), 2, 4);
    }

    //DOWNRIGHTCORNER
    cpct_drawSprite(g_border_3,  pvideo + (frame_w - 2), 2, 4);
}


