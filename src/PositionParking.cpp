// PositionParking.cpp
#include "PositionParking.h"

PositionParking::PositionParking(const std::string& id, const Position3D& pos, double distPiste)
    : identifiant(id), position(pos), occupee(false), avionOccupant(""),
    distancePiste(distPiste) {
    // Calcul simplifié : temps de roulage en secondes (vitesse moyenne 20 km/h)
    tempsRoulage = (distancePiste / 1000.0) / 20.0 * 3600.0;
}

void PositionParking::occuper(const std::string& codeAvion) {
    occupee = true;
    avionOccupant = codeAvion;
}

void PositionParking::liberer() {
    occupee = false;
    avionOccupant = "";
}