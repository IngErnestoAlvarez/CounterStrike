#include "game_io/sound/music.h"

#include <stdexcept>

Music::Music(std::string const &path) {
    music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        throw std::runtime_error("No pudo abrirse el archivo de musica");
    }
}

Music::Music(std::string const &path, int volume) : Music(path) {
    set_volume(volume);
}

Music::~Music() { Mix_FreeMusic(music); }

void Music::play() { Mix_PlayMusic(music, -1); }

void Music::set_volume(int volume) { Mix_VolumeMusic(volume); }
