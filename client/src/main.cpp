#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "sdl/SdlWindow.h"
#include "sound/sample.h"

int main(int argc, char const *argv[]) {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096);
    Sample sound("../assets/sounds/SHOT.wav");
    sound.play();

    std::getchar();

    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    return 0;
}
