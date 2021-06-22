#include <iostream>
#include "game_logic/game.h"
#include "game_logic/world.h"
#include "game_logic/body.h"
#include "game_logic/cell.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/SdlObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <cmath>

int main(int argc, const char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(800, 800, SDL_RENDERER_ACCELERATED, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 1);
    SDL_RenderClear(renderer);
    SDL_Texture* player = IMG_LoadTexture(renderer, "../assets/sprites/player.png");
    SDL_Texture* wall = IMG_LoadTexture(renderer, "../assets/sprites/wall.png");
    SDL_Texture* ground = IMG_LoadTexture(renderer, "../assets/sprites/office.png");
    SDL_RendererFlip flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_Rect dst;
    SDL_RenderCopy(renderer, ground, nullptr, nullptr);

    Game game("../config/config.yaml", "../assets/maps/map.yaml");
    World& world = game.getWorld();
    Map& map = game.getMap();
    Body* body = world.createBody(0, 500, 200);

    bool running = true;
    SDL_Event event;

	while (running) {
		SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, ground, nullptr, nullptr);
		SDL_WaitEvent(&event);

        float angle = 0;
        int mouse_x;
        int mouse_y;

        switch(event.type) {
            case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            body->moveLeft();
                            break;
                        case SDLK_RIGHT:
                            body->moveRight();
                            break;
                        case SDLK_UP:
                            body->moveUp();
                            break;
                        case SDLK_DOWN:
                            body->moveDown();
                            break;
                        }
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                body->stopMoving();
                break;
            case SDL_QUIT:
            	running = false;
                break;
        }

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                Cell* cell = map.getCellAt(i, j);
                dst = {int(cell->getWorldX()) - 4, int(cell->getWorldY()), 32, 32};
                if (cell->canBeAccesed()) {
                    // SDL_RenderCopy(renderer, ground, nullptr, &dst);
                } else {
                    SDL_RenderCopy(renderer, wall, nullptr, &dst);
                }
            }
        }

        dst = {int(body->getX()), int(body->getY()), 32, 32};

        if (mouse_x && mouse_y) {
            angle = (atan2(body->getY()-mouse_y, body->getX()-mouse_x)*180.0000)/3.1416 + 90;
        }

        SDL_RenderCopyEx(renderer, player, nullptr, &dst, angle, nullptr, flip);

		SDL_RenderPresent(renderer);
		world.step();
	}

	return 0;
}
