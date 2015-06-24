#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include <marble/Route.h>
#include <coordinates.h>

class AppInterface
{
public:
    AppInterface();
    virtual ~AppInterface(){}
    virtual void setProgress(int value) = 0;
    virtual Marble::Route getRoute(Coordinates from, Coordinates to) = 0;
    virtual void drawRoute(Marble::Route route) = 0;
    virtual void writeLog(QString text) = 0;

signals:
    virtual void routeFoundSignal(Marble::Route* route) = 0;


};

#endif // APPINTERFACE_H
