// Avion.cpp
#include "Avion.h"

Avion::Avion(const std::string& code, const Position3D& pos, const Vitesse& vit)
    : code(code), position(pos), vitesse(vit), etat(EtatAvion::EN_ROUTE),
    carburant(10000.0), consommationParHeure(2000.0), urgence(false),
    dureeParkingMinutes(30) {
}

void Avion::declencherUrgence(const std::string& type) {
    urgence = true;
    typeUrgence = type;
    etat = EtatAvion::URGENCE;
}

void Avion::consommerCarburant(double dureeHeures) {
    carburant -= consommationParHeure * dureeHeures;
    if (carburant < 1000.0 && !urgence) {  // Seuil critique
        declencherUrgence("CARBURANT");
    }
}

void Avion::mettreAJourPosition(double deltaTemps) {
    // Mise à jour simple de la position en fonction de la vitesse
    position.x += vitesse.vx * deltaTemps;
    position.y += vitesse.vy * deltaTemps;
    position.altitude += vitesse.vz * deltaTemps;

    // Consommer du carburant (deltaTemps en secondes, conversion en heures)
    consommerCarburant(deltaTemps / 3600.0);
}