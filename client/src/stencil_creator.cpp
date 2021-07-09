#include "stencil_creator.h"

#define multiplier 2

const unsigned char bluegreen[] = {255, 255, 255};
StencilCreator::StencilCreator(unsigned int screenWidth,
                               unsigned int screenHeight) {
    stencilWidth = screenWidth * multiplier;
    stencilHeight = screenHeight * multiplier;
}

StencilCreator::~StencilCreator() {}

void StencilCreator::create(int circleRadius, int viewRange) {
    using namespace cimg_library;
    CImg<unsigned char> bg(stencilWidth, stencilHeight, 1, 3, 0);

    bg.draw_circle(stencilWidth / 2, stencilHeight / 2, circleRadius,
                   bluegreen);
    bg.draw_triangle(stencilWidth / 2, stencilHeight / 2, stencilWidth,
                     -viewRange, stencilWidth, stencilHeight + viewRange,
                     bluegreen);
    bg.save("assets/sprites/stencil.png");
}
