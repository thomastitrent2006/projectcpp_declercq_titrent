// Aeroport.h
#ifndef AEROPORT_H
#define AEROPORT_H

#include <string>
#include <vector>
#include "Position3D.h"
#include "Piste.h"
#include "PositionParking.h"

class Aeroport {
private:
    std::string code;                // Ex: LFLL (Lille), LFMN (Nice)
    std::string nom;
    Position3D position;             // Position centrale de l'aéroport

    std::vector<Piste> pistes;
    std::vector<PositionParking> parkings;

    double rayonZoneApproche;        // Rayon de la zone APP (en km)
    double rayonCircuitAttente;      // Rayon du circuit d'attente circulaire

public:
    Aeroport(const std::string& code, const std::string& nom, const Position3D& pos);

    void ajouterPiste(const Piste& piste);
    void ajouterParking(const PositionParking& parking);

    std::string getCode() const { return code; }
    Position3D getPosition() const { return position; }
    Piste* getPisteLibre();
    PositionParking* getParkingLibre();
    PositionParking* getParkingPlusEloigne();
};

#endif