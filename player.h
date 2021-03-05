#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    int speed;
} Ball;

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int speed;
} Player;




Player p1;
Player p2;

Ball b1;

void ballMovement() {

}

void createPlayer() {
    p1 = (Player){
        .rect.w = 20,
        .rect.h = 80,
        .rect.x = 0,
        .rect.y = 0,
        .speed = 20,
        .texture = SDL_CreateTextureFromSurface(rendr,IMG_Load("assets/bar.png"))
    };

    p2 = (Player){
        .rect.w = 20,
        .rect.h = 80,
        .rect.x = WINDOW_WIDTH - 20,
        .rect.y = 0,
        .speed = 20,
        .texture = SDL_CreateTextureFromSurface(rendr, IMG_Load("assets/bar.png"))
    };
}

void createBall(SDL_Rect *darea) {
    b1 = (Ball) {
        .rect.x = darea->w/2,
        .rect.y = darea->h/2,
        .rect.w = 10,
        .rect.h = 10,
        .speed = 20,
        .texture = SDL_CreateTextureFromSurface(rendr, IMG_Load("assets/player.png"))
    };
}

void deleteTextures() {
    SDL_DestroyTexture(p1.texture);
    SDL_DestroyTexture(p2.texture);
    SDL_DestroyTexture(b1.texture);
}
#endif