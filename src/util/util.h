#ifndef _UTIL_H_
#define _UTIL_H_

#include <cpctelera.h>

typedef struct{
    cpct_keyID up;
    cpct_keyID down;
    cpct_keyID left;
    cpct_keyID right;
    cpct_keyID fire1;
    cpct_keyID fire2;
    cpct_keyID pause;
    cpct_keyID abort;
    cpct_keyID music;
} TKeys;

u16 fast_abs(i16 value);
u8 fast_collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2);
void reset_cpc();

char* itoa(int value, char* result, int base);
void delay(u32 cycles);
u8 checkKeys(const cpct_keyID* k, u8 numk);
u8 hasReachedTarget(TEntity *e, u8 x, u8 y, i16 stepX, i16 stepY);
u16 distance (u16 x1, u16 y1, u16 x2, u16 y2);
i8 sign(i16 x);

#endif
