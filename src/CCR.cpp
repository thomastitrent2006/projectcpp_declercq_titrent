// CCR.cpp
#include "../include/CCR.h"
#include <cmath>
#include <algorithm>

CCR::CCR(const std::string& id, const Position3D& centre, double rayon)
    : identifiant(id), centre(centre), rayon(rayon),
    altitudeMin(3000.0), altitudeMax(12000.0), capaciteMaxSimultanee(50) {
}

bool CCR::contientPosition(const Position3D& pos) const {
    // Vérification cylindrique : distance 2D + altitude
    double dx = pos.x - centre.x;
    double dy = pos.y - centre.y;
    double distance2D = std::sqrt(dx * dx + dy * dy);

    return (distance2D <= rayon) &&
        (pos.altitude >= altitudeMin) &&
        (pos.altitude <= altitudeMax);
}

bool CCR::peutAccepterAvion() const {
    // À implémenter avec le comptage réel d'avions
    return true;  // Simplifié pour l'instant
}

void CCR::ajouterAeroport(const std::string& codeAeroport) {
    aeroportsGeres.push_back(codeAeroport);
}

bool CCR::gereAeroport(const std::string& codeAeroport) const {
    return std::find(aeroportsGeres.begin(), aeroportsGeres.end(), codeAeroport)
        != aeroportsGeres.end();
}

void CCR::planifierVol(const std::string& origine, const std::string& destination) {
    // Logique de planification à implémenter
    // Pour l'instant, méthode vide
}

bool CCR::verifierCapacite(const std::string& aeroportDestination) const {
    // Vérifier si l'aéroport peut accepter plus de vols
    // À implémenter avec comptage réel
    return true;  // Simplifié
}