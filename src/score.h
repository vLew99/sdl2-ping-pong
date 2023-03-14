#ifndef _SCORE_HEADER
#define _SCORE_HEADER

#include <SDL2/SDL_rect.h>
void InitializeScore(char* fontName);

void ScoreRender(int score, int score2);
void ScoreTestRender();

void ScoreDestroy();

#endif  // _SCORE_HEADER
