#include "game_io/floor.h"

Floor::Floor(std::string const &path, int animation_frames, SdlWindow &window)
    : SdlObject(path, animation_frames, window) {
    center = {32, 32};
    sprite_clips->h = 64;
    sprite_clips->w = 64;
    sprite_clips->x = 0;
    sprite_clips->y = 0;
}

Floor::~Floor() {}

void Floor::render() {
    this->image.render(pos);
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 10; j++) {
            SDL_Point point = {i * 64, j * 64};
            this->image.render(point.x, point.y, angle, center, sprite_clips);
        }
    }
}
