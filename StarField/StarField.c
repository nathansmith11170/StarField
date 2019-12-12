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

typedef struct {
    int x;
    int y;
    int z;
} Star;

/* Generates a random integer in a range */
int randomInt(int lowerBound, int upperBound)
{
    return rand()%(upperBound - lowerBound + 1) + lowerBound;
}

/* Moves a star by a certain x and y */
void translateStar(Star* star, int translateByX, int translateByY)
{
    (*star).x + translateByX;
    (*star).y + translateByY;
}

/* Shifts a star's proximity by incrementing its z value */
void updateStar(Star* star)
{
    (*star).z -= 5;
    if((*star).z < 0)
    {
        (*star).z = WINDOW_WIDTH;
    }
}

/* This function takes a proportion and maps it from one interval of integers to a 
   second interval */
int map(double proportion, int min1, int max1, int min2, int max2)
{
    return (int) proportion * (max2 - min2) + min2;
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

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1,
                             SDL_RENDERER_ACCELERATED | 
                             SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL) {
        printf("error creating renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Star stars[800];
    for(int i = 0; i < 800; i++)
    {
        stars[i].x = randomInt(-WINDOW_WIDTH, WINDOW_WIDTH);
        stars[i].y = randomInt(-WINDOW_HEIGHT, WINDOW_HEIGHT);
        stars[i].z = randomInt(0, WINDOW_WIDTH);
    }
    
    /* The loop below is the main program loop. */
    SDL_Event e;
    int quit = 0;
    while(!quit)
    {

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
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for(int i = 0; i < 800; i++)
        {
            int sx = map((double) stars[i].x / stars[i].z, 0, 1, 0, WINDOW_WIDTH);
            int sy = map((double) stars[i].y / stars[i].z, 0, 1, 0, WINDOW_HEIGHT);
            translateStar(&stars[i], WINDOW_HEIGHT/2, WINDOW_WIDTH/2);
            filledEllipseColor(renderer, sx, sy, 2, 2, 0xFFFFFFFF);
            updateStar(&stars[i]);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}