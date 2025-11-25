// CCR.h (Centre de Contrôle Régional)
#ifndef CCR_H
#define CCR_H

#include <string>
#include <vector>
#include <memory>
#include "Position3D.h"
#include "Avion.h"

class CCR {
private:
    std::string identifiant;
    Position3D centre;
    double rayon;                    // Rayon de la zone (en km)
    double altitudeMin;
    double altitudeMax;

    std::vector<std::string> aeroportsGeres;  // Codes IATA des aéroports
    int capaciteMaxSimultanee;       // Nombre max d'avions gérés simultanément

public:
    CCR(const std::string& id, const Position3D& centre, double rayon);

    // Getters
    std::string getIdentifiant() const { return identifiant; }
    Position3D getCentre() const { return centre; }
    double getRayon() const { return rayon; }

    // Vérifications
    bool contientPosition(const Position3D& pos) const;
    bool peutAccepterAvion() const;

    // Gestion des aéroports
    void ajouterAeroport(const std::string& codeAeroport);
    bool gereAeroport(const std::string& codeAeroport) const;

    // Gestion du trafic
    void planifierVol(const std::string& origine, const std::string& destination);
    bool verifierCapacite(const std::string& aeroportDestination) const;
};

#endif