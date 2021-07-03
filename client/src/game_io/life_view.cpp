#include "game_io/life_view.h"

#include <iostream>

void lifeView::update(std::string const &newText) {
    std::cout << "Entra update" << std::endl;
    std::string aux = "life " + newText + "/100";
    if (!aux.compare(getText())) return;
    setTexture(aux);
}

lifeView::lifeView(SdlWindow &window, std::string const &text)
    : SdlText(window, text) {}

lifeView::~lifeView() {}