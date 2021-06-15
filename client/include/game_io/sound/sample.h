#ifndef __SAMPLE_H__
#define __SAMPLE_H__
#include <SDL2/SDL_mixer.h>

#include <string>

class Sample {
   private:
    Mix_Chunk *chunk;

   public:
    Sample(const std::string &filepath, int volume);
    Sample(const std::string &filepath);

    ~Sample();

    void play();
    void play(int times);
    void set_volume(int volume);
};

#endif
