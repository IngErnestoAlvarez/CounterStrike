#include "game_logic/team.h"
#include "game_logic/game.h"
#include "game_logic/player.h"

Team::Team(Game& game, Role team_role)
	: game(game),
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
	if (this->game.getWinnerTeam() == this->team_role)
		this->wins++;
}

int Team::getWinCount() {
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
