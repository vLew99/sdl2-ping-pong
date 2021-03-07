#ifndef _PLAYER_H
#define _PLAYER_H

#define PLAYER_PADDLE_WIDTH 20
#define PLAYER_PADDLE_HEIGHT 160
#define PLAYER_PADDLE_SPEED 30

typedef struct
{
    SDL_Rect rect;
    int speed;
    int dir;
    int score;
} Player;


Player p1;
Player p2;

void createPlayer() {
    p1.rect.w = PLAYER_PADDLE_WIDTH;
    p1.rect.h = PLAYER_PADDLE_HEIGHT;
    p1.rect.x = PLAYER_PADDLE_WIDTH;
    p1.rect.y = WINDOW_HEIGHT/2 - (PLAYER_PADDLE_HEIGHT/2);
    p1.speed = PLAYER_PADDLE_SPEED;
    
    p2.rect.w = PLAYER_PADDLE_WIDTH;
    p2.rect.h = PLAYER_PADDLE_HEIGHT;
    p2.rect.x = WINDOW_WIDTH - 2*PLAYER_PADDLE_WIDTH;
    p2.rect.y = WINDOW_HEIGHT/2 - (PLAYER_PADDLE_HEIGHT/2);
    p2.speed = PLAYER_PADDLE_SPEED;
}

bool paddleCollisionTop(Player *paddle) {
    return SDL_HasIntersection(&paddle->rect, &darea_top);
}

bool paddleCollisionBottom(Player *paddle) {
    return SDL_HasIntersection(&paddle->rect, &darea_bottom);
}

void paddleMoveUp(Player *paddle) {
    paddle->rect.y -= paddle->speed;
    if(paddleCollisionTop(paddle)) paddle->rect.y = 0;
}

void paddleMoveDown(Player *paddle) {
    paddle->rect.y += paddle->speed;
    if(paddleCollisionBottom(paddle)) paddle->rect.y = WINDOW_HEIGHT-PLAYER_PADDLE_HEIGHT;
}

#endif