#include "game.h"

extern bool gameClose;
extern int frameCount;
extern int timerFPS;
extern int lastFrame;
extern int fps;

extern SDL_Window* wind;
extern SDL_Renderer* rendr;

void gameLoop(Player* p1, Player* p2, Ball* b1) {
    static int lastTime = 0;
    while (!gameClose) {
        lastFrame = SDL_GetTicks();
        if (lastFrame >= (lastTime + 1000)) {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }
        events(p1, p2);
        update(p1, p2, b1);
        render(p1, p2, b1);
    }
}

void gameReset(Player* p1, Player* p2, Ball* ball) {
    PlayerInitialize(p1, p2);
    BallInitialize(ball);
    SDL_Delay(1000);
}

void events(Player* p1, Player* p2) {
    SDL_Event e;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) gameClose = true;

    p1->dir = 0;
    p2->dir = 0;

    if (keystates[SDL_SCANCODE_ESCAPE]) gameClose = true;
    if (keystates[SDL_SCANCODE_W]) {
        p1->dir = -1;
        paddleMoveUp(p1);
    }
    if (keystates[SDL_SCANCODE_S]) {
        p1->dir = 1;
        paddleMoveDown(p1);
    }
    if (keystates[SDL_SCANCODE_UP]) {
        p2->dir = -1;
        paddleMoveUp(p2);
    }
    if (keystates[SDL_SCANCODE_DOWN]) {
        p1->dir = 1;
        paddleMoveDown(p2);
    }
}

void render(Player* p1, Player* p2, Ball* b1) {
    SDL_SetRenderDrawColor(rendr, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(rendr);

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / FPS)) {
        SDL_Delay((1000 / FPS) - timerFPS);
    }

    SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 255);
    SDL_RenderFillRect(rendr, &p1->rect);
    SDL_RenderFillRect(rendr, &p2->rect);
    SDL_RenderFillRect(rendr, &b1->rect);
    SDL_RenderPresent(rendr);
}

void update(Player* p1, Player* p2, Ball* b1) { ballMove(p1, p2, b1); }
