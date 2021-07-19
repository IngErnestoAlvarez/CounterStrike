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

App::App(std::string const &host, std::string const &service, std::string const &game_id,
         const char *teamID)
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
        // std::cout << "time_left: " << time_left << std::endl;
        SDL_Delay(time_left);
        this->next_time += DELAY;
    }
    std::cout << "Llega a proxy.close" << std::endl;
    proxySender.join();
    proxyUpdater.join();
    std::cout << "Llega al finally" << std::endl;
    proxy.finally();
    view.renderFinal();
    playing = false;
    proxy.close();
    std::cout << "Llega al sleep" << std::endl;
    sleep(4);
}

Uint32 App::time_left() {
    Uint32 now = SDL_GetTicks();

    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}
