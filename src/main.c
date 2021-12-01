#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <time.h>



#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480



bool initSDL(const char *title, int width, int height, SDL_Window **window, SDL_Renderer **renderer)
{
	bool success = true;
	if ( SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SmaDL: %s\n", SDL_GetError());
		success = false;
	}

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN /*SDL_WINDOW_OPENGL*/);
	if (!*window) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		success = false;
	} else {
		*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
		if (!*renderer) {
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(*renderer, 0xff, 0xff, 0xff, 0xff);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if ( !( IMG_Init(imgFlags) & imgFlags ) ) {
				fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}
	return success;
}


void closeSDL(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}


#include "maths/vec2.h"
#include "maths/shape2.h"
#include "body.h"

#define NUM_BODIES 10
int main(void)
{
	Body_t bodies[NUM_BODIES];
	for (size_t i = 0; i < NUM_BODIES; i++) {
		Vec2_t pos = {i, 0};
		Shape2_t shape = shape2_initRegPoly(4, 0.25);
		bodies[i] = body_init(pos, shape, 1, 1);
		body_applyImpulse(&bodies[i], (Vec2_t){1, 1});
	}

	clock_t oldTime = clock();
	while (1) {
		clock_t newTime = clock();
		size_t dt = newTime - oldTime;
		for (size_t i = 0; i < NUM_BODIES; i++) {
			body_update(&bodies[i], dt);
		}
		oldTime = newTime;

		vec2_print(bodies[0].x);
		puts("");
	}

}
