#include "player.h"

#include "define.h"
#include "window.h"

extern SDL_Rect darea_bottom, darea_top;

void PlayerInitialize(Player* p1, Player* p2) {
    p1->rect = (SDL_Rect){.w = PLAYER_PADDLE_WIDTH,
                          .h = PLAYER_PADDLE_HEIGHT,
                          .x = PLAYER_PADDLE_WIDTH,
                          .y = WINDOW_HEIGHT / 2 - (PLAYER_PADDLE_HEIGHT / 2)};
    p1->speed = PLAYER_PADDLE_SPEED;
    p1->dir = 0;
    p1->score = 0;
    p2->rect = (SDL_Rect){.w = PLAYER_PADDLE_WIDTH,
                          .h = PLAYER_PADDLE_HEIGHT,
                          .x = WINDOW_WIDTH - 2 * PLAYER_PADDLE_WIDTH,
                          .y = WINDOW_HEIGHT / 2 - (PLAYER_PADDLE_HEIGHT / 2)};
    p2->speed = PLAYER_PADDLE_SPEED;
    p2->dir = 0;
    p2->score = 0;
}

void PlayerReset(Player* p1, Player* p2) {
    p1->rect = (SDL_Rect){.w = PLAYER_PADDLE_WIDTH,
                          .h = PLAYER_PADDLE_HEIGHT,
                          .x = PLAYER_PADDLE_WIDTH,
                          .y = WINDOW_HEIGHT / 2 - (PLAYER_PADDLE_HEIGHT / 2)};
    p1->dir = 0;
    p2->rect = (SDL_Rect){.w = PLAYER_PADDLE_WIDTH,
                          .h = PLAYER_PADDLE_HEIGHT,
                          .x = WINDOW_WIDTH - 2 * PLAYER_PADDLE_WIDTH,
                          .y = WINDOW_HEIGHT / 2 - (PLAYER_PADDLE_HEIGHT / 2)};
    p2->dir = 0;
}

bool paddleCollisionTop(Player* paddle) {
    return SDL_HasIntersection(&paddle->rect, &darea_top);
}

bool paddleCollisionBottom(Player* paddle) {
    return SDL_HasIntersection(&paddle->rect, &darea_bottom);
}

void paddleMoveUp(Player* paddle) {
    paddle->rect.y -= paddle->speed;
    if (paddleCollisionTop(paddle)) paddle->rect.y = 0;
}

void paddleMoveDown(Player* paddle) {
    paddle->rect.y += paddle->speed;
    if (paddleCollisionBottom(paddle))
        paddle->rect.y = WINDOW_HEIGHT - PLAYER_PADDLE_HEIGHT;
}
