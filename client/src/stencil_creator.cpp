#include "stencil_creator.h"

#define multiplier 1.5

const unsigned char bluegreen[] = {255, 255, 255};
StencilCreator::StencilCreator(unsigned int screenWidth,
                               unsigned int screenHeight) {
    stencilWidth = screenWidth * multiplier;
    stencilHeight = screenHeight * multiplier;
}

StencilCreator::~StencilCreator() {}

void StencilCreator::create() {
    using namespace cimg_library;
    CImg<unsigned char> bg(stencilWidth, stencilHeight, 1, 3, 0);

    bg.draw_circle(stencilWidth / 2, stencilHeight / 2, 100, bluegreen);
    bg.draw_triangle(stencilWidth / 2, stencilHeight / 2, stencilWidth, -100,
                     stencilWidth, stencilHeight + 100, bluegreen);
    bg.save("assets/sprites/stencil.png");
}
