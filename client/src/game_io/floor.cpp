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
    int i = 0;  // 13
    int j = 0;  // 10
    for (Cell &cell : (*this->map)) {
        SDL_Point point = {i * 32, j * 32};
        if (cell.canBeAccesed()) {
            this->image.render(point.x, point.y, angle, center, sprite_clips);
        } else {
            this->box.render(point.x, point.y, angle, center, sprite_clips);
        }

        if (j == 18) {
            i++;
            j = 0;
        } else {
            j++;
        }
    }
}
