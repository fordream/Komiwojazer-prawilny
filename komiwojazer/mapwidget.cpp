#include "mapwidget.h"
#include <iostream>
#include <marble/GeoDataDocument.h>
#include <QPainter>

MapWidget::MapWidget()
    : MarbleWidget()
{
    connect(this->model()->routingManager(), SIGNAL(stateChanged(RoutingManager::State)), this, SLOT(routeRetrivedSlot(RoutingManager::State)));
}

QVector<Place> MapWidget::findPlaceByName(QString name)
{
    Marble::SearchRunnerManager manager( &marbleModel );
    QVector<Marble::GeoDataPlacemark*> searchResult = manager.searchPlacemarks( name );
    QVector<Place> places;
    for(int i=0; i<searchResult.size(); i++)
    {
        Place place(*searchResult.at(i));
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
    this->repaint();
    //this->show();
}

Route MapWidget::findRoute(Coordinates from, Coordinates to)
{
    m_currentRouteSearch = std::make_pair(from, to);
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
        std::cout << request->at(0).latitude() << " " << from.getLat() <<std::endl;
        QEventLoop localEventLoop;
        QTimer watchdog;
        watchdog.setSingleShot(true);
        connect( &watchdog, SIGNAL(timeout()), &localEventLoop, SLOT(quit()));
        connect(this, SIGNAL(routeFoundSignal()), &localEventLoop, SLOT(quit()), Qt::QueuedConnection );
        watchdog.start( 10000 );
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

void MapWidget::routeRetrivedSlot(RoutingManager::State state)
{
    if(state == RoutingManager::State::Retrieved)
    {
        route = Route(this->model()->routingManager()->routingModel()->route());
        if(route.distance() == 0)
            return;
        if(route.path().size()){
            qreal firstLat = route.path().first().latitude();
            qreal firstLon = route.path().first().longitude();
            qreal lastLat = route.path().last().latitude();
            qreal lastLon = route.path().last().longitude();
            std::cout << "firstLat " << firstLat << "real firstLat " << m_currentRouteSearch.first.getLat() << std::endl;
            std::cout << "firstLon " << firstLon << "real firstLon " << m_currentRouteSearch.first.getLon() << std::endl;
            std::cout << "lastLat " << lastLat << "real lastLat " << m_currentRouteSearch.first.getLat() << std::endl;
            std::cout << "lastLon " << lastLon << "real lastLon " << m_currentRouteSearch.second.getLon() << std::endl;

            std::cout << "firstLat " << route.at(0).path().first().latitude() << "real firstLat " << m_currentRouteSearch.first.getLat() << std::endl;
            std::cout << "firstLon " << route.at(0).path().first().longitude() << "real firstLon " << m_currentRouteSearch.first.getLon() << std::endl;
            std::cout << "lastLat " << route.at(route.size()-1).path().last().latitude() << "real lastLat " << m_currentRouteSearch.first.getLat() << std::endl;
            std::cout << "lastLon " << route.at(route.size()-1).path().last().longitude() << "real lastLon " << m_currentRouteSearch.second.getLon() << std::endl;
        }
        this->model()->routingManager()->routeRequest()->clear();
        emit this->routeFoundSignal();
    }
}
