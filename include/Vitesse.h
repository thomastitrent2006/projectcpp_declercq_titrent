// Vitesse.h
#ifndef VITESSE_H
#define VITESSE_H

struct Vitesse {
    double vx;       // Vitesse en X (m/s ou km/h)
    double vy;       // Vitesse en Y (m/s ou km/h)
    double vz;       // Vitesse verticale (m/s)

    double getNorme() const;

    Vitesse(double vx = 0, double vy = 0, double vz = 0)
        : vx(vx), vy(vy), vz(vz) {
    }
};

#endif