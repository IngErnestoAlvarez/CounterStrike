#ifndef __STENCIL_CREATOR_H__
#define __STENCIL_CREATOR_H__

#include <CImg.h>

#define cimg_display 0

class StencilCreator {
   private:
    unsigned int stencilWidth;
    unsigned int stencilHeight;

   public:
    StencilCreator(unsigned int screenWidth, unsigned int screenHeight);
    ~StencilCreator();

    void create(int circleRadius, int viewRange);
};

#endif  // __STENCIL_CREATOR_H__
