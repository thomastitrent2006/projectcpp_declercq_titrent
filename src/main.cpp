#ifndef ATC_DATA_STRUCTURES_HPP
#define ATC_DATA_STRUCTURES_HPP

#include <string>
#include <vector>
#include <chrono>
#include <mutex>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// ============================================================================
// STRUCTURES DE BASE
// ============================================================================

/**
 * Position 3D d'un avion (x, y, altitude)
 * Compatible avec SFML pour l'affichage 2D
 */
struct Position {
    double x;           // Position horizontale (km)
    double y;           // Position horizontale (km)
    double altitude;    // Altitude (mètres)

    Position(double x = 0.0, double y = 0.0, double alt = 0.0)
        : x(x), y(y), altitude(alt) {
    }

    // Conversion vers sf::Vector2f pour affichage SFML
    sf::Vector2f toSFMLVector() const {
        return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    }
};

/**
 * Vecteur vitesse 3D
 */
struct Velocity {
    double vx;          // Vitesse horizontale X (km/h)
    double vy;          // Vitesse horizontale Y (km/h)
    double vz;          // Vitesse verticale (m/s)

    Velocity(double vx = 0.0, double vy = 0.0, double vz = 0.0)
        : vx(vx), vy(vy), vz(vz) {
    }

    double getSpeed() const;  // Vitesse totale
};

/**
 * Trajectoire assignée à un avion
 */
struct Trajectory {
    std::vector<Position> waypoints;  // Points de passage
    double targetAltitude;             // Altitude cible
    double targetSpeed;                // Vitesse cible (km/h)

    Trajectory() : targetAltitude(0.0), targetSpeed(0.0) {}
};

/**
 * État d'un avion
 */
enum class AircraftState {
    EN_ROUTE,           // En croisière (gestion CCR)
    APPROACHING,        // En approche (gestion APP)
    LANDING,            // En phase d'atterrissage
    TAXIING_IN,         // Roulage vers parking
    PARKED,             // Stationné
    TAXIING_OUT,        // Roulage vers piste
    TAKING_OFF,         // En phase de décollage
    DEPARTED            // Parti
};

/**
 * Niveau de priorité d'un avion
 */
enum class Priority {
    NORMAL,
    HIGH,
    EMERGENCY
};

/**
 * État d'urgence
 */
struct EmergencyStatus {
    bool isEmergency;
    std::string reason;     // "LOW_FUEL", "TECHNICAL", etc.

    EmergencyStatus() : isEmergency(false), reason("") {}
};

// ============================================================================
// STRUCTURE AVION
// ============================================================================

/**
 * Données complètes d'un avion
 */
struct AircraftData {
    // Identification
    std::string callsign;           // Code d'identification (ex: AFR10)
    std::string type;               // Type d'avion (ex: A320, B737)

    // Position et mouvement
    Position position;
    Velocity velocity;
    Trajectory assignedTrajectory;

    // Carburant
    double fuelLevel;               // Niveau de carburant (kg)
    double fuelConsumption;         // Consommation (kg/h)

    // État
    AircraftState state;
    Priority priority;
    EmergencyStatus emergency;

    // Parking assigné (si applicable)
    std::string assignedParking;    // Ex: "P1", "P2"

    // Timestamps
    std::chrono::system_clock::time_point entryTime;
    std::chrono::system_clock::time_point parkingArrivalTime;
    double parkingDuration;         // Durée de stationnement (secondes)

    AircraftData(const std::string& cs = "")
        : callsign(cs), type("GENERIC"),
        fuelLevel(5000.0), fuelConsumption(2000.0),
        state(AircraftState::EN_ROUTE),
        priority(Priority::NORMAL),
        assignedParking(""),
        parkingDuration(300.0) {
    }
};

// ============================================================================
// ZONES DE CONTRÔLE
// ============================================================================

/**
 * Zone de contrôle d'un centre APP
 */
struct APPControlZone {
    Position center;                // Centre (aéroport)
    double radius;                  // Rayon de contrôle (km)
    double minAltitude;             // Altitude min (m)
    double maxAltitude;             // Altitude max (m)

    APPControlZone()
        : radius(50.0), minAltitude(0.0), maxAltitude(10000.0) {
    }
};

/**
 * Zone de contrôle d'un CCR
 */
struct CCRControlZone {
    std::string name;               // Nom du secteur
    std::vector<Position> boundaries; // Polygone de délimitation
    double minAltitude;
    double maxAltitude;

    CCRControlZone() : name(""), minAltitude(10000.0), maxAltitude(15000.0) {}
};

