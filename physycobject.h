#ifndef PHYSYCOBJECT_H
#define PHYSYCOBJECT_H

#include "basictypes.h"

#include <QPolygonF>
#include <QVector>
#include <QPoint>
#include <QMap>

#include <iostream>






struct Constrain
{
    Constrain():
        pointA(0),
        pointB(0),
        d(0.0)
    {

    }
    Constrain(int _pointA, int _pointB):
        pointA(_pointA),
        pointB(_pointB)
    {
        //empty
    }
    int pointA;
    int pointB;
    double d;
};

struct Edge
{
    int pointA;
    int pointB;
};

struct ExternalConstrain
{
    int meshA;
    int pointA;
    int meshB;
    int pointB;
};

struct PhMesh {
    QVector<PhPointsType> points;
    QVector<Constrain> constrains;
    QVector<Edge> edges;
};

struct PhObject {
    QVector<PhMesh> meshs;
    QVector<ExternalConstrain> external_constrains;
};


class ParticleSystem {
    void verlet(float timeStamp);
    void accumulate_forces();
    void satisfy_constrains();
};


class PhysycObject
{
public:

    PhysycObject();
    PhysycObject(const MyPolygoinF& points);
    PhysycObject(const MyPolygoinF& points, const  PhPointsType& gravity , const  MyPolygoinF& forces );

    void setPoints(const MyPolygoinF& points);
    void setGravity(const PhPointsType& gravity);
    void setForces(const MyPolygoinF& forces);



    void verlet(float timeStamp);
    void accumulate_forces();
    void satisfy_constrains();

    void doWork(float timeStamp = 1);


    double distance(const PhPointsType& a, const PhPointsType& b);


    MyPolygoinF& points();
    MyPolygoinF& prev_points();

    MyPolygoinF m_points;
    MyPolygoinF m_prev_points;

    MyPolygoinF m_forces;

    PhPointsType m_gravity;

    QVector <Constrain> m_constrains;

    int POINT_COUNT;

};

#endif // PHYSYCOBJECT_H
