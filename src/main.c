#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "ball.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "window.h"

bool gameClose = false;
int frameCount;
int timerFPS;
int lastFrame;
int fps;

void InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error: %s", SDL_GetError());
        exit(-1);
    }
}

void InitializeGameItems(Player* player1, Player* player2, Ball* ball1) {
    PlayerInitialize(player1, player2);
    BallInitialize(ball1);
    InitializeScore("assets/SuboleyaRegular-qZeV1.ttf");
}

void DestroyGameItems() { ScoreDestroy(); }

void InitMain() { InitializeWindow(); }

int main() {
    Player p1, p2;
    Ball b1;
    InitializeSDL();
    InitializeWindow();
    InitializeGameItems(&p1, &p2, &b1);
    int currTime = time(0);
    srand(currTime);
    gameLoop(&p1, &p2, &b1);
    DestroyGameItems();
    DestroyWindow();
    SDL_Quit();
    return 0;
}
