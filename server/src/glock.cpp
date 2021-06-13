#include "../include/glock.h"
#include "../include/configuration.h"

Glock::Glock(const Configuration& config)
    : Weapon("Glock", config) {
}

void Glock::use() {}
