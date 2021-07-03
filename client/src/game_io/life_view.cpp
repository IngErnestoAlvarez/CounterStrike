#include "game_io/life_view.h"

void lifeView::update(std::string const &newText) {
    std::string aux = "life " + newText + "/100";
    if (!aux.compare(getText())) return;
    setTexture(aux);
}

lifeView::lifeView(SdlWindow &window, std::string const &text)
    : SdlText(window, text) {}

lifeView::~lifeView() {}
