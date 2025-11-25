// TWR.cpp
#include "../include/TWR.h"
#include <algorithm>

TWR::TWR(const std::string& id, const std::string& codeAeroport, const Position3D& pos)
    : identifiant(id), codeAeroport(codeAeroport), positionTour(pos),
    tempsAtterrissage(60.0), tempsDecollage(45.0), decollageTemporise(false) {
}

void TWR::ajouterPiste(const Piste& piste) {
    pistes.push_back(piste);
}

Piste* TWR::getPisteLibre() {
    for (auto& piste : pistes) {
        if (piste.estLibre()) {
            return &piste;
        }
    }
    return nullptr;
}

bool TWR::unePisteEstLibre() const {
    for (const auto& piste : pistes) {
        if (piste.estLibre()) {
            return true;
        }
    }
    return false;
}

void TWR::ajouterParking(const PositionParking& parking) {
    parkings.push_back(parking);
}

PositionParking* TWR::getParkingLibre() {
    for (auto& parking : parkings) {
        if (!parking.estOccupee()) {
            return &parking;
        }
    }
    return nullptr;
}

PositionParking* TWR::getParkingPlusEloigne() {
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

bool TWR::autoriserAtterrissage(const std::string& codeAvion) {
    if (!unePisteEstLibre()) {
        return false;
    }

    Piste* piste = getPisteLibre();
    if (piste) {
        piste->occuperPourAtterrissage(codeAvion);
        return true;
    }

    return false;
}

void TWR::enregistrerAtterrissage(const std::string& codeAvion) {
    // L'avion a atterri, libérer la piste après le temps d'occupation
    for (auto& piste : pistes) {
        if (piste.getEtat() == EtatPiste::OCCUPEE_ATTERRISSAGE) {
            // Dans une vraie implémentation, cela serait géré avec un timer
            // Pour l'instant, on libère immédiatement
        }
    }
}

std::string TWR::attribuerParking(const std::string& codeAvion) {
    PositionParking* parking = getParkingLibre();
    if (parking) {
        parking->occuper(codeAvion);
        avionsAuSol[codeAvion] = parking->getIdentifiant();
        return parking->getIdentifiant();
    }
    return "";
}

void TWR::enregistrerDemandeDecollage(const std::string& codeAvion) {
    fileAttenteDecollage.push_back(codeAvion);
}

std::string TWR::determinerProchainDecollage() {
    if (fileAttenteDecollage.empty() || decollageTemporise) {
        return "";
    }

    // Trouver l'avion au parking le plus éloigné (priorité)
    std::string avionPriorite = "";
    double distanceMax = 0.0;

    for (const auto& codeAvion : fileAttenteDecollage) {
        auto it = avionsAuSol.find(codeAvion);
        if (it != avionsAuSol.end()) {
            std::string idParking = it->second;

            for (auto& parking : parkings) {
                if (parking.getIdentifiant() == idParking &&
                    parking.getDistancePiste() > distanceMax) {
                    distanceMax = parking.getDistancePiste();
                    avionPriorite = codeAvion;
                }
            }
        }
    }

    return avionPriorite;
}

bool TWR::autoriserDecollage(const std::string& codeAvion) {
    if (decollageTemporise || !unePisteEstLibre()) {
        return false;
    }

    Piste* piste = getPisteLibre();
    if (piste) {
        piste->occuperPourDecollage(codeAvion);

        // Retirer de la file d'attente
        fileAttenteDecollage.erase(
            std::remove(fileAttenteDecollage.begin(), fileAttenteDecollage.end(), codeAvion),
            fileAttenteDecollage.end()
        );

        // Libérer le parking
        auto it = avionsAuSol.find(codeAvion);
        if (it != avionsAuSol.end()) {
            std::string idParking = it->second;
            for (auto& parking : parkings) {
                if (parking.getIdentifiant() == idParking) {
                    parking.liberer();
                    break;
                }
            }
            avionsAuSol.erase(it);
        }

        return true;
    }

    return false;
}

double TWR::calculerTempsRoulage(const std::string& positionParking) {
    for (const auto& parking : parkings) {
        if (parking.getIdentifiant() == positionParking) {
            return parking.getTempsRoulage();
        }
    }
    return 0.0;
}