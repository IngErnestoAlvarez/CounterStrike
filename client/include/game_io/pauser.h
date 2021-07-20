#ifndef __PAUSER_H__
#define __PAUSER_H__

#include <atomic>

class Pauser {
   private:
    int stepCount;
    int maxSteps;
    std::atomic_bool onPause;

   public:
    Pauser(int maxSteps);

    ~Pauser();

    bool load();

    void update();

    void pause();
};

#endif  // __PAUSER_H__
