#ifndef _DEFINE_H_INCLUDED_
#define _DEFINE_H_INCLUDED_

// window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FLAGS (SDL_WINDOW_OPENGL)
#define RENDERER_FLADS (SDL_REDNERER_ACCELERATED)


// player
#define PLAYER_PADDLE_WIDTH 20
#define PLAYER_PADDLE_HEIGHT 160
#define PLAYER_PADDLE_SPEED 30

// ball
#define BALL_SIZE 15
#define BALL_SPEED 1.5

// some functions
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : (-1*a))


#endif