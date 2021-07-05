#include "game_io/otherplayer.h"

OtherPlayer::OtherPlayer(std::string const &path, int animation_frames,
                         SdlWindow &window)
    : SdlObject(CT2_TYPE, window), animation_pos(0) {
    this->center = {16, 16};
    this->sprite_clips[0].x = 0;
    this->sprite_clips[0].y = 0;
    this->sprite_clips[0].w = 32;
    this->sprite_clips[0].h = 32;

    this->sprite_clips[1].x = 32;
    this->sprite_clips[1].y = 0;
    this->sprite_clips[1].w = 32;
    this->sprite_clips[1].h = 32;
}

OtherPlayer::~OtherPlayer() {}

void OtherPlayer::update_animation() { animation_pos = 1 - animation_pos; }

void OtherPlayer::render(int x, int y, float angle) {
    this->image.render(x, y, angle, center, &sprite_clips[animation_pos]);
}
