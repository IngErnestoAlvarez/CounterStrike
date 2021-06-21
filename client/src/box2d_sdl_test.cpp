#include <iostream>
#include "game_logic/world.h"
#include "game_logic/body.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/SdlObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

int main(int argc, const char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(800, 600, SDL_RENDERER_ACCELERATED, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 1);
    SDL_RenderClear(renderer);
    SDL_Rect dst;
	SDL_Texture* texture = IMG_LoadTexture(renderer, "../assets/sprites/ak47.png");
	World world;
	Body body(&world, 0, 500, 200);
	std::cout << body.getX() << " - " << body.getY() << std::endl;

	bool running = true;
    SDL_Event event;	

	while (running) {
		SDL_RenderClear(renderer);
		SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            body.startMoving(-800, 0);
                            break;
                        case SDLK_RIGHT:
                            body.startMoving(800, 0);
                            break;
                        case SDLK_UP:
                            body.startMoving(0, -800);
                            break;
                        case SDLK_DOWN:
                            body.startMoving(0, 800);
                            break;
                        }
                }
                break;
            case SDL_QUIT:
            	running = false;
                break;
        }
		std::cout << body.getX() << " - " << body.getY() << std::endl;
		dst = {int(body.getX()), int(body.getY()), 64, 64};
		SDL_RenderCopy(renderer, texture, nullptr, &dst);
		SDL_RenderPresent(renderer);
		// SDL_Delay(60);
		world.step();

	}

	return 0;
}
