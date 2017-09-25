#ifndef CONSTRAINTFIXEDPOS_H
#define CONSTRAINTFIXEDPOS_H

#include "constraint.h"
#include "pointmass.h"

class ConstraintFixedPos : public Constraint
{
public:
    ConstraintFixedPos(QVector3D pos);
    void applyTo(PointMass *o);

    QVector3D pos;
};

#endif // CONSTRAINTFIXEDPOS_H
