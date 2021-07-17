#include <arpa/inet.h>
#include "game_state.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "types.h"

GameState::GameState() {}

GameState::GameState(Game& game, int player_id) {
	Player* player = game.getPlayer(player_id);

	this->ammo = uint8_t(player->getAmmo());
	this->health = uint8_t(player->getHealth());
	this->money = ::htons(1000);
	this->x = ::htons(uint16_t(player->getX()));
	this->y = ::htons(uint16_t(player->getY()));
	float angleAux = player->getAngle();
	this->angle = ::htonl(*(uint32_t *)&angleAux);

	this->weapon = uint8_t(player->getEquippedWeaponType());
	this->has_bomb = uint8_t(player->hasBomb());
	this->body_type = uint8_t(player->getType());

	this->phase = uint8_t(game.getPhase());
	this->winner_team_id = uint8_t(game.getWinnerTeam());
	this->team_a_wins = uint8_t(game.getTeamAWins());
	this->team_b_wins = uint8_t(game.getTeamBWins());
    std::vector<Body *> bodies = game.getBodies(player_id);
	this->body_count = ::htons(uint16_t(bodies.size()));

	for (Body* body : bodies) {
		struct BodyData body_data;
		body_data.type = uint8_t(body->getType());
		body_data.x = ::htons(uint16_t(body->getX()));
		body_data.y = ::htons(uint16_t(body->getY()));
		body_data.angle = ::htonl(uint32_t(body->getAngle()));
		this->bodies.push_back(body_data);
	}
}
