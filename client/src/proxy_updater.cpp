#include "proxy_updater.h"

ProxyUpdater::ProxyUpdater(ModeloProxy *proxy, std::atomic_bool *playing)
    : Thread(), proxy(proxy), playing(playing) {}

ProxyUpdater::~ProxyUpdater() {}

void ProxyUpdater::run() {
    try {
        while ((*playing).load() == true) {
            proxy->update();
        }
    } catch (socket_t::SocketClosed &e) {
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
