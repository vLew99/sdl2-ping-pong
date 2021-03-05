#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tgmath.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "player.h"

SDL_Event e;
bool gameClose = false;

SDL_Rect darea;
SDL_Rect darea_top;
SDL_Rect darea_bottom;
SDL_Rect darea_left;
SDL_Rect darea_right;

bool flag = false;

int frameCount, timerFPS, lastFrame, fps;

int angle = 90;
// const SDL_Point new = (SDL_Point){0, 0};
SDL_Point calculatePoint(int angle, double distance, SDL_Rect start)
{
    SDL_Point end;
    end.x = start.x + SDL_cos((double)angle) * distance;
    end.y = start.y - SDL_sin((double)angle) * distance;
    return end;
}

bool checkCollision(SDL_Rect *currRect)
{

    SDL_Rect *rectsArray[] = {
        &b1.rect,
        &darea_bottom,
        &darea_top,
        &darea_left,
        &darea_right,
        &p1.rect,
        &p2.rect};

    for (size_t i = 0; i < (sizeof(rectsArray) / sizeof(rectsArray[0])); ++i)
    {
        if (SDL_RectEquals(currRect, rectsArray[i]))
        {
            continue;
        }
        else if (SDL_HasIntersection(currRect, rectsArray[i]))
        {
            return true;
        }
    }
    return false;
}


void events()
{

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            gameClose = true;

    if (keystates[SDL_SCANCODE_ESCAPE])
        gameClose = true;
    if (keystates[SDL_SCANCODE_W])
    {
        p1.rect.y -= p1.speed;
        if (checkCollision(&p1.rect))
            p1.rect.y += p1.speed;
    }
    if (keystates[SDL_SCANCODE_S])
    {
        p1.rect.y += p1.speed;
        if (checkCollision(&p1.rect))
            p1.rect.y -= p1.speed;
    }
    if (keystates[SDL_SCANCODE_UP])
    {
        p2.rect.y -= p2.speed;
        if (checkCollision(&p2.rect))
            p2.rect.y += p2.speed;
    }
    if (keystates[SDL_SCANCODE_DOWN])
    {
        p2.rect.y += p2.speed;
        if (checkCollision(&p2.rect))
            p2.rect.y -= p2.speed;
    }
}

void render()
{
    SDL_SetRenderDrawColor(rendr, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(rendr);

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60))
    {
        SDL_Delay((1000 / 60) - timerFPS);
    }

    SDL_SetRenderDrawColor(rendr, 0x00, 0x00, 0x00, 255);

    SDL_RenderCopy(rendr, p1.texture, NULL, &p1.rect);
    SDL_RenderCopyEx(rendr, p2.texture, NULL, &p2.rect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    SDL_RenderCopy(rendr, b1.texture, NULL, &b1.rect);
    SDL_RenderPresent(rendr);
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
        render();

        // if(checkCollision(&b1.rect)){
        //     angle = -angle;

        //     printf("angle - %f -collision!\n", angle);
        //     b1.rect.x = x;
        //     b1.rect.y = y;
        // }
        // else{

        // }
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    initialising();

    SDL_RenderGetViewport(rendr, &darea);
    darea_left = (SDL_Rect){darea.x - 1, darea.y, 1, darea.h};
    darea_right = (SDL_Rect){darea.w, darea.y, 1, darea.h};
    darea_top = (SDL_Rect){darea.x, darea.y - 1, darea.w, 1};
    darea_bottom = (SDL_Rect){darea.x, darea.h, darea.w, 1};

    createBall(&darea);
    createPlayer();

    game_loop();

    deleteTextures();

    deinitialising();

    SDL_Quit();
    return 0;
}