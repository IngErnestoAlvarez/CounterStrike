#include "game_proxy/modelo_proxy.h"

#include <cstdlib>
#include <stdexcept>
#include <string>

#include "Logger.h"

static BodyType teamIDtoBodyType(const char *teamID);
static BodyType teamIDtoBodyType(TeamID id);
static TeamID strToTeamID(const char *teamId);

typedef std::lock_guard<std::mutex> guard;

ModeloProxy::ModeloProxy(std::string const &host, std::string const &service,
                         const char *teamID)
    : myTeam(strToTeamID(teamID)),
      protocolo(),
      bodyProxy(),
      staticsProxy(),
      player(teamIDtoBodyType(teamID)),
      roundResult(),
      phase(TEAMS_FORMING_PHASE),
      skt(),
      mutex() {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->info("Conectando con el servidor");

    skt.connect(host.c_str(), service.c_str());

    protocolo.send_login(&skt, strToTeamID(teamID));

    log->info("Conexion exitosa");
}

ModeloProxy::~ModeloProxy() {}

void ModeloProxy::movePlayerUp() { protocolo.send_comando(UP, &skt); }

void ModeloProxy::movePlayerDown() { protocolo.send_comando(DOWN, &skt); }

void ModeloProxy::movePlayerLeft() { protocolo.send_comando(LEFT, &skt); }

void ModeloProxy::movePlayerRight() { protocolo.send_comando(RIGHT, &skt); }

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

void ModeloProxy::lockBodies() { bodyProxy.lock(); }

void ModeloProxy::unlockBodies() { bodyProxy.unlock(); }

bodyVector::iterator ModeloProxy::getStaticIterator() {
    return staticsProxy.getIterator();
}

bodyVector::iterator ModeloProxy::getStaticEnd() {
    return staticsProxy.getEnd();
}

void ModeloProxy::lockStatics() { staticsProxy.lock(); }

void ModeloProxy::unlockStatics() { staticsProxy.unlock(); }

void ModeloProxy::chargeBodies() {
    char *result;
    size_t size;
    uint8_t roundWinner;
    uint8_t AWins;
    uint8_t BWins;
    Phase auxPhase;

    protocolo.recv_state(&result, &size, &roundWinner, &auxPhase, &AWins,
                         &BWins, &skt);

    if (roundWinner != 0 && roundWinner != 1 && roundWinner != 2) {
        throw std::runtime_error("Error con el TeamID recibido del servidor");
    }
    {
        guard guard(mutex);
        roundResult = (TeamID)roundWinner;
        this->teamAWins = AWins;
        this->teamBWins = BWins;
        this->phase = auxPhase;
    }

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
    chargePlayer();
    chargeBodies();
}

int ModeloProxy::getWidth() { return 26; }

int ModeloProxy::getHeight() { return 26; }

TeamID ModeloProxy::getRoundState() {
    guard guard(mutex);
    return roundResult;
}

TeamID ModeloProxy::getMyTeam() { return myTeam; }

uint8_t ModeloProxy::getTeamARounds() { return teamAWins; }

uint8_t ModeloProxy::getTeamBRounds() { return teamBWins; }

Phase ModeloProxy::getPhase() {
    guard guard(mutex);
    return phase;
}

inline BodyType teamIDtoBodyType(const char *teamID) {
    int idAux = strToTeamID(teamID);
    return teamIDtoBodyType((TeamID)idAux);
}

inline BodyType teamIDtoBodyType(TeamID id) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Este es el id que toco: ");
    log->debug(std::to_string(id).c_str());
    if (id == TEAM_A) {
        return CT2_TYPE;
    }
    return TT1_TYPE;
}

inline TeamID strToTeamID(const char *teamId) {
    int idAux = strtol(teamId, nullptr, 10);
    if (idAux != 1 && idAux != 2) {
        throw std::runtime_error("TeamId invalido");
    }
    return (TeamID)idAux;
}
