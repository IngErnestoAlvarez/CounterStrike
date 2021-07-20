#include "game_io/pauser.h"

Pauser::Pauser(int maxSteps)
    : stepCount(0), maxSteps(maxSteps), onPause(false) {}

Pauser::~Pauser() {}

bool Pauser::load() { return onPause.load(); }

void Pauser::update() {
    if (!onPause) return;
    stepCount++;
    if (stepCount == maxSteps) {
        onPause = false;
        stepCount = 0;
    }
}

void Pauser::pause() { onPause = true; }
