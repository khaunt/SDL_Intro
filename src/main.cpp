#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"
#include "./raquet.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;
int down = FALSE;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;

raquet player_1 = {1};
raquet player_2 = {2};

int initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error rendering SDL.\n");
		return FALSE;
	}

	return TRUE;
	
}

void setup() {
	ball.x = WINDOW_WIDTH/2;
	ball.y = WINDOW_HEIGHT/2;
	ball.width = 15;
	ball.height = 15;
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_QUIT:
			game_is_running = FALSE;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				game_is_running = FALSE;
				break;
			}
	}
}

void update() {
	// Calculate how much we have to wait until we reach the target frame time
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	// Only delay if we are too fast to update this frame
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	// Get a delta time factor converted to seconds to be used to update my obj
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();
	
	ball.x += 40 * delta_time;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	//TODO: Here i where we an start drawing our game objects
	SDL_Rect ball_rect = {
		(int)ball.x, 
		(int)ball.y, 
		(int)ball.width, 
		(int)ball.height
	};
	SDL_Rect raq1 = {
		(int)player_1.x,
		(int)player_1.y,
		(int)player_1.width,
		(int)player_1.height
	};
	
	SDL_Rect raq2 = {
		(int)player_2.x,
		(int)player_2.y,
		(int)player_2.width,
		(int)player_2.height
	};
	

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);
	SDL_RenderFillRect(renderer, &raq1);
	SDL_RenderFillRect(renderer, &raq2);
	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);
}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	game_is_running = initialize_window();	

	setup();

	while (game_is_running) {
		process_input();
		update();
		render();
	}
	destroy_window();
	return 0;
}
