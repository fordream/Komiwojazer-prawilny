#include "place.h"

Place::Place()
{
}

Place::Place(Coordinates coor, QString name): coordinates(coor), name(name)
{

}

Place::Place(Marble::GeoDataPlacemark place)
{
    this->name = place.name();
    this->coordinates = place.coordinate();
}

Coordinates Place::getCoordinates() const
{
    return this->coordinates;
}

QString Place::getName() const
{
    return this->name;
}
