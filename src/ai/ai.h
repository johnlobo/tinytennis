#ifndef _AI_H_
#define _AI_H_

#include "../entities/TPlayer.h"
#include "../entities/TBall.h"

#define TARGET_CENTER_X 40
#define TARGET_CENTER_Y 20


void initAIPlayer(TPlayer *player);
void setAITarget(u8 x, u8 y, TPlayer *player);
void executeStateAI(TPlayer *player, TBall *ball); 

#endif