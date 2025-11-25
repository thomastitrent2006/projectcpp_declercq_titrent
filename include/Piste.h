// Piste.h
#ifndef PISTE_H
#define PISTE_H

#include <string>
#include "Position3D.h"

enum class EtatPiste {
    LIBRE,
    OCCUPEE_ATTERRISSAGE,
    OCCUPEE_DECOLLAGE
};

class Piste {
private:
    std::string identifiant;         // Ex: "09L", "27R"
    Position3D debut;
    Position3D fin;
    EtatPiste etat;
    double tempsOccupation;          // Temps fixe d'occupation (en secondes)
    std::string avionOccupant;       // Code de l'avion occupant la piste

public:
    Piste(const std::string& id, const Position3D& debut, const Position3D& fin);

    bool estLibre() const { return etat == EtatPiste::LIBRE; }
    EtatPiste getEtat() const { return etat; }
    void occuperPourAtterrissage(const std::string& codeAvion);
    void occuperPourDecollage(const std::string& codeAvion);
    void liberer();
    double getTempsOccupation() const { return tempsOccupation; }
};

#endif