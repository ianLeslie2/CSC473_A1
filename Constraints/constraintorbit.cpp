#include "constraintorbit.h"
#include "pointmass.h"

ConstraintOrbit::ConstraintOrbit(QVector3D orbitCenter, QVector3D orbitAxisUV, float dist)
{
    this->orbitCenter = orbitCenter;
    this->orbitAxisUV = orbitAxisUV;
    this->dist = dist;
}

void ConstraintOrbit::applyTo(PointMass *o)
{
    QVector3D relV = o->pos - orbitCenter;
    // Forces vector in orbit plane
    relV -= QVector3D::dotProduct(relV,orbitAxisUV)*orbitAxisUV;
    o->pos = orbitCenter + relV.normalized()*dist;
}
