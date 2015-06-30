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
#include <tuple>
#include <utility>

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
    QVector<Place> findPlaceByName(QString name);
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
    /**
     * @brief setFocusedMarker
     * Koncentruje mapę na współrzędnych geograficznych
     * @param lon Długość geograficzna
     * @param lat Szerokość geograficzna
     */
    void setFocusedMarker(double lon, double lat);
    /**
     * @brief setFocusedMarker
     * Koncentruje mapę na współrzędnych geograficznych
     * @param marker Współrzędne geograficzne
     */
    void setFocusedMarker(Coordinates marker);
    enum MarkerType {Normal, Selected};
    /**
     * @brief center
     * Koncentruje mapę na współrzędnych geograficznych
     * @param Coordinates Współrzędne geograficzne
     */
    void center(Coordinates);

private:
    Marble::MarbleModel marbleModel;
    //MarbleMap map;
    virtual void customPaint(Marble::GeoPainter* painter);
    std::map<Coordinates, std::tuple<MarkerType, QString> > markers;
    QImage getMarkerIcon(MarkerType type, QString text);
    Coordinates focusedMarker;
    Route route;
    std::pair<Coordinates, Coordinates> m_currentRouteSearch;

public slots:
    /**
     * @brief putMarker
     * Wstawia marker na mapę
     * @param lon Długość geograficzna
     * @param lat Szerokość geograficzna
     * @param type Typ markera
     * @param text Tekst do wyświetlenia na znaczniku
     */
    void putMarker(qreal lon, qreal lat, MarkerType type=Normal, QString text = "");
    /**
     * @brief putMarker
     * Wstawia marker na mapę
     * @param marker Współrzędne geograficzne
     * @param type Typ markera
     * @param text Tekst do wyświetlenia na znaczniku
     */
    void putMarker(Coordinates marker, MarkerType type=Normal, QString text = "");
    /**
     * @brief deleteMarker
     * Usuwa marker z mapy
     * @param marker Współrzędne geograficzne
     */
    void deleteMarker(Coordinates marker);
    /**
     * @brief routeRetrivedSlot
     * Wywoływany gdy droga została znaleziona
     */
    void routeRetrivedSlot(RoutingManager::State state);

signals:
    /**
     * @brief placeSelected
     * Sygnał oznaczający że miejsce zostało znalezione
     * double Długość geograficzna
     * double Szerokość geograficzna
     * QString Nazwa
     */
    void placeSelected(double, double, QString);
    /**
     * @brief routeFoundSignal
     * Sygnał informujący, że droga została znaleziona
     */
    void routeFoundSignal();


};

#endif // MAPWIDGET_H
