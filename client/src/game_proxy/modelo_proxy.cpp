#include "game_proxy/modelo_proxy.h"

#include <string>

#include "Logger.h"

ModeloProxy::ModeloProxy(std::string const &host, std::string const &service)
    : protocolo(), bodyProxy(), staticsProxy(), player() {
    skt.connect(host.c_str(), service.c_str());
}

ModeloProxy::~ModeloProxy() {}

void ModeloProxy::movePlayerUp() { protocolo.send_comando(UP, &skt); }

void ModeloProxy::movePlayerDown() { protocolo.send_comando(DOWN, &skt); }

void ModeloProxy::movePlayerLeft() { protocolo.send_comando(LEFT, &skt); }

void ModeloProxy::movePlayerRight() { protocolo.send_comando(RIGHT, &skt); }

void ModeloProxy::setPlayerAim(int x, int y) {
    protocolo.send_mouse(x, y, &skt);
}

void ModeloProxy::stopPlayer() { protocolo.send_comando(STOP, &skt); }

void ModeloProxy::usePlayerWeapon() { protocolo.send_comando(SHOOT, &skt); }

bodyVector::iterator ModeloProxy::getBodyIterator() {
    return bodyProxy.getIterator();
}

bodyVector::iterator ModeloProxy::getBodyEnd() { return bodyProxy.getEnd(); }

bodyVector::iterator ModeloProxy::getStaticIterator() {
    return staticsProxy.getIterator();
}

bodyVector::iterator ModeloProxy::getStaticEnd() {
    return staticsProxy.getEnd();
}

void ModeloProxy::chargeBodies() {
    char *result;
    size_t size;

    protocolo.recv_state(&result, &size, &skt);

    bodyProxy.setBodies(result, size);
    free(result);
}

void ModeloProxy::chargePlayer() {
    char *result;
    size_t size;

    protocolo.recv_player(&result, &size, &skt);

    player.setPlayer(result, size);
    free(result);
}

void ModeloProxy::chargeStatics() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    char *result;
    size_t size;

    protocolo.recv_player(&result, &size, &skt);
    log->debug("Se recibio lo siguiente del recv_config del protocolo: ");
    log->debug(result);

    staticsProxy.setStatics(result, size);

    free(result);
}

int ModeloProxy::getPlayerX() { return player.getX(); }

int ModeloProxy::getPlayerY() { return player.getY(); }

float ModeloProxy::getPlayerAngle() { return player.getAngle(); }

PlayerProxy *ModeloProxy::getPlayer() { return &this->player; }

void ModeloProxy::initialize() { chargeStatics(); }

void ModeloProxy::update() {
    chargeBodies();
    chargePlayer();
}

int ModeloProxy::getWidth() { return 26; }

int ModeloProxy::getHeight() { return 26; }
