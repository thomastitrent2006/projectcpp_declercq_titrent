// DonneesPartagees.cpp
#include "../include/DonneesPartagees.h"
#include <algorithm>

void DonneesPartagees::ajouterAvion(std::shared_ptr<Avion> avion) {
    std::lock_guard<std::mutex> lock(mutexAvions);
    avions.push_back(avion);
}

void DonneesPartagees::envoyerMessage(const std::string& idZoneDestination, const Message& msg) {
    std::lock_guard<std::mutex> lock(mutexMessages);
    messagesParZone[idZoneDestination].push_back(msg);
}

std::vector<Message> DonneesPartagees::getMessages(const std::string& idZone) {
    std::lock_guard<std::mutex> lock(mutexMessages);

    if (messagesParZone.find(idZone) != messagesParZone.end()) {
        return messagesParZone[idZone];
    }

    return std::vector<Message>();
}

void DonneesPartagees::viderMessages(const std::string& idZone) {
    std::lock_guard<std::mutex> lock(mutexMessages);

    if (messagesParZone.find(idZone) != messagesParZone.end()) {
        messagesParZone[idZone].clear();
    }
}