/**
 * Configuration d'un aéroport (TWR)
 */
struct AirportConfiguration {
    std::string icaoCode;           // Code ICAO (ex: LFQQ pour Lille)
    Position location;

    // Piste
    double runwayHeading;           // Cap de la piste (degrés)
    double runwayLength;            // Longueur (m)

    // Parkings
    std::vector<std::string> parkingPositions;  // ["P1", "P2", ..., "Pn"]
    std::vector<double> parkingDistances;       // Distance à la piste (m)

    // Temps standard
    double landingTime;             // Temps d'atterrissage (s)
    double takeoffTime;             // Temps de décollage (s)

    AirportConfiguration()
        : icaoCode(""), runwayHeading(0.0), runwayLength(3000.0),
        landingTime(60.0), takeoffTime(45.0) {
    }
};

// ============================================================================
// MESSAGES / COMMUNICATION
// ============================================================================

/**
 * Type de message échangé
 */
enum class MessageType {
    // Avion -> Contrôle
    ENTRY_REQUEST,          // Demande d'entrée dans zone
    POSITION_REPORT,        // Rapport de position
    EMERGENCY_DECLARED,     // Déclaration d'urgence
    READY_FOR_TAKEOFF,      // Prêt au décollage

    // Contrôle -> Avion
    CLEARANCE,              // Autorisation
    TRAJECTORY_ASSIGNMENT,  // Assignation de trajectoire
    ALTITUDE_CHANGE,        // Changement d'altitude
    LANDING_CLEARANCE,      // Autorisation d'atterrissage
    TAKEOFF_CLEARANCE,      // Autorisation de décollage
    HOLD_POSITION,          // Maintenir position

    // Inter-contrôles
    HANDOFF_REQUEST,        // Demande de transfert
    RUNWAY_STATUS_REQUEST,  // Demande statut piste
    RUNWAY_STATUS_RESPONSE  // Réponse statut piste
};

/**
 * Message échangé entre agents
 */
struct Message {
    MessageType type;
    std::string sender;             // Callsign ou ID contrôleur
    std::string recipient;          // Destinataire
    std::string content;            // Contenu (peut être JSON)
    std::chrono::system_clock::time_point timestamp;

    Message(MessageType t = MessageType::POSITION_REPORT,
        const std::string& s = "",
        const std::string& r = "",
        const std::string& c = "")
        : type(t), sender(s), recipient(r), content(c),
        timestamp(std::chrono::system_clock::now()) {
    }
};

// ============================================================================
// DONNÉES PARTAGÉES (THREAD-SAFE)
// ============================================================================

/**
 * Table de données partagées pour les avions
 * Accès thread-safe via mutex
 */
class SharedAircraftTable {
private:
    std::vector<AircraftData> aircrafts;
    mutable std::mutex mutex;

public:
    void addAircraft(const AircraftData& aircraft);
    void updateAircraft(const std::string& callsign, const AircraftData& data);
    AircraftData getAircraft(const std::string& callsign) const;
    std::vector<AircraftData> getAllAircrafts() const;
    void removeAircraft(const std::string& callsign);
    bool exists(const std::string& callsign) const;
};

/**
 * File de messages partagée (thread-safe)
 */
class MessageQueue {
private:
    std::vector<Message> messages;
    mutable std::mutex mutex;

public:
    void push(const Message& msg);
    bool pop(Message& msg);  // Retourne false si vide
    std::vector<Message> popAll();
    size_t size() const;
    bool empty() const;
};

// ============================================================================
// DOMAINES DE CONTRÔLE
// ============================================================================

/**
 * Définition du domaine de contrôle CCR
 */
struct CCRDomain {
    std::string identifier;
    CCRControlZone zone;
    std::vector<std::string> managedAirports;  // Aéroports gérés
    SharedAircraftTable* aircraftTable;        // Table partagée
    MessageQueue* messageQueue;                // File de messages
};

/**
 * Définition du domaine de contrôle APP
 */
struct APPDomain {
    std::string airportCode;
    APPControlZone zone;
    SharedAircraftTable* aircraftTable;
    MessageQueue* messageQueue;
    MessageQueue* twrMessageQueue;             // Communication avec TWR
};

/**
 * Définition du domaine de contrôle TWR
 */
struct TWRDomain {
    AirportConfiguration airport;
    SharedAircraftTable* aircraftTable;
    MessageQueue* messageQueue;
    bool runwayOccupied;
    std::string runwayOccupiedBy;

    TWRDomain() : runwayOccupied(false), runwayOccupiedBy("") {}
};

#endif // ATC_DATA_STRUCTURES_HPP