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

#include <QtWidgets>

#include "komiplugin.h"

KomiPlugin::KomiPlugin()
{

}

KomiPlugin::~KomiPlugin()
{

}

//! Returns (short) name (for menu entry, etc.)
QString KomiPlugin::getName() const
{
    return QString("Greedy");
}

//! Returns long name/description (for tooltip, etc.)
QString KomiPlugin::getDescription() const
{
    return QString("Solves TSP with greedy algorythm");
}

std::vector<Place*> KomiPlugin::calculate(const std::vector<Place*> places, Marble::Route** routes)
{
    m_bRunAlgorithm = true;
    std::vector<int> v_usedPlaces;
    std::vector<Place*> v_toRet;
    int size = places.size();
    if(size == 0)
        return v_toRet;

    v_usedPlaces.push_back(0);

    qreal min = std::numeric_limits<qreal>::max();
    int index;
    while(v_usedPlaces.size() != size && m_bRunAlgorithm)
    {
        for(int i = 0; i < size; ++i)
        {
            if(v_usedPlaces.end() != std::find(v_usedPlaces.begin(), v_usedPlaces.end(), i))
            {
                continue;
            }

            if(routes[v_usedPlaces.back()][i].distance() < min)
            {
                min = routes[v_usedPlaces.back()][i].distance();
                index = i;
            }
        }
        v_usedPlaces.push_back(index);
        min = std::numeric_limits<qreal>::max();\

        map->setProgress(v_usedPlaces.size() / size * 100);
        QApplication::processEvents();
    }

    if(v_usedPlaces.size() > 1)
    {
        std::vector<Marble::Route> toDraw;
        double overallLength = 0;
        for(int i = 0; i < v_usedPlaces.size()-1; ++i)
        {
            Marble::Route r = routes[v_usedPlaces.at(i)][v_usedPlaces.at(i+1)];
            overallLength += r.distance();
            toDraw.push_back(r);
        }
        Marble::Route r = routes[v_usedPlaces.at(size-1)][v_usedPlaces.at(0)];
        overallLength += r.distance();
        toDraw.push_back(r);
        map->writeLog(QString("Overall road length from greedy algorithm: %1 meters").arg(overallLength));
        this->map->drawRoute(toDraw);
    }

    for(auto it = v_usedPlaces.begin(); it != v_usedPlaces.end(); ++it)
        v_toRet.push_back(places.at(*it));


    return v_toRet;
}

void KomiPlugin::cancel()
{
    m_bRunAlgorithm = false;
}
