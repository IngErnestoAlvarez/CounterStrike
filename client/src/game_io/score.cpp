#include "game_io/score.h"

#include <iomanip>
#include <sstream>
#include <string>

Score::Score(SdlWindow &window) : window(&window) {}

Score::~Score() {
    size_t maxSize = teamAScores.size();
    for (size_t i = 0; i < maxSize; i++) {
        teamAScores.pop_back();
    }
    maxSize = teamBScores.size();
    for (size_t i = 0; i < maxSize; i++) {
        teamBScores.pop_back();
    }
}

void Score::setTeams(std::vector<PlayerScore> &teamA,
                     std::vector<PlayerScore> &teamB) {
    int pos = 200;
    std::stringstream aux;
    aux.str("");
    aux << std::setw(10) << "PLAYER";
    aux << std::setw(20) << "KILLS";
    aux << std::setw(20) << "DEATHS";
    aux << std::setw(20) << "MONEY";
    teamAScores.emplace_back(*window, aux.str(), GREEN, 14);
    teamAScores.back().set_pos(0, pos);
    pos += 30;
    for (PlayerScore &p : teamA) {
        aux.str("");
        aux << std::setw(10) << p.name;
        aux << std::setw(22) << std::to_string(p.kills);
        aux << std::setw(25) << std::to_string(p.deaths);
        aux << std::setw(30) << std::to_string(p.total_money);

        teamAScores.emplace_back(*window, aux.str(), BLUE, 14);
        teamAScores.back().set_pos(0, pos);
        pos += 30;
    }
    pos = 200;
    aux.str("");
    aux << std::setw(10) << "PLAYER";
    aux << std::setw(20) << "KILLS";
    aux << std::setw(20) << "DEATHS";
    aux << std::setw(20) << "MONEY";
    teamBScores.emplace_back(*window, aux.str(), GREEN, 14);
    teamBScores.back().set_pos(400, pos);
    pos += 30;
    for (PlayerScore &p : teamB) {
        aux.str("");
        aux << std::setw(10) << p.name;
        aux << std::setw(22) << std::to_string(p.kills);
        aux << std::setw(25) << std::to_string(p.deaths);
        aux << std::setw(30) << std::to_string(p.total_money);

        teamBScores.emplace_back(*window, aux.str(), RED, 14);
        teamBScores.back().set_pos(400, pos);
        pos += 30;
    }
}

void Score::render() {
    for (SdlText &p : teamAScores) {
        p.render();
    }
    for (SdlText &p : teamBScores) {
        p.render();
    }
}
