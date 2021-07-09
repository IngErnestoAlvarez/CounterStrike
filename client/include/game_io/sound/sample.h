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

    Sample &operator=(Sample const &sample) = delete;
    Sample &operator=(Sample &&sample);

    ~Sample();

    void play();
    void play(int times);
    void set_volume(int volume);

   private:
    void empty();
    void checkIfEmpty();
};

#endif
