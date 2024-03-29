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

#include "komipluginExample.h"

KomiPluginExample::KomiPluginExample()
{

}

KomiPluginExample::~KomiPluginExample()
{

}

//! Returns (short) name (for menu entry, etc.)
QString KomiPluginExample::getName() const
{
    return QString("Example plugin/random");
}

//! Returns long name/description (for tooltip, etc.)
QString KomiPluginExample::getDescription() const
{
    return QString("Plugin descrition");
}

std::vector<Place*> KomiPluginExample::calculate(const std::vector<Place*> places, Marble::Route** routes)
{
    std::vector<Place*> v_toRet = places;
    m_bRunAlgorithm = true;

    std::vector<int> test;
    for(int i = 0; i < 100000; ++i)
    {
        test.clear();
        for(int j = 0; j < 1000; ++j)
        {
            test.push_back(i*j);
            if(j % 50 == 0)
                QApplication::processEvents();
        }

        m_app->setProgress(i/1000);

        if(!m_bRunAlgorithm)
            return v_toRet;
    }

    return v_toRet;
}

void KomiPluginExample::cancel()
{
    m_bRunAlgorithm = false;
}
