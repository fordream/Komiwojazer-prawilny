#ifndef PLACE_H
#define PLACE_H
#include <coordinates.h>
#include <QString>
#include <marble/GeoDataPlacemark.h>
#include "komi_main_lib_global.h"

class KOMI_MAIN_LIBSHARED_EXPORT Place
{
public:
    Place();
    Place(Coordinates coor, QString name);
    Place(Marble::GeoDataPlacemark);
    Coordinates getCoordinates() const;
    QString getName();

private:
    Coordinates coordinates;
    QString name;
};

#endif // PLACE_H
