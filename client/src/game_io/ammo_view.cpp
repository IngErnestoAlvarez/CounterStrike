#include "game_io/ammo_view.h"

void AmmoView::update(std::string const &newText) {
    std::string aux = "ammo " + newText + "/30";
    if (!aux.compare(getText())) return;
    setTexture(aux);
}

AmmoView::AmmoView(SdlWindow &window, std::string const &text)
    : SdlText(window, text) {}

AmmoView::AmmoView(SdlWindow &window,int ammo)
    : SdlText(window, std::to_string(ammo)) {}

AmmoView::~AmmoView() {}
