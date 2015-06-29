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

#include "komiplugin2opt.h"
#include <place.h>

KomiPlugin2OPT::KomiPlugin2OPT()
{

}

KomiPlugin2OPT::~KomiPlugin2OPT()
{

}

//! Returns (short) name (for menu entry, etc.)
QString KomiPlugin2OPT::getName() const
{
    return QString("2-opt");
}

//! Returns long name/description (for tooltip, etc.)
QString KomiPlugin2OPT::getDescription() const
{
    return QString("Solves TSP with 2-opt algorythm");
}

std::vector<Place*> KomiPlugin2OPT::calculate(const std::vector<Place*> places, Marble::Route** routes)
{
    m_bRunAlgorithm = true;
    int progress = 0;
    map->setProgress(progress);
    size_t size = places.size();
    int* solution = new int[size];
    int* new_solution = new int[size];

    for(int i = 0; i < size; ++i)
    {
        solution[i] = i;
    }

    bool go = true;

    while (go)
    {
        double best = 0;
        std::vector<int> best_move = { 0, 0, 0, 0 };
        bool found = false;
        int ci;
        int xi;
        int yi;
        int zi;

        for (ci = 0; ci < size; ++ci)
        {
            for (xi = 0; xi < size; ++xi)
            {
                yi = (ci + 1) % size;
                zi = (xi + 1) % size;

                if (xi != ci && xi != yi)
                {
                    double cy = routes[solution[ci]][solution[yi]].distance();
                    double xz = routes[solution[xi]][solution[zi]].distance();
                    double cx = routes[solution[ci]][solution[xi]].distance();
                    double yz = routes[solution[yi]][solution[zi]].distance();

                    double oldDistance = cy + xz;
                    int yi_iter = yi;
                    int xi_iter = xi;
                    while(xi_iter != yi_iter)
                    {
                        oldDistance += routes[solution[yi_iter]][solution[(yi_iter + 1) % size]].distance();
                        yi_iter = (yi_iter + 1) % size;
                    }


                    double newDistance = cx + yz;
                    yi_iter = yi;
                    xi_iter = xi;
                    while(xi_iter != yi_iter)
                    {
                        int oneLess;
                        if(xi_iter == 0)
                            oneLess = size - 1;
                        else
                            oneLess = xi_iter - 1;
                        newDistance += routes[solution[xi_iter]][solution[oneLess]].distance();
                        if(xi_iter == 0)
                            xi_iter = size - 1;
                        else
                            --xi_iter;
                    }

                    double gain = oldDistance - newDistance;
                    if (gain > best)
                    {
                        best_move = { ci, yi, xi, zi };
                        best = gain;
                        found = true;
                    }
                }
            }
        }

        if (found)
        {
            map->writeLog(QString("Found more optimal way, gain: %1 meters\n").arg(best));
            ++progress;
            map->setProgress(progress%100);
            ci = best_move[0];
            yi = best_move[1];
            xi = best_move[2];
            zi = best_move[3];

            new_solution[0] = solution[ci];
            int n = 1;
            while (xi != yi)
            {
                new_solution[n] = solution[xi];
                n = n + 1;
                if(xi == 0)
                    xi = size - 1;
                else
                    xi = xi - 1;
            }
            new_solution[n] = solution[yi];
            n = n + 1;
            while (zi != ci)
            {
                new_solution[n] = solution[zi];
                n = n + 1;
                zi = (zi + 1) % size;
            }

            memcpy(solution, new_solution, sizeof(int) * size);
            found = false;
        }
        else
            go = false;
    }

    std::vector<Place*> v_toRet;

    for (unsigned int i = 0; i < size; ++i)
        v_toRet.push_back(places.at(solution[i]));

    if(size > 1)
    {
        double overallLength = 0;
        std::vector<Marble::Route> toDraw;
        for(int i = 0; i < size-1; ++i)
        {
            Marble::Route r = routes[solution[i]][solution[i+1]];
            overallLength += r.distance();
            toDraw.push_back(r);
            map->writeLog(QString("Place number %1: %2\n").arg(i+1).arg(places.at(solution[i])->getName()));
        }
        map->writeLog(QString("Place number %1: %2\n").arg(size).arg(places.at(solution[size-1])->getName()));
        map->writeLog(QString("Overall road length from 2-opt algorithm: %1 km\n").arg(overallLength/1000));

        this->map->drawRoute(toDraw);
    }

    delete[] solution;
    delete[] new_solution;

    return v_toRet;
}

void KomiPlugin2OPT::cancel()
{
    m_bRunAlgorithm = false;
}
