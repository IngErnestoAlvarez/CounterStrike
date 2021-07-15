#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

class Game;

struct BodyData {
	uint8_t type; 
	uint16_t x;
	uint16_t y;
	uint32_t angle;
};

class GameState {
public:
	uint8_t phase;
	uint8_t ammo;
	uint8_t health;
	uint16_t money;
	uint16_t x;
	uint16_t y;
	uint32_t angle;
	uint8_t weapon;
	uint8_t time = 60;
	uint8_t has_bomb;
	uint8_t body_type;

	uint8_t winner_team_id;
	uint8_t team_a_wins = 0;
	uint8_t team_b_wins = 0;
	uint16_t body_count;
	std::vector<struct BodyData> bodies;

	GameState();
	GameState(Game& game, int player_id);
};

#endif
