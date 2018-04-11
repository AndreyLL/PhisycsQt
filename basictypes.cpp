#include "basictypes.h"


double phDistance(const PhPointsType &a, const PhPointsType &b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return (  std::sqrt(dx*dx + dy*dy) );

}
