#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = FALSE;
int last_frame_time = 0;

struct ball 
{
	float x;
	float y;
	float height;
	float width;
	float xspeed;
	float yspeed;

} ball;

struct wall
{
	float x;
	float y;
	float height;
	float width;
	float xspeed;
	float yspeed;
};

struct pobeda 
{
	float speed;
} pobeda;

struct wall wall1;
struct wall wall2;
struct wall wall3;
struct wall wall4;


int initialize_window(void)
{

	ball.xspeed = pobeda.speed;
	ball.yspeed = pobeda.speed;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		fprintf(stderr, "Error initilazing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow("BRUH", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		0);
	
	if (!window) 
        {
                fprintf(stderr,"Error creating SDL Renderer. \n");
                return FALSE;
        }	

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	if (!renderer)
	{
		fprintf(stderr,"Error creating SDL Renderer. \n");
		return FALSE;
	}

	return TRUE;
}

void process_input()
{	
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_KEYDOWN: {
       			 switch (event.key.keysym.scancode) {
         			case SDL_SCANCODE_ESCAPE: {
           				 game_is_running = FALSE;
					 break;
         			}
					
        		}
       		 	break;
     		 }
	 
	}
}

void setup() 
{
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;

	wall1.width = 8;
	wall1.height = 90;
	wall1.x = WINDOW_WIDTH - 8;
	wall1.y = (WINDOW_HEIGHT / 2) - wall1.height / 2;

	wall2.width = 8;
	wall2.height = 90;
	wall2.x = 0;
	wall2.y = (WINDOW_HEIGHT / 2) - wall2.height / 2;

	wall3.width = 90;
	wall3.height = 8;
	wall3.x = (WINDOW_WIDTH / 2) - wall3.width / 2;
	wall3.y = WINDOW_HEIGHT - wall3.height;

	wall4.width = 90;
	wall4.height = 8;
	wall4.x = (WINDOW_WIDTH / 2) - wall3.width / 2;
	wall4.y = 0;
	
	

}

void update() 
{	

	const Uint8* key = SDL_GetKeyboardState(NULL);
	wall1.yspeed = 0;
	wall2.yspeed = 0;
	wall3.xspeed = 0;
	wall4.xspeed = 0;

	if (key[SDL_SCANCODE_UP]) {
		wall1.yspeed = -7;
		wall2.yspeed = -7;
	}
	if (key[SDL_SCANCODE_DOWN]) {
		wall1.yspeed = 7;
		wall2.yspeed = 7;
	}
	if (key[SDL_SCANCODE_LEFT]) {
		wall3.xspeed = -7;
		wall4.xspeed = -7;
	}
	if (key[SDL_SCANCODE_RIGHT]) {
		wall3.xspeed = 7;
		wall4.xspeed = 7;
	}
	wall1.y += wall1.yspeed;
	wall2.y += wall2.yspeed;
	wall3.x += wall3.xspeed;
	wall4.x += wall4.xspeed;

	
	

	if (ball.y <= 0) 
	{
		ball.yspeed = -ball.yspeed;
	} 

	
	if (ball.x + ball.width >= wall1.x) 
	{
		if ((ball.y + ball.height >= wall1.y) && (ball.y <= (wall1.y + wall1.height))) 
		{	
			ball.xspeed = -ball.xspeed;
			pobeda.speed += 1;

		} else {
			game_is_running = FALSE;
		}
	}

	if (ball.x <= wall2.x + wall2.width) 
	{
		if ((ball.y + ball.height >= wall2.y) && (ball.y <= (wall2.y + wall1.height))) 
		{	
			ball.xspeed = -ball.xspeed;
			pobeda.speed += 1;
			
		} else {
			game_is_running = FALSE;
		}
	}

	if (ball.y + ball.height >= wall3.y) 
	{
		if ((ball.x >= wall3.x) && (ball.x + ball.height <= wall3.x + wall3.width))
		{
			ball.yspeed = -ball.yspeed;
			pobeda.speed += 1;
			
		} else {
			game_is_running = FALSE;
		}
	}

	if (ball.y <= wall4.y + wall4.height)
	{
		if ((ball.x >= wall3.x) && (ball.x + ball.height <= wall3.x + wall3.width))
		{
			ball.yspeed = -ball.yspeed;
			pobeda.speed += 1;
			
		} else {
			game_is_running = FALSE;
		}
	}

	ball.x += ball.xspeed;
	ball.y += ball.yspeed;

}

void render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {(int)ball.x, (int)ball.y, (int)ball.width, (int)ball.height};
	SDL_Rect wall1_rect = {(int)wall1.x, (int)wall1.y, (int)wall1.width, (int)wall1.height};
	SDL_Rect wall2_rect = {(int)wall2.x, (int)wall2.y, (int)wall2.width, (int)wall2.height};
	SDL_Rect wall3_rect = {(int)wall3.x, (int)wall3.y, (int)wall3.width, (int)wall3.height};
	SDL_Rect wall4_rect = {(int)wall4.x, (int)wall4.y, (int)wall4.width, (int)wall4.height};


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(renderer, &ball_rect);
	SDL_RenderFillRect(renderer, &wall1_rect);
	SDL_RenderFillRect(renderer, &wall2_rect);
	SDL_RenderFillRect(renderer, &wall3_rect);
	SDL_RenderFillRect(renderer, &wall4_rect);

	SDL_RenderPresent(renderer);


}

void destroy_window() 
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	pobeda.speed = 3;
	game_is_running = initialize_window();
	
	setup();

	while (game_is_running == TRUE)
	{
		process_input();
		update();
		render();
	}
	
	destroy_window();

	return 0;
}
