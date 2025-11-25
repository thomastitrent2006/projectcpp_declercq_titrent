// APP.h (Contrôle d'Approche)
#ifndef APP_H
#define APP_H

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "Position3D.h"
#include "Avion.h"
#include "Trajectoire.h"

class APP {
private:
    std::string identifiant;
    std::string codeAeroport;        // Aéroport associé
    Position3D centreZone;
    double rayonZone;                // Rayon de la zone d'approche (en km)
    double altitudeMin;
    double altitudeMax;
    
    double rayonCircuitAttente;      // Rayon du circuit d'attente circulaire
    double altitudeCircuitAttente;   // Altitude du circuit d'attente
    
    std::queue<std::string> fileAttenteAtterrissage;  // File d'attente des avions
    std::vector<std::string> avionsEnApproche;        // Avions actuellement en approche
    
    int capaciteMaxCircuit;          // Nombre max d'avions dans le circuit
    
public:
    APP(const std::string& id, const std::string& codeAeroport, 
        const Position3D& centre, double rayon);
    
    // Getters
    std::string getIdentifiant() const { return identifiant; }
    std::string getCodeAeroport() const { return codeAeroport; }
    Position3D getCentreZone() const { return centreZone; }
    double getRayonZone() const { return rayonZone; }
    
    // Vérifications
    bool contientPosition(const Position3D& pos) const;
    bool peutAccepterAvion() const;
    
    // Gestion du trafic
    void enregistrerEntree(const std::string& codeAvion);
    Trajectoire genererTrajectoireCirculaire(const Position3D& positionAvion);
    Trajectoire genererTrajectoireUrgence(const Position3D& positionAvion);
    
    // Gestion de la file d'attente
    void ajouterFileAttente(const std::string& codeAvion);
    void ajouterFilePriorite(const std::string& codeAvion); // Pour urgences
    std::string getProchainAvionAtterrir();
    
    // Communication avec TWR
    bool demanderPisteLibre();
    void notifierDemandeTemporisationDecollage();
};

#endif