#ifndef __PAUSER_H__
#define __PAUSER_H__

class Pauser {
   private:
    int stepCount;
    int maxSteps;
    bool onPause;

   public:
    Pauser(int maxSteps);

    ~Pauser();

    bool load();

    void update();

    void pause();
};

#endif  // __PAUSER_H__
