// Avion.h
#ifndef AVION_H
#define AVION_H

#include <string>
#include <chrono>
#include "Position3D.h"
#include "Vitesse.h"
#include "Trajectoire.h"

enum class EtatAvion {
    EN_ROUTE,
    EN_APPROCHE,
    EN_ATTENTE,
    EN_ATTERRISSAGE,
    AU_SOL,
    EN_ROULAGE,
    EN_DECOLLAGE,
    URGENCE
};

class Avion {
private:
    std::string code;                    // Ex: AFR10
    Position3D position;
    Vitesse vitesse;
    Trajectoire trajectoire;
    EtatAvion etat;

    double carburant;                    // En litres ou kg
    double consommationParHeure;         // En litres/h ou kg/h
    bool urgence;
    std::string typeUrgence;             // "CARBURANT", "TECHNIQUE", etc.

    std::string positionParking;         // Ex: P1, P2, ..., Pn
    std::chrono::system_clock::time_point tempsArriveeParking;
    int dureeParkingMinutes;             // Durée de stationnement

public:
    Avion(const std::string& code, const Position3D& pos, const Vitesse& vit);

    // Getters
    std::string getCode() const { return code; }
    Position3D getPosition() const { return position; }
    Vitesse getVitesse() const { return vitesse; }
    EtatAvion getEtat() const { return etat; }
    double getCarburant() const { return carburant; }
    bool estEnUrgence() const { return urgence; }
    std::string getPositionParking() const { return positionParking; }

    // Setters
    void setPosition(const Position3D& pos) { position = pos; }
    void setVitesse(const Vitesse& vit) { vitesse = vit; }
    void setTrajectoire(const Trajectoire& traj) { trajectoire = traj; }
    void setEtat(EtatAvion nouvelEtat) { etat = nouvelEtat; }
    void setPositionParking(const std::string& parking) { positionParking = parking; }
    void declencherUrgence(const std::string& type);

    // Méthodes de simulation
    void consommerCarburant(double dureeHeures);
    void mettreAJourPosition(double deltaTemps);
};

#endif