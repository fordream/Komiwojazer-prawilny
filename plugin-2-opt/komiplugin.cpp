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
#include <place.h>

KomiPlugin::KomiPlugin()
{

}

KomiPlugin::~KomiPlugin()
{

}

//! Returns (short) name (for menu entry, etc.)
QString KomiPlugin::getName() const
{
    return QString("2-opt");
}

//! Returns long name/description (for tooltip, etc.)
QString KomiPlugin::getDescription() const
{
    return QString("Solves TSP with 2-opt algorythm");
}

std::vector<Place*> KomiPlugin::calculate(const std::vector<Place*> places)
{
    m_bRunAlgorithm = true;

    size_t size = places.size();
    int* solution = new int[size];
    int* new_solution = new int[size];

    Marble::Route** routes = new Marble::Route*[size];
    for(int i = 0; i < size; ++i)
    {
        routes[i] =  new Marble::Route[size];
        for(int j = 0; j < size; ++j)
        {
            Coordinates from = places[i]->getCoordinates();
            Coordinates to = places[j]->getCoordinates();
            routes[i][j] = map->getRoute(from, to);
        }

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
            for (xi = 0; xi < size; ++xi)
            {
                yi = (ci + 1) % size;
                zi = (xi + 1) % size;

                double cy = routes[ci][yi].distance();
                double xz = routes[xi][zi].distance();
                double cx = routes[ci][xi].distance();
                double yz = routes[yi][zi].distance();

                if (xi != ci && xi != yi)
                {
                    double oldDistance = cy + xz;
                    int yi_iter = yi;
                    int xi_iter = xi;
                    while(xi_iter != yi_iter)
                    {
                        oldDistance += routes[yi_iter][(yi_iter - 1)%size].distance();
                        yi_iter = (yi_iter + 1) % size;
                    }


                    double newDistance = cx + yz;
                    yi_iter = yi;
                    xi_iter = xi;
                    while(xi_iter != yi_iter)
                    {
                        newDistance += routes[xi_iter][(xi_iter - 1)%size].distance();
                        xi_iter = (xi_iter - 1) % size;
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

        if (found)
        {
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
                xi = (xi - 1) % size;
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

    delete[] solution;
    delete[] new_solution;

    return v_toRet;
}

void KomiPlugin::cancel()
{
    m_bRunAlgorithm = false;
}
