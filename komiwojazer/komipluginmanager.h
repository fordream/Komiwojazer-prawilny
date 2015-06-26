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
     * @return
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
    int m_numberOfPlugins;
    QMap<int, KomiwojazerPluginInterface*> m_pluginsMap;
};

#endif // KOMIPLUGINMANAGER_H
