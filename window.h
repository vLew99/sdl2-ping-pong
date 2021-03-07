#ifndef _WINDOW_H
#define _WINDOW_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL)
#define RENDERER_FLADS (SDL_REDNERER_ACCELERATED)


SDL_Window *wind = NULL;
SDL_Renderer *rendr = NULL;
SDL_Rect darea;
SDL_Rect darea_top;
SDL_Rect darea_bottom;
SDL_Rect darea_left;
SDL_Rect darea_right;

void initialising(){
    wind = SDL_CreateWindow(
        "game1",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        WINDOW_FLAGS
    );

    if(wind == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }
    
    rendr = SDL_CreateRenderer(
        wind,
        0,
        SDL_RENDERER_ACCELERATED
    );

    if(rendr == NULL){
        printf("%s\n", SDL_GetError());
        exit(1);
    }
}

void deinitialising(){
    SDL_DestroyRenderer(rendr);
    SDL_DestroyWindow(wind);
}

#endif