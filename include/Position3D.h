// Position3D.h
#ifndef POSITION3D_H
#define POSITION3D_H

struct Position3D {
    double x;        // Coordonnée X (en km ou en mètres)
    double y;        // Coordonnée Y (en km ou en mètres)
    double altitude; // Altitude (en mètres)

    Position3D(double x = 0, double y = 0, double alt = 0)
        : x(x), y(y), altitude(alt) {
    }
};

#endif