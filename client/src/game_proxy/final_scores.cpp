#include "game_proxy/final_scores.h"

FinalScores::FinalScores() : winnerTeam(NONE), playersA(), playersB() {}

FinalScores::~FinalScores() {}

void FinalScores::setWinnerTeam(TeamID team) { winnerTeam = team; }

void FinalScores::addPlayerA(std::string const &name, int kills, int deaths,
                             int total_money) {
    addPlayer(name, kills, deaths, total_money, playersA);
}

void FinalScores::addPlayerB(std::string const &name, int kills, int deaths,
                             int total_money) {
    addPlayer(name, kills, deaths, total_money, playersB);
}

const std::vector<PlayerScore> &FinalScores::getPlayersA() { return playersA; }

const std::vector<PlayerScore> &FinalScores::getPlayersB() { return playersB; }

void FinalScores::addPlayer(std::string const &name, int kills, int deaths,
                            int total_money, std::vector<PlayerScore> &vector) {
    PlayerScore player;
    player.name = name;
    player.kills = kills;
    player.deaths = deaths;
    player.total_money = total_money;
    vector.push_back(player);
}
