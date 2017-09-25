#ifndef CONSTRAINTORBIT_H
#define CONSTRAINTORBIT_H

#include "constraint.h"
#include <QVector3D>

class ConstraintOrbit : public Constraint
{
public:
    ConstraintOrbit(QVector3D orbitCenter, QVector3D orbitAxisUV, float dist);
    void applyTo(PointMass *o);

    QVector3D orbitCenter;
    QVector3D orbitAxisUV;
    float dist;
};

#endif // CONSTRAINTORBIT_H
