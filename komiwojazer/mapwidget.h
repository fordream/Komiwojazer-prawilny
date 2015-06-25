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

class MapWidget : public MarbleWidget
{
    Q_OBJECT

public:
    MapWidget();
    QVector<Place*> findPlaceByName(QString name);
    QString findPlaceByCoordinates(double lon, double lat);
    void drawRoute(Route route);
    void drawRoute(std::vector<Route> routes);
    Route findRoute(Coordinates from, Coordinates to);
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void setFocusedMarker(double lon, double lat);
    void setFocusedMarker(Coordinates marker);
    enum MarkerType {Normal, Selected};
    void center(Coordinates);

private:
    Marble::MarbleModel marbleModel;
    MarbleMap map;
    virtual void customPaint(Marble::GeoPainter* painter);
    std::map<Coordinates, MarkerType> markers;
    QImage getMarkerIcon(MarkerType type);
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
