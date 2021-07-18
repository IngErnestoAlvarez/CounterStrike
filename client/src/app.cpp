#include "app.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <syslog.h>

#include <iostream>
#include <stdexcept>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlObject.h"

#define DELAY 14

App::App(std::string const &host, std::string const &service,
         const char *teamID)
    : playing(true),
      proxy(host, service, teamID),
      view(proxy),
      proxyUpdater(&proxy, &playing),
      proxySender(&view, &playing) {}

App::~App() {}

void App::load_media() { proxy.initialize(); }

void App::main_loop() {
    playing = true;
    this->next_time = SDL_GetTicks() + DELAY;
    proxyUpdater.start();
    proxySender.start();
    while (playing) {
        playing = view.update();

        Uint32 time_left = this->time_left();
        // std::cout << "time_left: " << time_left << std::endl;
        SDL_Delay(time_left);
        this->next_time += DELAY;
    }
    proxySender.join();
    proxyUpdater.join();

    proxy.finally();
    view.renderFinal();
}

Uint32 App::time_left() {
    Uint32 now = SDL_GetTicks();

    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}
