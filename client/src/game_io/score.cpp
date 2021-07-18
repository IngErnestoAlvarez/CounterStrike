#include "game_io/score.h"

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
    std::string aux;
    for (PlayerScore &p : teamA) {
        aux = "";
        aux += p.name;
        aux += "  ";
        aux += p.kills;
        aux += "  ";
        aux += p.deaths;
        aux += "  ";
        aux += p.total_money;

        teamAScores.emplace_back(*window, aux, BLUE, 15);
        teamAScores.back().set_pos(50, pos);
        pos += 30;
    }
    pos = 200;
    for (PlayerScore &p : teamB) {
        aux = "";
        aux += p.name;
        aux += "  ";
        aux += p.kills;
        aux += "  ";
        aux += p.deaths;
        aux += "  ";
        aux += p.total_money;

        teamBScores.emplace_back(*window, aux, RED, 15);
        teamBScores.back().set_pos(650, pos);
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
