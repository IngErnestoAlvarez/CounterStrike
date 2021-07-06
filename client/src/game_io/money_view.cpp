#include "game_io/money_view.h"

void MoneyView::update(std::string const &newText) {
    std::string aux = "$" + newText;
    if (!aux.compare(getText())) return;
    setTexture(aux);
}

MoneyView::MoneyView(SdlWindow &window, std::string const &text)
    : SdlText(window, text) {}

MoneyView::MoneyView(SdlWindow &window, int money) : SdlText(window, "a") {
    std::string aux = "$" + std::to_string(money);
    setTexture(aux);
}

MoneyView::~MoneyView() {}
