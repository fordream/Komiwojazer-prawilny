/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef KOMIWOJAZERPLUGININTERFAC_H
#define KOMIWOJAZERPLUGININTERFAC_H

#include <QString>
#include "appinterface.h"
#include <place.h>
#include <marble/Route.h>

/**
 * @brief The KomiwojazerPluginInterface class
 * Interfejs pluginowy aplikacji po którym dziedziczą pluginy
 */
class KomiwojazerPluginInterface
{
public:
    /**
     * @brief KomiwojazerPluginInterface
     * Konstruktor
     */
    explicit KomiwojazerPluginInterface() :m_app(0), m_bRunAlgorithm(true){}
    /**
     * @brief setMap
     * Ustawia wskaźnik do głównej aplikacji.
     * @param _map wskaźnik do aplikacji
     */
    virtual void setMap(AppInterface * _m_app) {m_app =_m_app;}
    /**
     * @brief KomiwojazerPluginInterface
     * Destruktor
     */
    virtual ~KomiwojazerPluginInterface() {}
    /**
     * @brief getName
     * @return Nazwa pluginu
     */
    virtual QString getName() const = 0;
    /**
     * @brief getDescription
     * @return Zwraca opis pluginu
     */
    virtual QString getDescription() const = 0;
    /**
     * @brief calculate
     * Główna funkcja obliczająca obtymalną drogę według danego algorytmu.
     * @param places wektor wskaźników położeń geograficznych które należy odwiedzić
     * @param routes tablica 2d dróg z każdego miejsca do każdego innego routes[i][j] przechowuje trasę z i do j, która może być różna od trasy z j do i (np. przez drogi jednokierunkowe)
     * @return Zwraca posortowane elementy trasy
     */
    virtual std::vector<Place*> calculate(const std::vector<Place*> places, Marble::Route** routes) = 0;
    /**
     * @brief connectToSLOT
     * Podłącza sygnał odpowiedzialny za anulownanie algorytmu do odpowiedniego slota w pluginie
     * @param pReceiver źródło sygnału
     * @param pszSlot sygnał
     * @param bConnect jeśli true - podłączamy, false - odłączamy
     * @return Czy się udało
     */
    virtual bool connectToSLOT(QObject* pReceiver, const char* pszSlot, bool bConnect) const = 0;
public slots:
    virtual void cancel() = 0;
protected:
    /**
     * @brief map
     * Wskaźnik do głównego interjfejsu aplikacji
     */
    AppInterface * m_app;
    /**
     * @brief m_bRunAlgorithm
     * Czy użytkownik chce kontynuować obliczenia
     */
    bool m_bRunAlgorithm;
};


QT_BEGIN_NAMESPACE

#define KomiwojazerPluginInterface_iid "ztpr.Michal.Magda.KomiwojazerPluginInterface"

Q_DECLARE_INTERFACE(KomiwojazerPluginInterface, KomiwojazerPluginInterface_iid)
QT_END_NAMESPACE

#endif
