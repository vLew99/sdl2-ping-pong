#ifndef _GAME_HEADER_
#define _GAME_HEADER_

#include "ball.h"
#include "player.h"

void gameReset(Player* p1, Player* p2, Ball* ball);
void gameLoop(Player* p1, Player* p2, Ball* ball);

void render(Player* p1, Player* p2, Ball* ball);
void update(Player* p1, Player* p2, Ball* ball);
void events(Player*, Player*);

#endif  // _GAME_HEADER_
