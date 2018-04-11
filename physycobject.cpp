#include "physycobject.h"

const int ITERATIONS_COUNT =3;

PhysycObject::PhysycObject()
{

}

PhysycObject::PhysycObject(const MyPolygoinF &points):
   m_points(points),
   m_gravity(PhPointsType(0.0,1.0))
{
    m_prev_points = points;
}

PhysycObject::PhysycObject(const MyPolygoinF &points, const PhPointsType &gravity, const  MyPolygoinF &forces):
    m_points(points),
    m_gravity(gravity),
    m_forces(forces)
{

    m_prev_points = points;

}

void PhysycObject::setPoints(const MyPolygoinF &points)
{

    m_points = points;
    m_prev_points = points;
}

void PhysycObject::setGravity(const PhPointsType &gravity)
{
    m_gravity = gravity;
}

void PhysycObject::setForces(const MyPolygoinF &forces)
{
    m_forces = forces;
}


MyPolygoinF &PhysycObject::points()
{
    return m_points;
}

MyPolygoinF &PhysycObject::prev_points()
{
    return m_prev_points;
}


void PhysycObject::verlet(float timeStamp)
{
    for(int i =0;i<m_points.size(); i++)
    {
        PhPointsType& point  = m_points[i];
        PhPointsType tmp = point;
        PhPointsType&  prev_point = m_prev_points[i];
        PhPointsType&  force = m_forces[i];
        point += point - prev_point + force * timeStamp*timeStamp;
        prev_point = tmp;
    }


    auto a = m_points[0].ry();
    auto b =  m_prev_points[0].ry();
    std::cout << a-b << std::endl;
}

void PhysycObject::accumulate_forces() {
    for(int i =0; i <m_points.size(); i++)
    {
        m_forces[i] = m_gravity;
    }

}

void PhysycObject::satisfy_constrains()
{

    for(int i=0; i<ITERATIONS_COUNT; i++)
    {
        for(int j=0;j<m_points.size();j++)
        {
            PhPointsType& point = m_points[j];
            point.rx() = std::min(std::max(point.rx(), -600.0 ), 300.0);
            point.ry() = std::min(std::max(point.ry(), -600.0 ), 300.0);
        }

        for(int j=0; j<m_constrains.size();j++)
        {
            Constrain& con = m_constrains[j];

            QPointF &a = m_points[con.pointA];
            QPointF &b = m_points[con.pointB];
            QPointF deltaPoint = a - b;

            double deltaLength = distance(QPointF(0,0), deltaPoint);
            if ( deltaLength != deltaLength)
                deltaLength = 0;
            double diff = ( distance(a,b) - con.d ) / distance(a,b);
            if ( diff != diff)
                diff = 0;
            a-=deltaPoint*0.5*diff;
            b+=deltaPoint*0.5*diff;
        }
    }
}

void PhysycObject::doWork(float timeStamp)
{
    accumulate_forces();
    verlet(timeStamp/1000);
    satisfy_constrains();
}

double PhysycObject::distance(const PhPointsType &a, const PhPointsType &b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return (  std::sqrt(dx*dx + dy*dy) );

}

