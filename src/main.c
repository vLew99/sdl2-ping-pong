#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "ball.h"
#include "game.h"
#include "player.h"
#include "window.h"

bool gameClose = false;
int frameCount;
int timerFPS;
int lastFrame;
int fps;

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    WindowInit();

    Player p1;
    Player p2;
    Ball b1;

    int t = time(0);
    srand(t);

    PlayerInitialize(&p1, &p2);
    BallInitialize(&b1);

    gameLoop(&p1, &p2, &b1);

    WindowDestroy();

    printf("Player 1 -> %d\n", p1.score);
    printf("Player 2 -> %d\n", p2.score);

    SDL_Quit();
    return 0;
}
