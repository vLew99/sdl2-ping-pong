#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tgmath.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "player.h"
#define FPS 75

bool gameClose = false;

SDL_Rect darea;
SDL_Rect darea_top;
SDL_Rect darea_bottom;
SDL_Rect darea_left;
SDL_Rect darea_right;

bool flag = false;

int frameCount;
int timerFPS;
int lastFrame;
int fps;



void reset() {
    createPlayer();
    createBall(&darea);
    SDL_Delay(1000);
}



bool ballCollision(Ball *ball) {
    if(SDL_HasIntersection(&ball->rect, &darea_top) || SDL_HasIntersection(&ball->rect, &darea_bottom)){
        b1.speedY *= -1;
        return true;
    }
    if(SDL_HasIntersection(&ball->rect, &darea_left) ){
        printf("1 wins!\n");
        reset();
        return true;
    }

    if(SDL_HasIntersection(&ball->rect, &darea_right)){
        printf("2 wins!\n");
        reset();
        return true;
    }

    if(SDL_HasIntersection(&ball->rect, &p1.rect)){
        ball->speedX *= -1;
        ball->speedY += p1.dir*0.2*p1.speed*(-1);
        return true;
    }

    if(SDL_HasIntersection(&ball->rect, &p2.rect)){
        ball->speedX *= -1;
        ball->speedY += p2.dir*0.2*p2.speed*(-1);
        return true;
    }
    return false;
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


void events() {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            gameClose = true;

    if (keystates[SDL_SCANCODE_ESCAPE])
        gameClose = true;
    if (keystates[SDL_SCANCODE_W])
    {
        paddleMoveUp(&p1);
    }
    if (keystates[SDL_SCANCODE_S])
    {
        paddleMoveDown(&p1);
    }
    if (keystates[SDL_SCANCODE_UP])
    {
        paddleMoveUp(&p2);
    }
    if (keystates[SDL_SCANCODE_DOWN])
    {
        paddleMoveDown(&p2);
    }
}

void render()
{
    SDL_SetRenderDrawColor(rendr, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(rendr);

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / FPS))
    {
        SDL_Delay((1000 / FPS) - timerFPS);
    }

    SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 255);

    SDL_RenderCopy(rendr, p1.texture, NULL, &p1.rect);
    SDL_RenderCopyEx(rendr, p2.texture, NULL, &p2.rect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    // SDL_RenderFillRect(rendr, &p1.rect);
    // SDL_RenderFillRect(rendr, &p2.rect);
    SDL_RenderCopy(rendr, b1.texture, NULL, &b1.rect);
    SDL_RenderPresent(rendr);
}



void update() {
    ballCollision(&b1);
    b1.rect.x += b1.speedX;
    b1.rect.y += b1.speedY;
    // printf("%d, %d, %d, %d \n", p1.rect.x, p1.rect.y, p1.rect.w, p1.rect.h);
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

    srand(time(NULL));

    SDL_RenderGetViewport(rendr, &darea);
    darea_left = (SDL_Rect){darea.x - 100, darea.y, 100, darea.h};
    darea_right = (SDL_Rect){darea.w, darea.y, 100, darea.h};
    darea_top = (SDL_Rect){darea.x, darea.y - 100, darea.w, 100};
    darea_bottom = (SDL_Rect){darea.x, darea.h, darea.w, 100};

    createBall(&darea);
    createPlayer();

    game_loop();

    deleteTextures();

    deinitialising();

    SDL_Quit();
    return 0;
}