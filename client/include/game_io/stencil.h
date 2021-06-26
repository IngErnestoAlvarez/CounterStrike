#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "sdl/SdlObject.h"

class Stencil : public SdlObject {
   private:
   public:
    Stencil(SdlWindow &window);
    ~Stencil();
};

#endif  // __STENCIL_H__
