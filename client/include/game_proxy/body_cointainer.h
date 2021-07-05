#ifndef BODY_COINTAINER_H
#define BODY_COINTAINER_H

#include <iostream>

#include "types.h"

struct BodyContainer {
    BodyType tipo;
    uint16_t posx;
    uint16_t posy;
    float angle;
};

#endif  // BODY_COINTAINER_H
