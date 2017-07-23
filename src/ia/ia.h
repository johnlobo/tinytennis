#ifndef _IA_H_
#define _IA_H_

#include "../entities/TPlayer.h"
#include "../entities/TBall.h"

#define TARGET_CENTER_X 40
#define TARGET_CENTER_Y 20


void initIAPlayer(TPlayer *player);
void executeStateIA(TPlayer *player, TBall *ball); 

#endif