// Aeroport.cpp
#include "../include/Aeroport.h"
#include <algorithm>

Aeroport::Aeroport(const std::string& code, const std::string& nom, const Position3D& pos)
    : code(code), nom(nom), position(pos), rayonZoneApproche(50.0),
    rayonCircuitAttente(10.0) {
}

void Aeroport::ajouterPiste(const Piste& piste) {
    pistes.push_back(piste);
}

void Aeroport::ajouterParking(const PositionParking& parking) {
    parkings.push_back(parking);
}

Piste* Aeroport::getPisteLibre() {
    for (auto& piste : pistes) {
        if (piste.estLibre()) {
            return &piste;
        }
    }
    return nullptr;  // Aucune piste libre
}

PositionParking* Aeroport::getParkingLibre() {
    for (auto& parking : parkings) {
        if (!parking.estOccupee()) {
            return &parking;
        }
    }
    return nullptr;  // Aucun parking libre
}

PositionParking* Aeroport::getParkingPlusEloigne() {
    PositionParking* plusEloigne = nullptr;
    double distanceMax = 0.0;

    for (auto& parking : parkings) {
        if (parking.estOccupee() && parking.getDistancePiste() > distanceMax) {
            distanceMax = parking.getDistancePiste();
            plusEloigne = &parking;
        }
    }

    return plusEloigne;
}