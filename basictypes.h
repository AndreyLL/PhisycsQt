#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <QPointF>
#include <QVector>


typedef QPointF PhPointsType;
typedef QVector<QPointF> MyPolygoinF;


double phDistance(const PhPointsType &a, const PhPointsType &b);


#endif // BASICTYPES_H
