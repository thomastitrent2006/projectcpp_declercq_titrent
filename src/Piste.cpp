// Piste.cpp
#include "../include/Piste.h"

Piste::Piste(const std::string& id, const Position3D& debut, const Position3D& fin)
    : identifiant(id), debut(debut), fin(fin), etat(EtatPiste::LIBRE),
    tempsOccupation(60.0), avionOccupant("") {
}

void Piste::occuperPourAtterrissage(const std::string& codeAvion) {
    etat = EtatPiste::OCCUPEE_ATTERRISSAGE;
    avionOccupant = codeAvion;
}

void Piste::occuperPourDecollage(const std::string& codeAvion) {
    etat = EtatPiste::OCCUPEE_DECOLLAGE;
    avionOccupant = codeAvion;
}

void Piste::liberer() {
    etat = EtatPiste::LIBRE;
    avionOccupant = "";
}