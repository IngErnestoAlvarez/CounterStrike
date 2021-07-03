#include "game_io/player.h"

#include <iostream>
#include <string>

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window)
    : SdlObject(path, animation_frames, window),
      stencil(window),
      primaryWeapon("assets/sprites/ak47.png", 1, window, nullptr),
      life(window, "life 100/100"),
      ammo(window, "ammo 30/30") {
    life.set_pos(0, 500);
    ammo.set_pos(550, 500);
}

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window, Player *player)
    : SdlObject(path, animation_frames, window),
      player(player),
      animation_pos(0),
      stencil(window),
      primaryWeapon("assets/sprites/ak47.png", 1, window,
                    player->getEquippedWeapon()),  // ! Cambiar el nullptr
      life(window, "Life 100/100"),
      ammo(window, "Ammo 30/30") {
    life.set_pos(0, 500);
    ammo.set_pos(550, 500);
    this->selectAnimationPositions();
}

PlayerView::~PlayerView() {}

void PlayerView::render() {
    this->image.render(player->getX(), player->getY(),
                       180.0 + player->getAngle(), center,
                       &sprite_clips[animation_pos]);
    this->stencil.render(player->getX(), player->getY(), player->getAngle());
    this->primaryWeapon.render(player->getX(), player->getY(),
                               player->getAngle());
    life.render(std::to_string(this->player->getHealth()));
    ammo.render(std::to_string(this->primaryWeapon.getAmmo()));
}

void PlayerView::mouse_mov(int x, int y) {
    this->prevangle = this->angle;
    this->angle = (atan2(pos.y - y, pos.x - x) * 180.0000 / M_PI) - 90;
    if (!angle) {
        this->angle = this->prevangle;
    }
}

void PlayerView::update_animation() {
    // this->animation_pos = 1 - this->animation_pos;
    this->animation_pos = 2;
}

float PlayerView::get_angle() { return this->angle; }

void PlayerView::shootWeapon() { this->primaryWeapon.shoot(); }

void PlayerView::selectAnimationPositions() {
    this->center = {16, 16};
    this->sprite_clips[0].x = 0;
    this->sprite_clips[0].y = 0;
    this->sprite_clips[0].w = 32;
    this->sprite_clips[0].h = 32;

    this->sprite_clips[1].x = 32;
    this->sprite_clips[1].y = 0;
    this->sprite_clips[1].w = 32;
    this->sprite_clips[1].h = 32;

    this->sprite_clips[2].x = 32;
    this->sprite_clips[2].y = 32;
    this->sprite_clips[2].w = 32;
    this->sprite_clips[2].h = 32;
}
