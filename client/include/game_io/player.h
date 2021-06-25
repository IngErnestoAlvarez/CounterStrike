#ifndef __PLAYER_VIEW_H__
#define __PLAYER_VIEW_H__

#include <string>

#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_logic/player.h"

class PlayerView : public SdlObject {
   private:
    Player *player;

   public:
    PlayerView(std::string const &path, int animation_frames,
               SdlWindow &window);
    PlayerView(std::string const &path, int animation_frames, SdlWindow &window,
               Player *player);

    ~PlayerView();
    // void moveUp() override;
    // void moveDown() override;
    // void moveRight() override;
    // void moveLeft() override;
    void mouse_mov(int x, int y) override;
    void render() override;
};

#endif
