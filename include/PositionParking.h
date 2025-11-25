// PositionParking.h
#ifndef POSITION_PARKING_H
#define POSITION_PARKING_H

#include <string>
#include "Position3D.h"

class PositionParking {
private:
    std::string identifiant;         // Ex: P1, P2, ..., Pn
    Position3D position;
    bool occupee;
    std::string avionOccupant;
    double distancePiste;            // Distance jusqu'à la piste (en mètres)
    double tempsRoulage;             // Temps de roulage jusqu'à la piste (en secondes)

public:
    PositionParking(const std::string& id, const Position3D& pos, double distPiste);

    bool estOccupee() const { return occupee; }
    std::string getIdentifiant() const { return identifiant; }
    double getTempsRoulage() const { return tempsRoulage; }
    double getDistancePiste() const { return distancePiste; }

    void occuper(const std::string& codeAvion);
    void liberer();
};

#endif