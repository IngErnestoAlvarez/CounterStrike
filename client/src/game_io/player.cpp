#include "game_io/player.h"

#include <iostream>
#include <string>

#include "Logger.h"

PlayerView::PlayerView(BodyType type, SdlWindow &window, PlayerProxy *player)
    : SdlObject("assets/sprites/ct2.png", 1, window),
      player(player),
      animation_pos(0),
      stencil(window),
      primaryWeapon(window, player->getWeapon()),
      life(window, player->getLife()),
      ammo(window, player->getWeapon()->getAmmo()),
      money(window, player->getMoney()),
      killNotice(window, "Fuiste asesinado", RED, 50) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza constructor PlayerView");
    life.set_pos(0, 500);
    ammo.set_pos(550, 500);
    money.set_pos(0, 100);
    killNotice.set_pos(350, 100);
    log->debug("Finaliza constructor PlayerView");
}

PlayerView::~PlayerView() {}

void PlayerView::render() {
    if (!this->isDead()) {
        renderAlivePlayer();
    } else {
        renderDeadPlayer();
    }
}

void PlayerView::update_animation() {
    // this->animation_pos = 1 - this->animation_pos;
    this->animation_pos = 0;
}

void PlayerView::shootWeapon() { this->primaryWeapon.shoot(); }

bool PlayerView::isDead() {
    // return (player->getLife() <= 0);
    return (player->getWeapon()->getAmmo() < 15);
}

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

void PlayerView::renderAlivePlayer() {
    this->image.render(player->getX(), player->getY(), player->getAngle(),
                       center, &sprite_clips[animation_pos]);
    this->stencil.render(player->getX(), player->getY(), player->getAngle());
    this->primaryWeapon.render(player->getX(), player->getY(),
                               player->getAngle() - 180);
    life.render(std::to_string(this->player->getLife()));
    ammo.render(std::to_string(this->primaryWeapon.getAmmo()));
    money.render(std::to_string(this->player->getMoney()));
}

void PlayerView::renderDeadPlayer() {
    money.render();
    killNotice.render();
}
