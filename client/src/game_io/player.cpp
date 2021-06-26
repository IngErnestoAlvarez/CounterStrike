#include "game_io/player.h"

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window)
    : SdlObject(path, animation_frames, window) {}

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window, Player *player)
    : SdlObject(path, animation_frames, window), player(player) {
    this->sprite_clips[0].x = 0;
    this->sprite_clips[0].y = 0;
    this->sprite_clips[0].w = 32;
    this->sprite_clips[0].h = 32;

    this->sprite_clips[1].x = 32;
    this->sprite_clips[1].y = 0;
    this->sprite_clips[1].w = 32;
    this->sprite_clips[1].h = 32;
}

PlayerView::~PlayerView() {}

void PlayerView::render() {
    SDL_Point pos_actual = {player->getX(), player->getY()};
    if ((pos_actual.x != this->pos.x) || (pos_actual.y != this->pos.y)) {
        this->update_animation();
        this->pos = pos_actual;
    }
    this->image.render(player->getX(), player->getY(), angle, center,
                       &sprite_clips[animation_pos]);
}

// void PlayerView::moveUp() { pos.y -= this->sprite_clips->h / 16; }
// void PlayerView::moveDown() { pos.y += this->sprite_clips->h / 16; }
// void PlayerView::moveRight() { pos.x += this->sprite_clips->h / 16; }
// void PlayerView::moveLeft() { pos.x -= this->sprite_clips->h / 16; }
void PlayerView::mouse_mov(int x, int y) {
    this->prevangle = this->angle;
    this->angle = (atan2(pos.y - y, pos.x - x) * 180.0000 / M_PI) - 90;
    if (!angle) {
        this->angle = this->prevangle;
    }
}

void PlayerView::update_animation() {
    this->animation_pos = 1 - this->animation_pos;
}
