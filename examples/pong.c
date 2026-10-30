#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int x,y;
} Vec2i_t;

typedef struct {
    Vec2i_t position;
    int score;
} playerpaddle_t;

typedef struct {
    Vec2i_t position;
    Vec2i_t velocity;
} ball_t;

int main(void)
{
    #ifndef _WIN32
    setbuf(stdout, NULL);
    #endif

    displaycontext_t d = initdisplay(80,50);

    playerpaddle_t player1 = {
        .position = {0,0},
        .score = 0
    };
    playerpaddle_t player2 = {
        .position = {0,0},
        .score = 0
    };
    ball_t ball = {
        .position = {d.width/2,d.height/2},
        .velocity = {1,1}
    }; // TODO ball starts with random direction

    while(1) {
        // TODO draw paddles
        plotpixel(&d, 0xFFFFFF, ball.position.x, ball.position.y);
        showdisplay(d);

        ball.position.x += ball.velocity.x;
        ball.position.y += ball.velocity.y;

        if(ball.position.x < 0) {
            ++player2.score;
            ball.position = (Vec2i_t){d.width/2,d.height/2};
            ball.velocity = (Vec2i_t){1,1}; // TODO velocity depends on who won
        }
        if(ball.position.x >= (int)d.width) {
            ++player1.score;
            ball.position = (Vec2i_t){d.width/2,d.height/2};
            ball.velocity = (Vec2i_t){1,1}; // TODO velocity depends on who won
        }

        // TODO check if ball hits paddle

        if(ball.position.y < 0 || ball.position.y >= (int)d.height) {
            ball.position.y -= ball.velocity.y; // we could be out of bounds, go back
            ball.velocity.y = -ball.velocity.y;
        }

        // TODO paddle movement
        // TODO automove paddle2

        resetdisplay(&d);
        printf("\n\033[1m%d%*d\033[0m", player1.score, (int)d.width+1, player2.score);
        usleep(1000000/60);
    }

    destroydisplay(&d);
    return 0;
}
