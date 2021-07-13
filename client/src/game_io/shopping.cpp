#include "game_io/shopping.h"

Shopping::Shopping(SdlWindow &window)
    : ak47(AK47_M_TYPE, window),
      awp(AWP_M_TYPE, window),
      m3(M3_M_TYPE, window),
      akText(window, "1_ $2700", GREEN, 20),
      awpText(window, "2_ $4750", GREEN, 20),
      m3Text(window, "3_ $2700", GREEN, 20),
      bullets(window, "4_ $300  BULLETS", GREEN, 20) {
    akText.set_pos(0, 100);
    awpText.set_pos(0, 200);
    m3Text.set_pos(0, 300);
    bullets.set_pos(0, 400);
}

Shopping::~Shopping() {}

void Shopping::render() {
    akText.render();
    ak47.renderAbsolute(140, 100, 0);
    awpText.render();
    awp.renderAbsolute(140, 200, 0);
    m3Text.render();
    m3.renderAbsolute(140, 300, 0);
    bullets.render();
}
