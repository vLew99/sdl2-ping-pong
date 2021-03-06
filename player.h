#ifndef _PLAYER_H
#define _PLAYER_H

#define BALL_SIZE 10
#define PLAYER_PADDLE_WIDTH 20
#define PLAYER_PADDLE_HEIGHT 160
#define PLAYER_PADDLE_SPEED 30


typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    float speedX;
    float speedY;
} Ball;

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int speed;
    int dir;
} Player;


Player p1;
Player p2;

Ball b1;


int speeds[] = {
    -7, -6, -5, -4, 4, 5, 6, 7
};

void createPlayer() {
    p1 = (Player){
        .rect.w = PLAYER_PADDLE_WIDTH,
        .rect.h = PLAYER_PADDLE_HEIGHT,
        .rect.x = PLAYER_PADDLE_WIDTH,
        .rect.y = WINDOW_HEIGHT/2 - (PLAYER_PADDLE_HEIGHT/2),
        .speed = PLAYER_PADDLE_SPEED,
        .texture = SDL_CreateTextureFromSurface(rendr,IMG_Load("assets/bar.png"))
    };

    p2 = (Player){
        .rect.w = PLAYER_PADDLE_WIDTH,
        .rect.h = PLAYER_PADDLE_HEIGHT,
        .rect.x = WINDOW_WIDTH - 2*PLAYER_PADDLE_WIDTH,
        .rect.y = WINDOW_HEIGHT/2 - (PLAYER_PADDLE_HEIGHT/2),
        .speed = PLAYER_PADDLE_SPEED,
        .texture = SDL_CreateTextureFromSurface(rendr, IMG_Load("assets/bar.png"))
    };
}

void createBall(SDL_Rect *darea) {
    b1 = (Ball) {
        .rect.x = darea->w/2,
        .rect.y = darea->h/2,
        .rect.w = BALL_SIZE,
        .rect.h = BALL_SIZE,
        .speedX = speeds[rand()%8]*1.5,
        .speedY = speeds[rand()%8]*1.5,
        .texture = SDL_CreateTextureFromSurface(rendr, IMG_Load("assets/player.png"))
    };
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

void deleteTextures() {
    SDL_DestroyTexture(p1.texture);
    SDL_DestroyTexture(p2.texture);
    SDL_DestroyTexture(b1.texture);
}
#endif