#include "ia.h"
#include "../entities/TPlayer.h"
#include "../sprites/player1.h"

const TPlayer tempIAPlayer =
{
	{	{ 40 * SCALE, 40 * SCALE }
		, 	{ 10 * SCALE, 10 * SCALE }
		, 	{ 0, 0 }
		,	PLAYER_WIDTH, PLAYER_HEIGHT
		,   256, 512
		,	&g_frames[12]
		,	0
		,	M_right
		,	2
	}
	,	GM_play
	,	ST_stopped
	,	SD_up
	,	0
	,	ST_IAstopped
	, {
		255, 512, 255, 255 // Character definition

	}
	, 0, 0  // targetX and targetY
	, 0, 0	// stepX and stepY
};

void initIAPlayer(TPlayer *player) {
	cpct_memcpy(player, &tempIAPlayer, sizeof(TPlayer));
}

void IAHitting(TPlayer *player, TBall *ball) {
}

void IAMovingToTarget(TPlayer *player, TBall *ball) {
	u8 posX, posY;

	posX = player->e.x[0] / SCALE;
	posY = player->e.y[0] / SCALE;

	if (hasReachedTarget(&player->e, player->targetX, player->targetY)) {
		player->iaState = ST_stopped;
	} else {
		if (posX < player->targetX) {
			moveRight(player);
			walking_animate(M_right, player);
		} else if (posX > player->targetX) {
			moveLeft(player);
			walking_animate(M_left, player);
		}
		if (posY < player->targetY) {
			moveDown(player);
			down_animate(player);
		} else {
			moveUp(player);
			up_animate(player);
		}
		player->e.draw = 1;
	}
}


void setIATarget(u8 x, u8 y, TPlayer *player){
	i16 distX, distY;
	i16 t, stX, stY;

	player->targetX = x;
	player->targetY = y;
	// Calculate the steps to target
	distX = x - player->e.x;  	//distance X
	distY = y - player->e.y;  	//distance Y
	t = max((abs(distX)/player->car.speedX), (abs(distY)/player->car.speedY));  // # of steps
	stX = distX / t; 			// size of step X
	stY = distY / t;			// size of step Y
	// Set the steps to target 
	if (player->car.speedX<stX){
		player->stepX = player->car.speedX;
	}else{
		player->stepX = stX;
	}
	if (player->car.speedY<stY){
		player->stepY = player->car.speedY;
	}else{
		player->stepY = stY;
	}
	// Set IA state
	player->iaState = IAMovingToTarget;
}

void IAStopped(TPlayer *player, TBall *ball)
{
	if (!hasReachedTarget(&player->e, TARGET_CENTER_X, TARGET_CENTER_Y) && (ball->vy < 0)) {
		player->targetX = TARGET_CENTER_X;
		player->targetY = TARGET_CENTER_Y;
		player->state = ST_walking;
	} else if (ball->vy < 0) {
		player->targetX = ball->bouncex + ball->vx;
		player->targetY = ball->bouncey + ball->vy;
		player->state = ST_walking;
	}
}

void executeStateIA(TPlayer *player, TBall *ball)
{
	switch (player->iaState)
	{
	case ST_IAStopped:
		IAStopped(player, ball);
		break;
	case ST_IAMovingToTarget:
		IAMovingToTarget(player, ball);
		break;
	case ST_IAHitting:
		IAHitting(player, ball);
		break;
	}
}