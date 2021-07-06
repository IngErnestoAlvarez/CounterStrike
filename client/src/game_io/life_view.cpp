#include "game_io/life_view.h"

#include <iostream>
#include <string>

#include "Logger.h"

void lifeView::update(std::string const &newText) {
    std::string aux = "life " + newText + "/100";
    if (!aux.compare(getText())) return;
    setTexture(aux);
}

lifeView::lifeView(SdlWindow &window, std::string const &text)
    : SdlText(window, text) {}

lifeView::lifeView(SdlWindow &window, int life) : SdlText(window, "a") {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->debug("Comienza lifeView");
    std::string aux = "life " + std::to_string(life) + "/100";
    setTexture(aux);
    log->debug("Finaliza lifeView");
}

lifeView::~lifeView() {}
