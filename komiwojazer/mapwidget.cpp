#include "mapwidget.h"
#include <iostream>

MapWidget::MapWidget()
{
    //this->map.setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    //QObject::connect(this->map, SIGNAL(mouseClickGeoPosition(qreal,qreal,GeoDataCoordinates::Unit)), this, SLOT(putMarker(qreal,qreal,Marble::GeoDataCoordinates::Unit)));
}

QVector<Place*> MapWidget::findPlaceByName(QString name)
{
    Marble::SearchRunnerManager* manager = new Marble::SearchRunnerManager( &marbleModel );
    QVector<Marble::GeoDataPlacemark*> searchResult = manager->searchPlacemarks( name );
    QVector<Place*> places;
    for(int i=0; i<searchResult.size(); i++)
    {
        Place* place = new Place(*places.at(i));
        places.push_back(place);
        delete places.at(i);
    }
    delete manager;
    return places;
}

QString MapWidget::findPlaceByCoordinates(double lon, double lat)
{
    Marble::ReverseGeocodingRunnerManager *manager = new Marble::ReverseGeocodingRunnerManager(&marbleModel);

    Marble::GeoDataCoordinates position( lon,  lat, 0.0);
    delete manager;
    return manager->searchReverseGeocoding(position);
}

void MapWidget::putMarker(qreal lon, qreal lat, MarkerType type)
{
    Coordinates marker(lon, lat);
    this->putMarker(marker, type);
}

void MapWidget::putMarker(Coordinates marker, MarkerType type)
{
    std::cout<<"Marker type : "<<this->markers.size()<<std::endl;
    this->markers[marker] = type;
    this->update();
}

void MapWidget::deleteMarker(Coordinates marker)
{
    this->markers.erase(marker);
    this->update();
}

void MapWidget::drawLine()
{

}

void MapWidget::drawRoute(Route route)
{

}

Route MapWidget::findRoute(Coordinates from, Coordinates to)
{
    // Access the shared route request (start, destination and parameters)
    std::cout<<"from"<<from.getLon()<<"  "<<from.getLat()<<std::endl;
    std::cout<<"to"<<to.getLon()<<"  "<<to.getLat()<<std::endl;
    RoutingManager* manager = this->model()->routingManager();
    RouteRequest* request = manager->routeRequest();
    request->clear();
    // Use default routing settings for cars
    request->setRoutingProfile( manager->defaultProfile( RoutingProfile::Motorcar ) );

    // Set start and destination
    request->append( GeoDataCoordinates( from.getLon(), from.getLat(), 0.0, GeoDataCoordinates::Radian) );
    request->append( GeoDataCoordinates( to.getLon(), to.getLat(), 0.0, GeoDataCoordinates::Radian ) );

    manager->retrieveRoute();

    //this->show();
    std::cout<<"distance: " <<manager->routingModel()->route().waypoints().size()<<std::endl;
    Route route=manager->routingModel()->route();
    return route;
}

void MapWidget::saveRoute(QString file)
{
    RoutingManager* manager = this->model()->routingManager();
    manager->saveRoute(file);
}

void MapWidget::drawRoute(QString file)
{
    RoutingManager* manager = this->model()->routingManager();
    manager->loadRoute(file);
}

void MapWidget::mouseDoubleClickEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton) {
        qreal lon;
        qreal lat;
        if (geoCoordinates(event->x(), event->y(), lon, lat, GeoDataCoordinates::Radian))
        {
            QString placeDesc = this->findPlaceByCoordinates(lon, lat);
            std::cout<<"Found point jej: "<<lon<<"  "<<lat<<"  "<<placeDesc.toStdString()<<std::endl;
            emit placeSelected(lon, lat, placeDesc);
            //this->setFocusedMarker(lon, lat);
        }
    }
}

void MapWidget::customPaint(Marble::GeoPainter* painter)
{
    std::map<Coordinates, MarkerType>::iterator i;
    for (i=markers.begin(); i!=this->markers.end(); ++i)
    {
        GeoDataCoordinates coordinates(i->first.getLon(), i->first.getLat(), 0.0);
        //painter->setBrush(Qt::green);
        //painter->drawEllipse(coordiantes, 15, 15);
        painter->drawImage(coordinates, QImage(getMarkerIcon(i->second)));
    }

}

QImage MapWidget::getMarkerIcon(MarkerType type)
{
    switch (type)
    {
        case Normal:
            return QImage(":/images/grey.png");
        case Selected:
            return QImage(":/images/yellow.png");
    }
}

void MapWidget::center(Coordinates c)
{
    this->centerOn(GeoDataCoordinates(c.getLon(), c.getLat(), 0, GeoDataCoordinates::Radian));
}
