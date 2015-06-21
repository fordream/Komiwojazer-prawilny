#ifndef GEOLISTITEM_H
#define GEOLISTITEM_H
#include <QListWidgetItem>
#include <place.h>
#include "komi_main_lib_global.h"

class KOMI_MAIN_LIBSHARED_EXPORT GeoListItem : public QListWidgetItem
{
public:
    GeoListItem(QString);
    ~GeoListItem();
    GeoListItem(Place* place);
    Place *getPlace();

private:
    Place* place;
};

#endif // GEOLISTITEM_H
