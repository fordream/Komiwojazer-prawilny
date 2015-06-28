#ifndef KOMIPLUGINMANAGER_H
#define KOMIPLUGINMANAGER_H

#include <QObject>
#include <QMap>
#include "komiwojazerplugininterface.h"

/**
 * @brief The KomiPluginManager class
 * Klasa zarządzająca pluginami.
 */
class KomiPluginManager
{
public:
    /**
     * @brief KomiPluginManager
     * Konstruktor
     */
    KomiPluginManager();
    ~KomiPluginManager();
    /**
     * @brief loadPlugin
     * Szuka pluginów i zapisuje ich nazwy.
     * @param _plugIndexNameMap kontener, w kórym zapisywane są nazwy pluginów.
     * @return Czy udało się załadować plugin
     */
    bool loadPlugin(QMap<int, QString> &_plugIndexNameMap);
    /**
     * @brief getPluginByIndex
     * Zwraca wskaźnik do pluginu o podanym indeksie.
     * @param _index
     * @return
     */
    KomiwojazerPluginInterface* getPluginByIndex(int _index) const;
private:
    /**
     * @brief m_numberOfPlugins
     * Ilość dostępnych pluginów.
     */
    int m_numberOfPlugins;
    /**
     * @brief m_pluginsMap
     * Kontener przechowujący wskaźniki do dostępnych pluginów i ich indeksy.
     */
    QMap<int, KomiwojazerPluginInterface*> m_pluginsMap;
};

#endif // KOMIPLUGINMANAGER_H
