#include "sound/sample.h"

#include <iostream>

Sample::Sample(const std::string &filepath) {
    this->chunk = Mix_LoadWAV(filepath.c_str());
    if (this->chunk == NULL) {
        std::cout << filepath << std::endl;
        throw 1;
    }
}

Sample::Sample(const std::string &filepath, int volume) : Sample(filepath) {
    Mix_VolumeChunk(chunk, volume);
}

Sample::~Sample() { Mix_FreeChunk(this->chunk); }

void Sample::play() { Mix_PlayChannel(-1, this->chunk, 0); }

void Sample::play(int times) { Mix_PlayChannel(-1, this->chunk, times - 1); }

void Sample::set_volume(int volume) { Mix_VolumeChunk(this->chunk, volume); }
