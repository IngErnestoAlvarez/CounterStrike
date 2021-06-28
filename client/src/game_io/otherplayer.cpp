#include "game_io/otherplayer.h"

OtherPlayer::OtherPlayer(std::string const &path, int animation_frames,
                         SdlWindow &window, Player *player)
    : SdlObject(path, animation_frames, window),
      player(player),
      animation_pos(0) {
    this->center = {16, 16};
    this->pos = {200, 200};
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

void OtherPlayer::render() {
    SDL_Point pos_actual = {int(player->getX()), int(player->getY())};
    if ((pos_actual.x != this->pos.x) || (pos_actual.y != this->pos.y)) {
        this->update_animation();
        this->pos = pos_actual;
    }
    this->image.render(pos_actual.x, pos_actual.y, this->player->getAngle(),
                       center, &sprite_clips[animation_pos]);
}
