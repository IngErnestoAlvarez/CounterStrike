#include "game_logic/team.h"
#include "game_logic/game.h"
#include "game_logic/player.h"

Team::Team(Game& game, TeamID team_id, Role team_role)
	: game(game),
	  team_id(team_id),
	  team_role(team_role),
	  wins(0) {}

void Team::addPlayer(Player* player) {
	this->players.push_back(player);
	player->registerTeam(this);
}

bool Team::hasPlayersAlive() {
	for (Player* player : this->players) {
		if (player->isAlive())
			return true;
	}

	return false;
}

void Team::update() {
	if (this->game.getWinnerTeam() == this->team_id)
		this->wins++;
}

int Team::getWinCount() const {
	return this->wins;
}

void Team::switchRole() {
	if (this->team_role == COUNTER_TERRORIST)
		this->team_role = TERRORIST;
	else
		this->team_role = COUNTER_TERRORIST;
}

Role Team::getRole() {
	return this->team_role;
}

bool Team::isFull() const {
	return this->players.size() == 1;
}

void Team::initialize() {
	if (this->players.size() == 0)
		return;

	for (Player* player : this->players)
		player->setRole(this->team_role);

	if (this->team_role == TERRORIST) {
		int index = rand() % this->players.size();
		this->players[index]->receiveBomb();
	}
}

int Team::getSize() {
	return this->players.size();
}

std::vector<Player*>& Team::getPlayers() {
	return this->players;
}
