#include "mapwidget.h"
#include <iostream>
#include <marble/GeoDataDocument.h>
#include <QPainter>

MapWidget::MapWidget()
    : MarbleWidget()
{
    connect(this->model()->routingManager()->routingModel(), SIGNAL(currentRouteChanged()), this, SLOT(routeRetrivedSlot()));
}

QVector<Place*> MapWidget::findPlaceByName(QString name)
{
    Marble::SearchRunnerManager manager( &marbleModel );
    QVector<Marble::GeoDataPlacemark*> searchResult = manager.searchPlacemarks( name );
    QVector<Place*> places;
    for(int i=0; i<searchResult.size(); i++)
    {
        Place* place = new Place(*searchResult.at(i));
        places.push_back(place);
        delete searchResult.at(i);
    }
    return places;
}

QString MapWidget::findPlaceByCoordinates(double lon, double lat)
{
    Marble::ReverseGeocodingRunnerManager manager(&marbleModel);
    Marble::GeoDataCoordinates position( lon,  lat, 0.0);
    return manager.searchReverseGeocoding(position);
}

void MapWidget::putMarker(qreal lon, qreal lat, MarkerType type, QString text)
{
    Coordinates marker(lon, lat);
    this->putMarker(marker, type, text);
}

void MapWidget::putMarker(Coordinates marker, MarkerType type, QString text)
{
    this->markers[marker] = std::tuple<MarkerType, QString>(type, text);
    this->update();
}

void MapWidget::deleteMarker(Coordinates marker)
{
    this->markers.erase(marker);
    this->update();
}

void MapWidget::drawRoute(std::vector<Route> routes)
{
    Route r;
    if(routes.size()>0)
    {
        r = routes.at(0);
    }
    for(auto it = routes.begin() + 1; it!=routes.end(); ++it)
    {
        for(int i=0; i<it->size(); i++)
        {
            r.addRouteSegment(it->at(i));
        }
    }
    drawRoute(r);
}

void MapWidget::drawRoute(Route r)
{
    //this->routingLayer()->
    this->model()->routingManager()->routingModel()->clear();
    this->model()->routingManager()->routingModel()->setRoute(r);
    this->show();
}

Route MapWidget::findRoute(Coordinates from, Coordinates to)
{
    route = Route();
    if(from.getLat() != to.getLat() || from.getLon() != to.getLon())
    {
        RoutingManager* manager = this->model()->routingManager();
        RouteRequest* request = manager->routeRequest();
        request->clear();
        // Use default routing settings for cars
        request->setRoutingProfile( manager->defaultProfile( RoutingProfile::Motorcar ) );

        // Set start and destination
        request->append( GeoDataCoordinates( from.getLon(), from.getLat(), 0.0, GeoDataCoordinates::Radian) );
        request->append( GeoDataCoordinates( to.getLon(), to.getLat(), 0.0, GeoDataCoordinates::Radian ) );
        QEventLoop localEventLoop;
        QTimer watchdog;
        watchdog.setSingleShot(true);
        connect( &watchdog, SIGNAL(timeout()), &localEventLoop, SLOT(quit()));
        connect(this->model()->routingManager()->routingModel(), SIGNAL(currentRouteChanged()), &localEventLoop, SLOT(quit()), Qt::QueuedConnection );
        watchdog.start( 30000 );
        manager->retrieveRoute();
        localEventLoop.exec();
    }
    return route;
}

void MapWidget::mouseDoubleClickEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton) {
        qreal lon;
        qreal lat;
        if (geoCoordinates(event->x(), event->y(), lon, lat, GeoDataCoordinates::Radian))
        {
            QString placeDesc = this->findPlaceByCoordinates(lon, lat);
            emit placeSelected(lon, lat, placeDesc);
        }
    }
}

void MapWidget::customPaint(Marble::GeoPainter* painter)
{
    std::map<Coordinates, std::tuple<MarkerType, QString> >::iterator i;
    for (i=markers.begin(); i!=this->markers.end(); ++i)
    {
        GeoDataCoordinates coordinates(i->first.getLon(), i->first.getLat(), 0.0);
        painter->drawImage(coordinates, QImage(getMarkerIcon(std::get<0>(i->second), std::get<1>(i->second))));
    }

}

QImage MapWidget::getMarkerIcon(MarkerType type, QString text)
{
    QString path;
    switch (type)
    {
        case Normal:
        {
            path = ":/images/grey.png";
            break;
        }
        case Selected:
        {
            path = ":/images/yellow.png";
            break;
        }
    }
    QImage marker(path);
    QPainter p(&marker);
    p.setFont(QFont("Times", 12, QFont::Bold));
    p.drawText(0, 0, 50, 50, Qt::AlignCenter, text);
    return marker;
}

void MapWidget::center(Coordinates c)
{
    this->centerOn(GeoDataCoordinates(c.getLon(), c.getLat(), 0, GeoDataCoordinates::Radian));
}

void MapWidget::routeRetrivedSlot()
{
    route = this->model()->routingManager()->routingModel()->route();
}
