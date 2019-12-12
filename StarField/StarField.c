#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

const int FRAMES_PER_SECOND = 60;
const int MSECONDS_PER_FRAME = 1000/60;

/*
  The x and the y are the position of the ellipse, and the z value represents
  the proximity of the star, with 1 being far away and 0 being very close.
*/
typedef struct {
    int x;
    int y;
    double z;
} Star;

/* Generates a random integer in a range */
int randomInt(int lowerBound, int upperBound)
{
    return rand()%(upperBound - lowerBound + 1) + lowerBound;
}

/* Moves a star by a certain x and y */
void translate(int (*coord)[], int translateByX, int translateByY)
{
    (*coord)[0] = (*coord)[0] + translateByX;
    
    (*coord)[1] = (*coord)[1] + translateByY;
}

/* Shifts a star's proximity by decrementing its z value */
void updateStar(Star *star)
{
    (*star).z -= .025;
    if((*star).z < 0)
    {
        (*star).z = 1.0;
    }
}

int main()
{
    srand(time(0));

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* win = SDL_CreateWindow("Water", 
                      SDL_WINDOWPOS_CENTERED, 
                      SDL_WINDOWPOS_CENTERED, 
                      WINDOW_WIDTH, 
                      WINDOW_HEIGHT, 
                      0);

    if (win == NULL) {
        printf("error creating window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, 1,
                             SDL_RENDERER_ACCELERATED | 
                             SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL) {
        printf("error creating renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Initialize the stars */
    Star stars[800];
    for(int i = 0; i < 800; i++)
    {
        stars[i].x = randomInt(-WINDOW_WIDTH/2, WINDOW_WIDTH/2);
        stars[i].y = randomInt(-WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
        stars[i].z = (double)rand()/RAND_MAX;
    }
    
    /* The loop below is the main program loop. */
    SDL_Event e;
    int quit = 0;
    while(!quit)
    {
        /* this timer is for the framerate control */
        int start = SDL_GetTicks();

        /* event loop */
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;

                default: {}
            }
        }

        /* rendering */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for(int i = 0; i < 800; i++)
        {
            int sx, sy, temp[2];
            double size;
            updateStar(&stars[i]);
            temp[0] = stars[i].x/stars[i].z;
            temp[1] = stars[i].y/stars[i].z;
            translate(&temp, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
            size = stars[i].z;
            if( size < .2)
            {
                filledEllipseColor(renderer, temp[0], temp[1], 5, 5, 0xFFFFFFFF);
            }
            else if (size < .4)
            {
                filledEllipseColor(renderer, temp[0], temp[1], 4, 4, 0xFFFFFFFF);
            }
            else if (size < .6)
            {
                filledEllipseColor(renderer, temp[0], temp[1], 3, 3, 0xFFFFFFFF);
            }
            else if (size < .8)
            {
                filledEllipseColor(renderer, temp[0], temp[1], 2, 2, 0xFFFFFFFF);
            }
            else
            {
                filledEllipseColor(renderer, temp[0], temp[1], 1, 1, 0xFFFFFFFF);
            }
            
        }
        SDL_RenderPresent(renderer);

        /* frame rate control */
        int time = SDL_GetTicks()-start;
        if (time < 0)
        {
            continue;
        }

        int sleepTime = MSECONDS_PER_FRAME - time;
        if (sleepTime > 0)
        {
            SDL_Delay(sleepTime);
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}