#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <SDL2/SDL_mixer.h>

#include <string>

class Music {
   private:
    Mix_Music *music;

   public:
    Music(std::string const &path);
    Music(std::string const &path, int volume);

    ~Music();

    void play();

    void set_volume(int volume);
};

#endif  // __MUSIC_H__
