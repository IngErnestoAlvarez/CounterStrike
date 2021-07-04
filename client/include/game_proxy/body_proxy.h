#ifndef __BODY_PROXY_H__
#define __BODY_PROXY_H__

#include <string>
#include <vector>

#include "body_cointainer.h"

class BodyProxy {
   private:
    std::vector<BodyContainer> bodies;

   public:
    BodyProxy();

    ~BodyProxy();

    std::vector<BodyContainer>::iterator getIterator();

    std::vector<BodyContainer>::iterator getEnd();

    void setBodies(char *data, size_t n);

   private:
    void setWithBiggerData(char *data, size_t n);

    void setWithSmallerData(char *data, size_t n);
};

#endif
