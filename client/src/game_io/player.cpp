#include "game_io/player.h"

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window)
    : SdlObject(path, animation_frames, window) {}

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window, Player *player)
    : SdlObject(path, animation_frames, window), player(player) {}

PlayerView::~PlayerView() {}

void PlayerView::render() {
    this->image.render(player->getX(), player->getY(), angle, center,
                       sprite_clips);
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
