#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tgmath.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "define.h"
#include "window.h"
#include "player.h"
#include "ball.h"

#define FPS 75

bool gameClose = false;

int frameCount;
int timerFPS;
int lastFrame;
int fps;


void events() {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            gameClose = true;

    p1.dir = 0;
    p2.dir = 0;
    
    if (keystates[SDL_SCANCODE_ESCAPE])
        gameClose = true;
    if (keystates[SDL_SCANCODE_W])
    {
        p1.dir = -1;
        paddleMoveUp(&p1);
    }
    if (keystates[SDL_SCANCODE_S])
    {
        p1.dir = 1;
        paddleMoveDown(&p1);
    }
    if (keystates[SDL_SCANCODE_UP])
    {
        p2.dir = -1;
        paddleMoveUp(&p2);
    }
    if (keystates[SDL_SCANCODE_DOWN])
    {
        p1.dir = 1;
        paddleMoveDown(&p2);
    }
}

void render() {
    SDL_SetRenderDrawColor(rendr, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(rendr);

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / FPS))
    {
        SDL_Delay((1000 / FPS) - timerFPS);
    }

    SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 255);
    SDL_RenderFillRect(rendr, &p1.rect);
    SDL_RenderFillRect(rendr, &p2.rect);
    SDL_RenderFillRect(rendr, &b1.rect);
    SDL_RenderPresent(rendr);
}



void update() {
    ballMove();
}

void game_loop()
{
    static int lastTime = 0;
    while (!gameClose)
    {

        lastFrame = SDL_GetTicks();
        if (lastFrame >= (lastTime + 1000))
        {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }
        events();
        update();
        render();
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    initialising();

    int t = time(0);
    srand(t);

    SDL_RenderGetViewport(rendr, &darea);
    darea_left = (SDL_Rect){darea.x - 100, darea.y, 100, darea.h};
    darea_right = (SDL_Rect){darea.w, darea.y, 100, darea.h};
    darea_top = (SDL_Rect){darea.x, darea.y - 100, darea.w, 100};
    darea_bottom = (SDL_Rect){darea.x, darea.h, darea.w, 100};

    createBall();
    createPlayer();

    game_loop();

    deinitialising();

    printf("Player 1 -> %d\n", p1.score);
    printf("Player 2 -> %d\n", p2.score);

    SDL_Quit();
    return 0;
}