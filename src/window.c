#include "window.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* wind = NULL;
SDL_Renderer* rendr = NULL;

SDL_Rect darea;
SDL_Rect darea_top;
SDL_Rect darea_bottom;
SDL_Rect darea_left;
SDL_Rect darea_right;

void InitializeWindow() {
    wind = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, WINDOW_FLAGS);

    if (wind == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    rendr = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

    if (rendr == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    SaveWindowDimensions();
    TTF_Init();
}

void SaveWindowDimensions() {
    SDL_RenderGetViewport(rendr, &darea);
    darea_left = (SDL_Rect){darea.x - 100, darea.y, 100, darea.h};
    darea_right = (SDL_Rect){darea.w, darea.y, 100, darea.h};
    darea_top = (SDL_Rect){darea.x, darea.y - 100, darea.w, 100};
    darea_bottom = (SDL_Rect){darea.x, darea.h, darea.w, 100};
}

void DestroyWindow() {
    TTF_Quit();
    SDL_DestroyRenderer(rendr);
    SDL_DestroyWindow(wind);
}
