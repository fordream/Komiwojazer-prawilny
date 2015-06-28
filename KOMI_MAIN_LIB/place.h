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
    Place();
    Place(Coordinates coor, QString name);
    Place(Marble::GeoDataPlacemark);
    Coordinates getCoordinates() const;
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
