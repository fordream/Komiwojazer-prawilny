#ifndef PLACE_H
#define PLACE_H
#include <coordinates.h>
#include <QString>
#include <marble/GeoDataPlacemark.h>
#include "komi_main_lib_global.h"

/**
 * @brief The Place class
 * Miejsce reprezentowane na mapie
 */
class KOMI_MAIN_LIBSHARED_EXPORT Place
{
public:
    /**
     * @brief Place
     * Domyślny konstruktor
     */
    Place();
    /**
     * @brief Place
     * Konstruktor przyjmujący współrzędne geograficzne i nazwę miejsca
     * @param coor Współrzędne geograficzne
     * @param name Nazwa miejsca
     */
    Place(Coordinates coor, QString name);
    /**
     * @brief Place
     * Konstruktor przyjmujący obiekt klasy GeoDataPlacemark z biblioteki Marble
     * @param place Miejsce
     */
    Place(Marble::GeoDataPlacemark);
    /**
     * @brief getCoordinates
     * Zwraca współrzędne geograficzne miejsca
     * @returns Współrzędne geograficzne miejsca
     */
    Coordinates getCoordinates() const;
    /**
     * @brief getName
     * Zwraca nazwę miejsca
     * @returns Nazwa miejsca
     */
    QString getName() const;

private:
    /**
     * @brief coordinates
     * Współrzędne geograficzne miejsca
     */
    Coordinates coordinates;
    /**
     * @brief name
     * Nazwa miejsca
     */
    QString name;
};

#endif // PLACE_H
