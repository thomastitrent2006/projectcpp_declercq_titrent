// Trajectoire.h
#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

#include <vector>
#include "Position3D.h"

enum class TypeTrajectoire {
    DIRECTE,
    CIRCULAIRE,
    APPROCHE,
    URGENCE
};

struct Trajectoire {
    TypeTrajectoire type;
    std::vector<Position3D> waypoints;  // Points de passage
    double altitudeCible;

    Trajectoire() : type(TypeTrajectoire::DIRECTE), altitudeCible(0) {}
};

#endif