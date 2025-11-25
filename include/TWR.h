// TWR.h (Tour de Contrôle)
#ifndef TWR_H
#define TWR_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Position3D.h"
#include "Avion.h"
#include "Piste.h"
#include "PositionParking.h"

class TWR {
private:
    std::string identifiant;
    std::string codeAeroport;        // Aéroport associé
    Position3D positionTour;

    std::vector<Piste> pistes;
    std::vector<PositionParking> parkings;

    std::map<std::string, std::string> avionsAuSol;  // Code avion -> Position parking
    std::vector<std::string> fileAttenteDecollage;

    double tempsAtterrissage;        // Temps fixe d'atterrissage (en secondes)
    double tempsDecollage;           // Temps fixe de décollage (en secondes)

    bool decollageTemporise;         // Flag pour temporiser décollage en cas d'urgence

public:
    TWR(const std::string& id, const std::string& codeAeroport, const Position3D& pos);

    // Getters
    std::string getIdentifiant() const { return identifiant; }
    std::string getCodeAeroport() const { return codeAeroport; }

    // Gestion des pistes
    void ajouterPiste(const Piste& piste);
    Piste* getPisteLibre();
    bool unePisteEstLibre() const;

    // Gestion des parkings
    void ajouterParking(const PositionParking& parking);
    PositionParking* getParkingLibre();
    PositionParking* getParkingPlusEloigne();

    // Gestion atterrissage
    bool autoriserAtterrissage(const std::string& codeAvion);
    void enregistrerAtterrissage(const std::string& codeAvion);
    std::string attribuerParking(const std::string& codeAvion);

    // Gestion décollage
    void enregistrerDemandeDecollage(const std::string& codeAvion);
    std::string determinerProchainDecollage();  // Priorité au plus éloigné
    bool autoriserDecollage(const std::string& codeAvion);

    // Gestion roulage
    double calculerTempsRoulage(const std::string& positionParking);

    // Gestion urgences
    void temporiserDecollages() { decollageTemporise = true; }
    void reprendreDecollages() { decollageTemporise = false; }
    bool estDecollageTemporise() const { return decollageTemporise; }
};

#endif