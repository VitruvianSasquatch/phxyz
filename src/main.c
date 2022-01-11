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

#include "phxy.h"


int main(void)
{
	Vec2_t a1 = {0, -2};
	Vec2_t a2 = {-1, 0};
	Vec2_t b1 = {1, 0};
	Vec2_t b2 = {0, 2};

	printf("%d\n", vec2_lineIntersect(a1, a2, b1, b2));

	/*
	Phxy_t world = phxy_init();
	Shape2_t square = shape2_initRegPoly(4, 0.25);

	for (size_t i = 0; i < 10; i++) {
		Vec2_t pos = {i, 0};
		
		PhxyId_t id = phxy_addBody(&world, body_init(pos, &square, 1, 1));
		phxy_applyImpulse(&world, id, (Vec2_t){1, 1});
	}

	clock_t oldTime = clock();
	while (1) {
		clock_t newTime = clock();
		double dt = (newTime - oldTime)/1000;
		phxy_update(&world, dt);
		oldTime = newTime;

		vec2_print(world.bodies[0].pos);
		puts("");
	}
	*/
}
