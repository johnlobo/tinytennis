#ifndef _PALETTE_H_
#define _PALETTE_H_

#include <types.h>

extern const u8 sp_palette[16];
extern const u8 colours[27];

void fadeIn(u8 palette[16]);
void fadeOut(u8 palette[16]);

#endif
