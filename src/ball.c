#include "ball.h"

#include <SDL2/SDL_rect.h>

#include "game.h"

extern SDL_Rect darea;
extern SDL_Rect darea_top;
extern SDL_Rect darea_left;
extern SDL_Rect darea_right;
extern SDL_Rect darea_bottom;

void BallInitialize(Ball* ball) {
    int initial_speeds[] = {-7, -6, -5, -4, 4, 5, 6, 7};
    *(ball) = (Ball){.rect.x = darea.w / 2,
                     .rect.y = darea.h / 2,
                     .rect.w = BALL_SIZE,
                     .rect.h = BALL_SIZE,
                     .speedX = initial_speeds[rand() % 8] * BALL_SPEED,
                     .speedY = initial_speeds[rand() % 8] * BALL_SPEED,
                     .prev_collision = false};
}

bool ballPaddleCollision(Ball* ball, Player* paddle) {
    if (!ball->prev_collision) ball->speedX *= -1;
    if (abs(paddle->dir * 7) > abs(paddle->dir * paddle->speed * 0.5))
        ball->speedY += paddle->dir * paddle->speed * 0.5;
    else
        ball->speedY += 0;
    return true;
}

bool ballCollision(Player* p1, Player* p2, Ball* ball) {
    if (SDL_HasIntersection(&ball->rect, &darea_top) ||
        SDL_HasIntersection(&ball->rect, &darea_bottom)) {
        ball->speedY *= -1;
    }
    if (SDL_HasIntersection(&ball->rect, &darea_left)) {
        printf("1 wins!\n");
        p1->score++;
        gameReset(p1, p2, ball);
    }

    if (SDL_HasIntersection(&ball->rect, &darea_right)) {
        printf("2 wins!\n");
        p2->score++;
        gameReset(p1, p2, ball);
    }

    if (SDL_HasIntersection(&ball->rect, &p1->rect)) {
        return ballPaddleCollision(ball, p1);
    }

    if (SDL_HasIntersection(&ball->rect, &p2->rect)) {
        return ballPaddleCollision(ball, p2);
    }
    return false;
}

void ballMove(Player* p1, Player* p2, Ball* b1) {
    b1->prev_collision = ballCollision(p1, p2, b1);
    b1->rect.x += b1->speedX;
    b1->rect.y += b1->speedY;
}
