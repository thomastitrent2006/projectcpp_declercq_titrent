// Vitesse.cpp
#include "Vitesse.h"
#include <cmath>

double Vitesse::getNorme() const {
    return std::sqrt(vx * vx + vy * vy + vz * vz);
}