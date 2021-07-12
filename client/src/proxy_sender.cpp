#include "proxy_sender.h"

ProxySender::ProxySender(ModeloIO *modelo, std::atomic_bool *playing)
    : Thread(), modelo(modelo), playing(playing) {}

ProxySender::~ProxySender() {}

void ProxySender::run() {
    while (playing->load() == true) {
        modelo->check_actions();
    }
}
