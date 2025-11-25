// DonneesPartagees.h
#ifndef DONNEES_PARTAGEES_H
#define DONNEES_PARTAGEES_H

#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include "Avion.h"
#include "Message.h"
#include "CCR.h"
#include "APP.h"
#include "TWR.h"

// Structure pour partager les données entre threads
struct DonneesPartagees {
    // Avions
    std::vector<std::shared_ptr<Avion>> avions;
    std::mutex mutexAvions;

    // Messages par zone de contrôle
    std::map<std::string, std::vector<Message>> messagesParZone;  // identifiant zone -> messages
    std::mutex mutexMessages;

    // Contrôleurs
    std::vector<std::shared_ptr<CCR>> centres_ccr;
    std::vector<std::shared_ptr<APP>> centres_app;
    std::vector<std::shared_ptr<TWR>> tours_twr;

    // Ajouter un avion de manière thread-safe
    void ajouterAvion(std::shared_ptr<Avion> avion);

    // Envoyer un message de manière thread-safe
    void envoyerMessage(const std::string& idZoneDestination, const Message& msg);

    // Récupérer les messages pour un contrôleur
    std::vector<Message> getMessages(const std::string& idZone);

    // Vider les messages lus
    void viderMessages(const std::string& idZone);
};

#endif