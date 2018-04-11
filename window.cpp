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
#include "window.h"

#include <QtWidgets>
#include <QPolygonF>



//! [0]
//!
//!

double distance(const PointsType &a, const PointsType &b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return (  std::sqrt(dx*dx + dy*dy) );

}

void constructObjectTREST(PhysycObject& object)
{

//    MyPolygoinF poly ={QPointF(40,0),
//                      QPointF(50,50),
//                      QPointF(0, 40),
//                      QPointF(-50,50),
//                      QPointF(-40,0),
//                      QPointF(-50,-50),
//                      QPointF(0,-40),
//                      QPointF(50,-50)
//                     } ;
    MyPolygoinF poly =  {   QPointF(70,0), //0
                            QPointF(0, 40), //1
                            QPointF(-40,0), //2
                            QPointF(0,-40), //3
                            QPointF(70, 0), //4
                        };
    MyPolygoinF poly2 = {
                            QPointF(70,0), //     5
                            QPointF(130,20), //   6
                            QPointF(130,-20), //  7
                        };
    MyPolygoinF poly3 = {
                            QPointF(130, -20), //     8
                            QPointF(150, -40), //   9
                            QPointF(150, 0), //  10
                        };
    poly.append(poly2);
    poly.append(poly3);

    for (int i =0; i < poly.size(); i++) {
        poly[i]=poly[i]-QPointF(0, 300);
    }

    object.setPoints( poly );
    MyPolygoinF forces;
    forces.resize( object.points().size() );
    object.setForces(forces);
    object.setGravity(PointsType(0.0,40.0));

    //for (int i = 0; i < poly.size()-1; ++i)
    for (int i = 0; i < 4; ++i)
    {
        object.m_constrains.push_back({ i,i+1, distance(poly[i],poly[i+1] )} );
    }

    object.m_constrains.push_back({ 0,4, distance(poly[0],poly[4])} );
    object.m_constrains.push_back({ 0,2, distance(poly[0],poly[2]) } );
    object.m_constrains.push_back({ 1,3, distance(poly[1],poly[3]) } );



    int tsf =  5;
    object.m_constrains.push_back({ 5, 6, distance(poly[5],poly[6]) } );
    object.m_constrains.push_back({ 6,7, distance(poly[6],poly[7]) } );

    object.m_constrains.push_back({ 7,5, distance(poly[7],poly[5]) } );
    object.m_constrains.push_back({ 0, 5, distance(poly[0],poly[5]) } );
    object.m_constrains.push_back({ 0, 7, distance(poly[0],poly[7]) } );


    object.m_prev_points[2] = object.m_points[2] - QPointF(10,10);

    object.m_constrains.push_back({ 8, 9, distance(poly[8],poly[9]) } );
    object.m_constrains.push_back({ 9, 10, distance(poly[9],poly[10]) } );
    object.m_constrains.push_back({ 8, 10, distance(poly[8],poly[10]) } );

    object.m_constrains.push_back({ 7, 8, distance(poly[6],poly[8]) } );
    object.m_constrains.push_back({ 7, 10, distance(poly[6],poly[10]) } );

}

Window::Window()
{
    setGeometry(100,100,1100,1100);
    setMaximumHeight(1000);
    setMaximumWidth(1000);


    aliasedLabel = createLabel(tr("Aliased"));
    antialiasedLabel = createLabel(tr("Antialiased"));
    intLabel = createLabel(tr("Int"));
    floatLabel = createLabel(tr("Float"));

    QGridLayout *layout = new QGridLayout;

    QTimer *timer = new QTimer(this);

    circleWidgets[0][0] = new CircleWidget;
    circleWidgets[0][0]->setAntialiased(1);
    circleWidgets[0][0]->setFloatBased(1);


    constructObjectTREST(phisyc_obj);
    circleWidgets[0][0]->setFigure(phisyc_obj);

    connect(timer, SIGNAL(timeout()),
            circleWidgets[0][0], SLOT(nextAnimationFrame()));


    layout->addWidget(aliasedLabel, 0, 0);
    layout->addWidget(circleWidgets[0][0], 1, 1);
    timer->start(1000/60);
    setLayout(layout);
    setWindowTitle(tr("Concentric Circles"));
}
//! [2]

//! [3]
QLabel *Window::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    label->setMargin(2);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);
    return label;
}
//! [3]

