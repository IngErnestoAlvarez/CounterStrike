#ifndef __OTHERPLAYER_H__
#define __OTHERPLAYER_H__

#include "game_io/sdl/SdlObject.h"
#include "game_logic/player.h"

class OtherPlayer : public SdlObject {
   private:
    Player *player;
    size_t animation_pos;

   public:
    OtherPlayer(std::string const &path, int animation_frames,
                SdlWindow &window);

    ~OtherPlayer();

    void render() override;

   private:
    void update_animation();
};

#endif  // __OTHERPLAYER_H__
