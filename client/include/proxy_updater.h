#ifndef __PROXY_UPDATER_H__
#define __PROXY_UPDATER_H__

#include <atomic>

#include "game_proxy/modelo_proxy.h"
#include "my_thread.h"

class ProxyUpdater : public Thread {
   private:
    ModeloProxy *proxy;
    std::atomic_bool *playing;

   public:
    ProxyUpdater(ModeloProxy *proxy, std::atomic_bool *playing);

    ~ProxyUpdater();

    void run() override;
};

#endif  // __PROXY_UPDATER_H__
