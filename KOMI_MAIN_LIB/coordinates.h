#ifndef COORDINATES_H
#define COORDINATES_H
#include <marble/GeoDataCoordinates.h>
#include "komi_main_lib_global.h"

class KOMI_MAIN_LIBSHARED_EXPORT Coordinates
{
public:
    Coordinates();
    Coordinates(double lon, double lat);
    Coordinates(Marble::GeoDataCoordinates);
    double getLon() const;
    double getLat() const;
    bool operator < (const Coordinates& that) const;

private:
    double lon;
    double lat;
};

#endif // Coordinates_H
