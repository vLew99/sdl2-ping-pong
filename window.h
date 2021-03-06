#ifndef _WINDOW_H
#define _WINDOW_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

SDL_Window *wind = NULL;
SDL_Renderer *rendr = NULL;

void initialising(){
    wind = SDL_CreateWindow(
        "game1",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
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