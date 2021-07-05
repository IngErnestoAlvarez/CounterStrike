#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "types.h"

class Game;
class Player;

class Team {
private:
	Game& game;
	std::vector<Player*> players;
	Role team_role;
	int wins;

public:
	Team(Game& game, Role team_role);
	void addPlayer(Player* player);
	void switchRole();
	Role getRole();
	bool hasPlayersAlive();
	void update();
	int getWinCount();
};

#endif
