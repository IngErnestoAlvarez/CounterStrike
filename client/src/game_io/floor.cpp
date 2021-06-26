#include "game_io/floor.h"

Floor::Floor(std::string const &path, int animation_frames, SdlWindow &window,
             Map *map)
    : SdlObject(path, animation_frames, window),
      box(window, "assets/sprites/wall.png"),
      map(map) {
    center = {32, 32};
    sprite_clips->h = 64;
    sprite_clips->w = 64;
    sprite_clips->x = 0;
    sprite_clips->y = 0;
}

Floor::~Floor() {}

void Floor::render() {
    int i = 0;  // 13
    int j = 0;  // 10
    for (Cell &cell : (*this->map)) {
        SDL_Point point = {i * 64, j * 64};
        if (cell.canBeAccesed()) {
            this->image.render(point.x, point.y, angle, center, sprite_clips);
        } else {
            this->box.render(point.x, point.y, angle, center, sprite_clips);
        }

        if (j == 9) {
            i++;
            j = 0;
        } else {
            j++;
        }
    }
}
