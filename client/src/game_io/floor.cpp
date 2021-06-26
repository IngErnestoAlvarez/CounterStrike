#include "game_io/floor.h"

Floor::Floor(std::string const &path, int animation_frames, SdlWindow &window,
             Map *map)
    : SdlObject(path, animation_frames, window),
      box(window, "assets/sprites/wall.png"),
      map(map) {
    center = {16, 16};
    sprite_clips->h = 32;
    sprite_clips->w = 32;
    sprite_clips->x = 0;
    sprite_clips->y = 0;
}

Floor::~Floor() {}

void Floor::render() {
    for (Cell &cell : (*this->map)) {
        if (cell.canBeAccesed()) {
            this->image.render(cell.getWorldX(), cell.getWorldY(), angle,
                               center, sprite_clips);
        } else {
            this->box.render(cell.getWorldX(), cell.getWorldY(), angle, center,
                             sprite_clips);
        }
    }
}
