#ifndef GEOLISTITEM_H
#define GEOLISTITEM_H
#include <QListWidgetItem>
#include <place.h>
#include "komi_main_lib_global.h"

/**
 * @brief The GeoListItem class
 * Klasa przechowująca informacje o wybranych punktach do odwiedzenia
 */
class KOMI_MAIN_LIBSHARED_EXPORT GeoListItem : public QListWidgetItem
{
public:
    /**
     * @brief GeoListItem
     * Konstruktor
     */
    GeoListItem(QString);
    /**
     * @brief GeoListItem
     * Konstruktor
     */
    GeoListItem(const Place* place);
    /**
     * @brief ~GeoListItem
     * Destruktor
     */
    ~GeoListItem();
    /**
     * @brief getPlace
     * Zetaca miejsce na mapie
     * @return Miejsce
     */
    Place *getPlace();
    /**
     * @brief clone
     * Kompije element
     * @return Kopia
     */
    //virtual GeoListItem* clone();

private:
    /**
     * @brief place
     * Miejsce, które zostało dodane
     */
    Place* place;
};

#endif // GEOLISTITEM_H
