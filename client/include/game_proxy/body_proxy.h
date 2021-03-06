#ifndef __BODY_PROXY_H__
#define __BODY_PROXY_H__

#include <mutex>
#include <string>
#include <vector>

#include "body_cointainer.h"

typedef std::vector<BodyContainer> bodyVector;

class BodyProxy {
   private:
    std::vector<BodyContainer> bodies;
    std::mutex mutex;

   public:
    BodyProxy();

    ~BodyProxy();

    bodyVector::iterator getIterator();

    bodyVector::iterator getEnd();

    void lock();

    void unlock();

    void setBodies(char *data, size_t n);

    void setStatics(char *data, size_t n);

   private:
    void setWithBiggerData(char *data, size_t n);

    void setWithSmallerData(char *data, size_t n);

    void setStaticWithBiggerData(char *data, size_t n);
};

#endif
