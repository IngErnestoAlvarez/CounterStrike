#ifndef __WEAPON_PROXY_H__
#define __WEAPON_PROXY_H__

#include <string>

class WeaponProxy {
   private:
    const std::string path2image;

   public:
    WeaponProxy();

    ~WeaponProxy();

    int getAmmo();

    int getMaxAmmo();

    const std::string &getPath();
};

#endif
