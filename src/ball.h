#ifndef _BALL_H_INCLUDED
#define _BALL_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "define.h"
#include "player.h"
#include "window.h"

typedef struct {
    SDL_Rect rect;
    float speedX;
    float speedY;
    bool prev_collision;
} Ball;

void BallInitialize(Ball* ball);
bool ballPaddleCollision(Ball* ball, Player* paddle);
bool ballCollision(Player* p1, Player* p2, Ball* ball);
void ballMove(Player* p1, Player* p2, Ball* ball);
#endif
