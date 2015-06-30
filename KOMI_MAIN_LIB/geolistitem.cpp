#include "geolistitem.h"

GeoListItem::GeoListItem(QString text) : QListWidgetItem(text)
{
    this->place=nullptr;
}

GeoListItem::GeoListItem(const Place *place) :
    QListWidgetItem(place->getName())
{
    this->place = new Place(*place);
}

Place* GeoListItem::getPlace()
{
    return this->place;
}

GeoListItem::~GeoListItem()
{
    delete this->place;
}
