#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <QPointF>
#include <QVector>


typedef QPointF PhPointsType;
typedef QVector<QPointF> MyPolygoinF;


double distance(const PhPointsType &a, const PhPointsType &b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return (  std::sqrt(dx*dx + dy*dy) );

}

#endif // BASICTYPES_H
