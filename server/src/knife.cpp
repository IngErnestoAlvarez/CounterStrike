#include "../include/knife.h"
#include "../include/configuration.h"

Knife::Knife(const Configuration& config)
    : Weapon("Knife", config) {

}

void Knife::use() {}
