#ifndef MAPWIDGET_H
#define MAPWIDGET_H
#include <marble/MarbleWidget.h>
#include <marble/MarbleMap.h>
#include <marble/MarbleModel.h>
#include <marble/SearchRunnerManager.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/ReverseGeocodingRunnerManager.h>
#include <marble/GeoPainter.h>
#include <QMouseEvent>
#include <coordinates.h>
#include <marble/RouteRequest.h>
#include <marble/RoutingManager.h>
#include <marble/Route.h>
#include <marble/RoutingModel.h>
#include <map>
#include <place.h>
#include <marble/MarbleMap.h>
#include <marble/GeoDataCoordinates.h>
#include <QEventLoop>
#include <QTimer>

using namespace Marble;

/**
 * @brief The MapWidget class
 * Klasa dziedzicząca po MarbleWidget odpowiedzialna za wyświetlanie, wyszukiwanie i zarządzanie danymi dotyczącymi mapy OSM
 */
class MapWidget : public MarbleWidget
{
    Q_OBJECT

public:
    /**
     * @brief MapWidget
     * Konstruktor
     */
    MapWidget();
    /**
     * @brief findPlaceByName
     * Wyszukuje miejsca na mapie na podstawie nazwy
     * @param name Nazwa miejsca która ma być wyszukana
     * @returns Wektor miejsc pasujących do nazwy
     */
    QVector<Place*> findPlaceByName(QString name);
    /**
     * @brief findPlaceByCoordinates
     * Wyszukuje miejsca na mapie po współrzędnych
     * @param lon Długość geograficzna
     * @param lat Szerokość geograficzna
     * @returns Miejsce
     */
    QString findPlaceByCoordinates(double lon, double lat);
    /**
     * @brief drawRoute
     * Rysuje pojedyńczą drogę na mapie
     * @param route Droga do narysowania
     */
    void drawRoute(Route route);
    /**
     * @brief drawRoute
     * Rysuje drogi na mapie.
     * @param routes Wektor dróg do narysowania
     */
    void drawRoute(std::vector<Route> routes);
    /**
     * @brief findRoute
     * Znajduje drogę pomiędzy dwoma punktami na mapie
     * @param from Miejsce startowe
     * @param to Miejsce docelowe
     * @returns Znaleziona droga
     */
    Route findRoute(Coordinates from, Coordinates to);
    /**
     * @brief mouseDoubleClickEvent
     * Dodaje marker na mapie
     * @param mouseDoubleClickEvent Event myszy
     */
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void setFocusedMarker(double lon, double lat);
    void setFocusedMarker(Coordinates marker);
    enum MarkerType {Normal, Selected};
    void center(Coordinates);

private:
    Marble::MarbleModel marbleModel;
    //MarbleMap map;
    virtual void customPaint(Marble::GeoPainter* painter);
    std::map<Coordinates, MarkerType> markers;
    QImage getMarkerIcon(MarkerType type, QString text);
    Coordinates focusedMarker;
    Route route;

public slots:
    void putMarker(qreal lon, qreal lat, MarkerType type=Normal);
    void putMarker(Coordinates marker, MarkerType type=Normal);
    void deleteMarker(Coordinates marker);
    void routeRetrivedSlot();

signals:
    void placeSelected(double, double, QString);
    void routeFoundSignal();


};

#endif // MAPWIDGET_H
