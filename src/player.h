#ifndef _PLAYER_H
#define _PLAYER_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>

typedef struct {
    SDL_Rect rect;
    int speed;
    int dir;
    int score;
} Player;

void PlayerInitialize(Player* p1, Player* p2);
bool paddleCollisionTop(Player* paddle);
bool paddleCollisionBottom(Player* paddle);
void paddleMoveUp(Player* paddle);
void paddleMoveDown(Player* paddle);

#endif
