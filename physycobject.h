#ifndef PHYSYCOBJECT_H
#define PHYSYCOBJECT_H

#include <QPolygonF>
#include <QVector>
#include <QPoint>
#include <QMap>

#include <iostream>


typedef QPointF PointsType;
typedef QVector<QPointF> MyPolygoinF;


struct Constrain
{
    int pointA;
    int pointB;
    double d;
};


class PhysycObject
{
public:

    PhysycObject();
    PhysycObject(const MyPolygoinF& points);
    PhysycObject(const MyPolygoinF& points, const  PointsType& gravity , const  MyPolygoinF& forces );

    void setPoints(const MyPolygoinF& points);
    void setGravity(const PointsType& gravity);
    void setForces(const MyPolygoinF& forces);



    void verlet(float timeStamp);
    void accumulate_forces();
    void satisfy_constrains();

    void doWork(float timeStamp = 1);


    double distance(const PointsType& a, const PointsType& b);


    MyPolygoinF& points();
    MyPolygoinF& prev_points();

    MyPolygoinF m_points;
    MyPolygoinF m_prev_points;

    MyPolygoinF m_forces;

    PointsType m_gravity;

    QVector <Constrain> m_constrains;

    int POINT_COUNT;

};

#endif // PHYSYCOBJECT_H
