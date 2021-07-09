#include "game_io/sound/sample.h"

#include <iostream>
#include <stdexcept>

Sample::Sample(const std::string &filepath) {
    this->chunk = Mix_LoadWAV(filepath.c_str());
    if (this->chunk == NULL) {
        std::cout << filepath << std::endl;
        throw std::runtime_error("No se pudo leer el archivo de audio.");
    }
}

Sample &Sample::operator=(Sample &&other) {
    if (this == &other) return *this;
    this->empty();
    this->chunk = other.chunk;
    other.chunk = nullptr;
    return *this;
}

Sample::Sample(const std::string &filepath, int volume) : Sample(filepath) {
    Mix_VolumeChunk(chunk, volume);
}

Sample::~Sample() { empty(); }

void Sample::play() {
    checkIfEmpty();
    Mix_PlayChannel(-1, this->chunk, 0);
}

void Sample::play(int times) {
    checkIfEmpty();
    Mix_PlayChannel(-1, this->chunk, times - 1);
}

void Sample::set_volume(int volume) {
    checkIfEmpty();
    Mix_VolumeChunk(this->chunk, volume);
}

void Sample::empty() {
    if (this->chunk != nullptr) {
        Mix_FreeChunk(this->chunk);
        chunk = nullptr;
    }
}

void Sample::checkIfEmpty() {
    if (chunk == nullptr) {
        throw std::logic_error("El sample esta vacio");
    }
}
