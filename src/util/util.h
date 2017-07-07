#ifndef _UTIL_H_
#define _UTIL_H_

#include <cpctelera.h>

typedef struct{
    cpct_keyID up;
    cpct_keyID down;
    cpct_keyID left;
    cpct_keyID right;
    cpct_keyID fire;
    cpct_keyID pause;
    cpct_keyID abort;
    cpct_keyID music;
} TKeys;

u8 fast_collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2);
void reset_cpc();

char* itoa(int value, char* result, int base);
void delay(u32 cycles);
u8 checkKeys(const cpct_keyID* k, u8 numk);

#endif
