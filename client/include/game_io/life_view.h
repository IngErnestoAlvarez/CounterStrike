#ifndef __LIFE_VIEW_H__
#define __LIFE_VIEW_H__

#include <string>

#include "game_io/sdl/text/SdlText.h"

class lifeView : public SdlText {
   private:
    void update(std::string const &newText) override;

   public:
    lifeView(SdlWindow &, std::string const &text);
    lifeView(SdlWindow &, int life);

    ~lifeView();
};

#endif  // __LIFE_VIEW_H__
