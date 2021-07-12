#ifndef __APP_H__
#define __APP_H__

#include <atomic>
#include <string>

#include "game_io/modelo_io.h"
#include "game_proxy/modelo_proxy.h"
#include "proxy_sender.h"
#include "proxy_updater.h"

class App {
   private:
    Uint32 next_time;
    std::atomic_bool playing;
    ModeloProxy proxy;
    ModeloIO view;
    ProxyUpdater proxyUpdater;
    ProxySender proxySender;

   public:
    App(std::string const &host, std::string const &service,
        const char *teamID);

    ~App();

    void load_media();

    void main_loop();

   private:
    Uint32 time_left();
};

#endif
