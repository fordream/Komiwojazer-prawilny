#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include <marble/Route.h>
#include <coordinates.h>

/**
 * @brief The AppInterface class
 * Interfejs aplikacji obsługującej mapy.
 */
class AppInterface
{
public:
    /**
     * @brief AppInterface - konstruktor
     */
    explicit AppInterface(){}
    /**
     * @brief ~AppInterface
     */
    virtual ~AppInterface(){}
    /**
     * @brief setProgress
     * Ustawia postęp obliczeń.
     * @param value - postęp obliczeń
     */
    virtual void setProgress(int value) = 0;
    /**
     * @brief getRoute
     * Zwraca drogę z punktu o współrzędnych from do punktu o współrzędnych to.
     * @param from współrzędne punktu początkowego
     * @param to współrzędne punktu koncowego
     * @return droga
     */
    virtual Marble::Route getRoute(Coordinates from, Coordinates to) = 0;
    /**
     * @brief drawRoute
     * Rysuje drogę na mapie
     * @param route droga
     */
    virtual void drawRoute(Marble::Route route) = 0;
    /**
     * @brief drawRoute
     * Rysuje drogę, która jest sumą dróg przekazanych w wektorze.
     * @param routes wektor dróg
     */
    virtual void drawRoute(std::vector<Marble::Route> routes) = 0;
    /**
     * @brief writeLog
     * Przekazuje informacje w formie wiadomości tekstowych.
     * @param text wiadomość
     */
    virtual void writeLog(QString text) = 0;

};

#endif // APPINTERFACE_H
