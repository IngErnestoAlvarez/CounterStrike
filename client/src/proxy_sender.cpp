#include "proxy_sender.h"

ProxySender::ProxySender(ModeloIO *modelo, std::atomic_bool *playing)
    : Thread(), modelo(modelo), playing(playing) {}

ProxySender::~ProxySender() {}

void ProxySender::run() {
    try {
        while (playing->load() && modelo->isActive()) {
            modelo->check_actions();
        }
    } catch (socket_t::SocketClosed &e) {
        *playing = false;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    *playing = false;
}
