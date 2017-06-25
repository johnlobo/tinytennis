#ifndef _UTIL_H_
#define _UTIL_H_

#include <types.h>

typedef struct{
    cpct_keyID up;
    cpct_keyID down;
    cpct_keyID left;
    cpct_keyID right;
    cpct_keyID fire;
    cpct_keyID pause;
    cpct_keyID abort;
    cpct_keyID music;
    cpct_keyID camelotmode;
} TKeys;

extern TKeys keys;

void delay(u32 cycles);
u8 checkKeys(const cpct_keyID* k, u8 numk);

#endif
