#ifndef __FINAL_SCORES_H__
#define __FINAL_SCORES_H__

#include <string>
#include <vector>

#include "types.h"

struct PlayerScore {
    std::string name;
    int kills;
    int deaths;
    int total_money;
};

class FinalScores {
   private:
    TeamID winnerTeam;
    std::vector<PlayerScore> playersA;
    std::vector<PlayerScore> playersB;

   public:
    FinalScores();
    ~FinalScores();

    void setWinnerTeam(TeamID team);

    void addPlayerA(std::string const &name, int kills, int deaths,
                    int total_money);

    void addPlayerB(std::string const &name, int kills, int deaths,
                    int total_money);

    const std::vector<PlayerScore> &getPlayersA();
    const std::vector<PlayerScore> &getPlayersB();

   private:
    void addPlayer(std::string const &name, int kills, int deaths,
                   int total_money, std::vector<PlayerScore> &vector);
};

#endif  // __FINAL_SCORES_H__
