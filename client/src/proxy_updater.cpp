#include "proxy_updater.h"

ProxyUpdater::ProxyUpdater(ModeloProxy *proxy, std::atomic_bool *playing)
    : Thread(), proxy(proxy), playing(playing) {}

ProxyUpdater::~ProxyUpdater() {}

void ProxyUpdater::run() {
    while ((*playing).load() == true) {
        proxy->update();
    }
}
