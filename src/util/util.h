#ifndef _UTIL_H_
#define _UTIL_H_

#include <cpctelera.h>


u16 fast_abs(i16 value);
u8 fast_collision(u8 x1, u8 y1, u8 w1, u8 h1, u8 x2, u8 y2, u8 w2, u8 h2);
void reset_cpc();

char *itoa(int value, char *result, int base);
void delay(u32 cycles);
u8 hasReachedTarget(TEntity *e, u8 x, u8 y, i16 stepX, i16 stepY);
u16 distance (u16 x1, u16 y1, u16 x2, u16 y2);
i16 sign(i16 x);

#endif
