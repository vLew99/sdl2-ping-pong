#ifndef _BALL_H_INCLUDED
#define _BALL_H_INCLUDED

#define BALL_SIZE 15
#define BALL_SPEED 1.5

typedef struct {
    SDL_Rect rect;
    float speedX;
    float speedY;
    bool prev_collision;
} Ball;

Ball b1;

void createBall() {
    int speeds[] = {
    	-7, -6, -5, -4, 4, 5, 6, 7
	};
    b1 = (Ball) {
        .rect.x = darea.w/2,
        .rect.y = darea.h/2,
        .rect.w = BALL_SIZE,
        .rect.h = BALL_SIZE,
        .speedX = speeds[rand()%8]*BALL_SPEED,
        .speedY = speeds[rand()%8]*BALL_SPEED,
        .prev_collision = false
    };
}

void gameReset() {
    createPlayer();
    createBall();
    SDL_Delay(1000);
}


bool ballPaddleCollision(Ball *ball, Player *paddle) {
    if(!ball->prev_collision)
        ball->speedX *= -1;
    if(abs(paddle->dir*7) > abs(paddle->dir * paddle->speed * 0.3))
    	ball->speedY += paddle->dir * paddle->speed * 0.3;
   	else
   		ball->speedY += 0;
    return true;
}

bool ballCollision(Ball *ball) {
    if(SDL_HasIntersection(&ball->rect, &darea_top) || SDL_HasIntersection(&ball->rect, &darea_bottom)){
        b1.speedY *= -1;

    }
    if(SDL_HasIntersection(&ball->rect, &darea_left) ){
        printf("1 wins!\n");
        p1.score++;
        gameReset();
    }

    if(SDL_HasIntersection(&ball->rect, &darea_right)){
        printf("2 wins!\n");
        p2.score++;
        gameReset();
    }

    if(SDL_HasIntersection(&ball->rect, &p1.rect)){
	    return ballPaddleCollision(ball, &p1);
    }

    if(SDL_HasIntersection(&ball->rect, &p2.rect)){
	    return ballPaddleCollision(ball, &p2);
    }
    return false;
}


void ballMove() {
	b1.prev_collision = ballCollision(&b1);
    b1.rect.x += b1.speedX;
    b1.rect.y += b1.speedY;
}

#endif
