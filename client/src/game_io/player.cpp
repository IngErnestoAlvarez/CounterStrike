#include "game_io/player.h"

#include <iostream>

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window)
    : SdlObject(path, animation_frames, window),
      stencil(window),
      primaryWeapon("assets/sprites/ak47.png", 1, window, nullptr) {}

PlayerView::PlayerView(std::string const &path, int animation_frames,
                       SdlWindow &window, Player *player)
    : SdlObject(path, animation_frames, window),
      player(player),
      animation_pos(0),
      stencil(window),
      primaryWeapon("assets/sprites/ak47.png", 1, window,
                    nullptr)  // ! Cambiar el nullptr
{
    this->selectAnimationPositions();
    this->createText(window);
}

PlayerView::~PlayerView() {}

void PlayerView::render() {
    SDL_Point pos_actual = {int(player->getX()), int(player->getY())};
    if ((pos_actual.x != this->pos.x) || (pos_actual.y != this->pos.y)) {
        this->update_animation();
        this->pos = pos_actual;
    }
    this->image.render(player->getX(), player->getY(),
                       180.0 + player->getAngle(), center,
                       &sprite_clips[animation_pos]);
    this->stencil.render(player->getX(), player->getY(), player->getAngle());
    this->primaryWeapon.render(player->getX(), player->getY(),
                               player->getAngle());
    for (auto &x : this->texts) {
        x->render();
    }
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
void PlayerView::createText(SdlWindow &window) {
    using up = std::unique_ptr<SdlText>;
    this->texts.push_back(up(new SdlText(window, "life 100/100")));
    this->texts.back()->set_pos(0, 570);
    this->texts.push_back(up(new SdlText(window, "ammo 30/30")));
    this->texts.back()->set_pos(600, 570);
}
