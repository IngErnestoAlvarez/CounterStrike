#ifndef __AMMO_VIEW_H__
#define __AMMO_VIEW_H__

#include "game_io/sdl/text/SdlText.h"

class AmmoView : public SdlText {
   private:
    void update(std::string const &newText) override;

   public:
    AmmoView(SdlWindow &, std::string const &text);

    ~AmmoView();
};

#endif  // __AMMO_VIEW_H__
