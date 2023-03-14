#include "score.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

#include "define.h"

TTF_Font* font;
int digits_texture_width;
int digits_texture_height;

extern SDL_Renderer* rendr;

SDL_Texture* player1Texture;
SDL_Texture* player2Texture;
SDL_Texture* timeTexture;

void InitializeScore(char* fontName) {
    font = TTF_OpenFontDPI(fontName, SCORE_FONT_SIZE, SCORE_FONT_DPI,
                           SCORE_FONT_DPI);
    TTF_SetFontHinting(font, TTF_HINTING_LIGHT_SUBPIXEL);
    if (font == NULL) printf("Font \"%s\" not opened\n", fontName);
}

/* void ScoreTestRender() { SDL_RenderCopy(rendr, digits_texture, NULL, NULL); }
 */

void ScoreRender(int score1, int score2) {
    char scoreText[4];
    sprintf(scoreText, "%d", score1);

    SDL_Surface* tempSurface = TTF_RenderText_Shaded(
        font, scoreText, (SDL_Color){0xff, 0xff, 0xff, 0xff},
        (SDL_Color){0x00, 0x00, 0x00, 0x00});
    SDL_Texture* digits_texture =
        SDL_CreateTextureFromSurface(rendr, tempSurface);
    SDL_QueryTexture(digits_texture, NULL, NULL, &digits_texture_width,
                     &digits_texture_height);

    SDL_FRect scoreLocation = (SDL_FRect){
        .x = ((float)WINDOW_WIDTH / 2) - ((float)digits_texture_width / 2) -
             SCORE_OFFSET_MIDDLE,
        .y = SCORE_POS_TOP,
        .w = digits_texture_width,
        .h = digits_texture_height};
    SDL_FreeSurface(tempSurface);
    SDL_RenderCopyF(rendr, digits_texture, NULL, &scoreLocation);
    SDL_DestroyTexture(digits_texture);

    sprintf(scoreText, "%d", score2);

    tempSurface = TTF_RenderText_Shaded(font, scoreText,
                                        (SDL_Color){0xff, 0xff, 0xff, 0xff},
                                        (SDL_Color){0x00, 0x00, 0x00, 0x00});
    digits_texture = SDL_CreateTextureFromSurface(rendr, tempSurface);
    SDL_QueryTexture(digits_texture, NULL, NULL, &digits_texture_width,
                     &digits_texture_height);
    scoreLocation =
        (SDL_FRect){.x = ((float)WINDOW_WIDTH / 2) + SCORE_OFFSET_MIDDLE -
                         ((float)digits_texture_width / 2),
                    .y = SCORE_POS_TOP,
                    .w = digits_texture_width,
                    .h = digits_texture_height};
    SDL_FreeSurface(tempSurface);
    SDL_RenderCopyF(rendr, digits_texture, NULL, &scoreLocation);
    SDL_DestroyTexture(digits_texture);
}

void ScoreDestroy() {
    TTF_CloseFont(font);
    /* SDL_DestroyTexture(digits_texture); */
    printf("Font Destroyed\n");
}
