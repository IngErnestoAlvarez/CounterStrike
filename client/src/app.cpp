#include "app.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <syslog.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlObject.h"

#define DELAY 14

App::App(std::string const &host, std::string const &service,
         std::string const &game_id, const char *teamID)
    : playing(true),
      proxy(host, service, game_id, teamID),
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
        SDL_Delay(time_left);
        this->next_time += DELAY;
    }
    proxySender.join();
    proxyUpdater.join();
    if (proxy.getPhase() == FINAL_PHASE) {
        proxy.finally();
        view.renderFinal();
    }
    proxy.close();
    sleep(10);
}

Uint32 App::time_left() {
    Uint32 now = SDL_GetTicks();

    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}
