#ifndef COORDINATES_H
#define COORDINATES_H
#include <marble/GeoDataCoordinates.h>
#include "komi_main_lib_global.h"

/**
 * @brief The Coordinates class
 * Klasa przechowujące szerokość i długość geograficzną
 */
class KOMI_MAIN_LIBSHARED_EXPORT Coordinates
{
public:
    /**
     * @brief Coordinates - konstruktor
     */
    Coordinates();
    /**
     * @brief Coordinates - konstruktor
     */
    Coordinates(double lon, double lat);
    /**
     * @brief Coordinates - konstruktor
     * Z obiektu GeoDataCoordinates biblioteki Marble
     */
    Coordinates(Marble::GeoDataCoordinates);
    /**
     * @brief getLon
     * Zwraca długośc gegraficzną
     * @return Długość geograficzna
     */
    double getLon() const;
    /**
     * @brief getLat
     * Zwraca szerokość gegraficzną
     * @return Szerokość geograficzna
     */
    double getLat() const;
    bool operator < (const Coordinates& that) const;

private:
    /**
     * @brief lon
     * Długość geograficzna
     */
    double lon;
    /**
     * @brief lat
     * Szerokość geograficzna
     */
    double lat;
};

#endif // Coordinates_H
