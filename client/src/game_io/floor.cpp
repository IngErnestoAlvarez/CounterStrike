#include "game_io/floor.h"

Floor::Floor(SdlWindow &window) : SdlObject(OFFICE_TYPE, window) {
    width = 26;
    height = 26;
    center = {16, 16};
    sprite_clips->h = 32;
    sprite_clips->w = 32;
    sprite_clips->x = 0;
    sprite_clips->y = 0;
}

Floor::~Floor() {}

void Floor::render() {
    for (int raw = 0; raw < width; ++raw) {
        for (int col = 0; col < height; ++col) {
            this->image.render(raw * 64, col * 64, 0, center, sprite_clips);
        }
    }
}
