#include "game_proxy/modelo_proxy.h"

#include <cstdlib>
#include <stdexcept>
#include <string>

#include "Logger.h"

static BodyType teamIDtoBodyType(const char *teamID);
static BodyType teamIDtoBodyType(TeamID id);

ModeloProxy::ModeloProxy(std::string const &host, std::string const &service,
                         const char *teamID)
    : protocolo(),
      bodyProxy(),
      staticsProxy(),
      player(teamIDtoBodyType(teamID)),
      roundResult(0),
      skt() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->info("Conectando con el servidor");

    skt.connect(host.c_str(), service.c_str());

    int teamIDaux = strtol(teamID, nullptr, 10);
    if (teamIDaux != 1 && teamIDaux != 2) {
        throw std::runtime_error("No es valido el equipo elegido");
    }
    protocolo.send_login(&skt, (TeamID)teamIDaux);

    log->info("Conexion exitosa");
}

ModeloProxy::~ModeloProxy() {}

void ModeloProxy::movePlayerUp() { protocolo.send_comando(UP, &skt); }

void ModeloProxy::movePlayerDown() { protocolo.send_comando(DOWN, &skt); }

void ModeloProxy::movePlayerLeft() { protocolo.send_comando(LEFT, &skt); }

void ModeloProxy::movePlayerRight() { protocolo.send_comando(RIGHT, &skt); }

void ModeloProxy::setPlayerAim(int x, int y) {
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    protocolo.send_mouse(x, y, &skt);
}

void ModeloProxy::setPlayerAngle(float angle) {
    protocolo.send_angle(angle, &skt);
}

void ModeloProxy::stopPlayer() { protocolo.send_comando(STOP, &skt); }

void ModeloProxy::usePlayerWeapon() { protocolo.send_comando(SHOOT, &skt); }

void ModeloProxy::changeToW1() { protocolo.send_comando(CW1, &skt); }

void ModeloProxy::changeToW2() { protocolo.send_comando(CW2, &skt); }

void ModeloProxy::changeToW3() { protocolo.send_comando(CW3, &skt); }

void ModeloProxy::changeToBomb() { protocolo.send_comando(CB, &skt); }

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

    protocolo.recv_state(&result, &size, &roundResult, &skt);

    bodyProxy.setBodies(result, size);
    delete (result);
}

void ModeloProxy::chargePlayer() {
    char *result;
    size_t size;

    protocolo.recv_player(&result, &size, &skt);

    player.setPlayer(result, size);
    delete (result);
}

void ModeloProxy::chargeStatics() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    char *result;
    size_t size;

    protocolo.recv_config(&result, &size, &skt);
    log->debug("Se recibio lo siguiente del recv_config del protocolo: ");
    log->debug(result);

    staticsProxy.setStatics(result, size);

    delete (result);
}

int ModeloProxy::getPlayerX() { return player.getX(); }

int ModeloProxy::getPlayerY() { return player.getY(); }

float ModeloProxy::getPlayerAngle() { return player.getAngle(); }

PlayerProxy *ModeloProxy::getPlayer() { return &this->player; }

void ModeloProxy::initialize() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->info("Cargando objetos estaticos");
    chargeStatics();
    log->info("Terminados de cargar objetos estaticos");
}

void ModeloProxy::update() {
    chargeBodies();
    chargePlayer();
}

int ModeloProxy::getWidth() { return 26; }

int ModeloProxy::getHeight() { return 26; }

uint8_t ModeloProxy::getRoundState() { return roundResult; }

inline BodyType teamIDtoBodyType(const char *teamID) {
    int idAux = strtol(teamID, nullptr, 10);
    if (idAux != 1 && idAux != 2) {
        throw std::runtime_error("TeamId invalido");
    }

    return teamIDtoBodyType((TeamID)idAux);
}

inline BodyType teamIDtoBodyType(TeamID id) {
    if (id == TEAM_A) {
        return CT2_TYPE;
    }
    return TT1_TYPE;
}
