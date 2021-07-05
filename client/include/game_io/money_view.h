#ifndef MONEY_VIEW_H
#define MONEY_VIEW_H

#include "game_io/sdl/text/SdlText.h"

class MoneyView : public SdlText {
   private:
    void update(std::string const &newText) override;

   public:
    MoneyView(SdlWindow &, std::string const &text);
    MoneyView(SdlWindow &, int money);

    ~MoneyView();
};

#endif  // MONEY_VIEW_H
