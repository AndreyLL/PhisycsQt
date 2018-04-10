/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include "circlewidget.h"

#include <QPainter>
#include <iostream>

#include <stdlib.h>

//! [0]
CircleWidget::CircleWidget(QWidget *parent)
    : QWidget(parent)
{
    floatBased = false;
    antialiased = false;
    frameNo = 0;

    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QTime timer;
    int currentTime = timer.currentTime().msecsSinceStartOfDay();
    m_timeBefore  = currentTime;
}
//! [0]

//! [1]
void CircleWidget::setFloatBased(bool floatBased)
{
    this->floatBased = floatBased;
    update();
}
//! [1]

//! [2]
void CircleWidget::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}
//! [2]

//! [3]
QSize CircleWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}
//! [3]

//! [4]
QSize CircleWidget::sizeHint() const
{
    return QSize(180, 180);
}

void CircleWidget::setFigure(PhysycObject &object)
{
    m_object = &object;
}





//! [4]

//! [5]
void CircleWidget::nextAnimationFrame()
{
    ++frameNo;
    update();

}
//! [5]

//! [6]
void CircleWidget::paintEvent(QPaintEvent *)
{
    QTime timer;

    int currentTime = timer.currentTime().msecsSinceStartOfDay();
    int diff  =  currentTime - m_timeBefore;
    m_timeBefore  = currentTime;
    m_object->doWork(diff);

    MyPolygoinF* points =  &( m_object->points() );

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiased);
    painter.translate( width() / 2, height() / 2 );
    int size_v = points->size();
    if (!size_v)
        return;
    painter.setPen(QPen(QColor(0,  127, 127), 3));
    //painter.setBackground(QBrush(QColor(0,  127, 127)));
    painter.drawPolygon(*points,Qt::OddEvenFill);
}
//! [8]
