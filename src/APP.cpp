// APP.cpp
#include "../include/APP.h"
#include <cmath>

APP::APP(const std::string& id, const std::string& codeAeroport,
    const Position3D& centre, double rayon)
    : identifiant(id), codeAeroport(codeAeroport), centreZone(centre),
    rayonZone(rayon), altitudeMin(500.0), altitudeMax(3000.0),
    rayonCircuitAttente(10.0), altitudeCircuitAttente(1500.0),
    capaciteMaxCircuit(10) {
}

bool APP::contientPosition(const Position3D& pos) const {
    double dx = pos.x - centreZone.x;
    double dy = pos.y - centreZone.y;
    double distance2D = std::sqrt(dx * dx + dy * dy);

    return (distance2D <= rayonZone) &&
        (pos.altitude >= altitudeMin) &&
        (pos.altitude <= altitudeMax);
}

bool APP::peutAccepterAvion() const {
    return avionsEnApproche.size() < static_cast<size_t>(capaciteMaxCircuit);
}

void APP::enregistrerEntree(const std::string& codeAvion) {
    avionsEnApproche.push_back(codeAvion);
}

Trajectoire APP::genererTrajectoireCirculaire(const Position3D& positionAvion) {
    Trajectoire traj;
    traj.type = TypeTrajectoire::CIRCULAIRE;
    traj.altitudeCible = altitudeCircuitAttente;

    // Générer des waypoints en cercle autour de l'aéroport
    const int nbPoints = 8;  // 8 points pour faire le cercle
    for (int i = 0; i < nbPoints; ++i) {
        double angle = (2.0 * M_PI * i) / nbPoints;
        Position3D waypoint;
        waypoint.x = centreZone.x + rayonCircuitAttente * std::cos(angle);
        waypoint.y = centreZone.y + rayonCircuitAttente * std::sin(angle);
        waypoint.altitude = altitudeCircuitAttente;
        traj.waypoints.push_back(waypoint);
    }

    return traj;
}

Trajectoire APP::genererTrajectoireUrgence(const Position3D& positionAvion) {
    Trajectoire traj;
    traj.type = TypeTrajectoire::URGENCE;
    traj.altitudeCible = 500.0;  // Descente rapide

    // Trajectoire directe vers la piste
    Position3D approche = centreZone;
    approche.altitude = 500.0;
    traj.waypoints.push_back(approche);

    Position3D finale = centreZone;
    finale.altitude = 100.0;
    traj.waypoints.push_back(finale);

    return traj;
}

void APP::ajouterFileAttente(const std::string& codeAvion) {
    fileAttenteAtterrissage.push(codeAvion);
}

void APP::ajouterFilePriorite(const std::string& codeAvion) {
    // Pour les urgences, on utilise une approche simple :
    // créer une nouvelle queue temporaire avec l'avion urgent en premier
    std::queue<std::string> nouvelleFile;
    nouvelleFile.push(codeAvion);

    while (!fileAttenteAtterrissage.empty()) {
        nouvelleFile.push(fileAttenteAtterrissage.front());
        fileAttenteAtterrissage.pop();
    }

    fileAttenteAtterrissage = nouvelleFile;
}

std::string APP::getProchainAvionAtterrir() {
    if (fileAttenteAtterrissage.empty()) {
        return "";
    }

    std::string codeAvion = fileAttenteAtterrissage.front();
    fileAttenteAtterrissage.pop();
    return codeAvion;
}

bool APP::demanderPisteLibre() {
    // Cette méthode sera utilisée pour communiquer avec la TWR
    // L'implémentation réelle se fera via les messages
    return true;  // Simplifié
}

void APP::notifierDemandeTemporisationDecollage() {
    // Communication avec TWR via messages
    // À implémenter avec le système de messages
}