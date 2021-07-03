#ifndef __BODY_PROXY_H__
#define __BODY_PROXY_H__

#include <string>

class BodyProxy {
   private:
    const std::string path2image;

   public:
    BodyProxy();

    ~BodyProxy();

    int getX();

    int getY();

    const std::string &getPath();
};

#endif
