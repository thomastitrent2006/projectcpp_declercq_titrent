// main.cpp
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../include/Avion.h"
#include "../include/APP.h"
#include "../include/TWR.h"
#include "../include/AffichageConsole.h"
#include "../include/JSONLogger.h"
#include "../include/FichierConfig.h"
#include "../include/GenerateurAleatoire.h"

int main() {
    std::cout << "=== SYSTEME DE CONTROLE AERIEN ===\n\n";

    // Initialiser le générateur aléatoire
    GenerateurAleatoire::initialiser();

    // Créer le logger JSON
    JsonLogger logger("logs_atc.json");
    logger.logEvenement("DEMARRAGE", "Initialisation du système ATC");

    // Option 1: Charger depuis un fichier
    // std::vector<Avion*> avions = FichierConfig::chargerAvionsDepuisFichier("avions.txt");

    // Option 2: Générer aléatoirement
    std::cout << "Génération de 5 avions aléatoires...\n";
    std::vector<Avion*> avions = GenerateurAleatoire::genererAvionsAleatoires(5);

    // Créer les contrôleurs
    Position3D centreAeroport(0, 0, 0);
    APP app("APP_LFLL", "LFLL", centreAeroport, 50.0);
    TWR twr("TWR_LFLL", "LFLL");

    // Ajouter quelques pistes et parkings
    twr.ajouterPiste(Piste("09L"));
    twr.ajouterPiste(Piste("27R"));
    twr.ajouterParking(PositionParking("P1", Position3D(-100, -100, 0), 200));
    twr.ajouterParking(PositionParking("P2", Position3D(-150, -150, 0), 300));

    logger.logEvenement("CONFIGURATION", "2 pistes et 2 parkings configurés");

    // Mettre quelques avions en approche
    if (avions.size() > 0) avions[0]->setEtat(EtatAvion::EN_APPROCHE);
    if (avions.size() > 1) avions[1]->setEtat(EtatAvion::EN_APPROCHE);
    if (avions.size() > 2) avions[2]->setEtat(EtatAvion::AU_SOL);

    // Simuler quelques cycles d'affichage
    for (int i = 0; i < 3; ++i) {
        AffichageConsole::clearScreen();

        std::cout << "\n=== CYCLE " << (i + 1) << " ===\n";

        // Afficher les positions
        AffichageConsole::afficherPositionsAvions(avions);

        // Afficher APP
        AffichageConsole::afficherAPP(app, avions);

        // Afficher TWR
        AffichageConsole::afficherTWR(twr, avions);

        // Logger les positions
        for (const auto& avion : avions) {
            logger.logPosition(*avion);
        }

        AffichageConsole::afficherSeparateur();

        // Attendre 2 secondes
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    // Sauvegarder dans un fichier texte
    FichierConfig::sauvegarderAvionsDansFichier("avions_sauvegarde.txt", avions);

    logger.logEvenement("ARRET", "Fin de la simulation");

    // Nettoyer la mémoire
    for (auto avion : avions) {
        delete avion;
    }

    std::cout << "\n\nSimulation terminée. Logs sauvegardés dans logs_atc.json\n";

    return 0;
}
