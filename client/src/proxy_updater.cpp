#include "proxy_updater.h"

ProxyUpdater::ProxyUpdater(ModeloProxy *proxy, std::atomic_bool *playing)
    : Thread(), proxy(proxy), playing(playing) {}

ProxyUpdater::~ProxyUpdater() {}

void ProxyUpdater::run() {
    try {
        while ((proxy->isActive()) && playing->load()) {
            proxy->update();
        }
    } catch (socket_t::SocketClosed &e) {
        *playing = false;
        proxy->deactivate();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    *playing = false;
    proxy->deactivate();
}
