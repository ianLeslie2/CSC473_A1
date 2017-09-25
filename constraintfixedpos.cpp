#include "constraintfixedpos.h"

ConstraintFixedPos::ConstraintFixedPos(QVector3D pos)
{
    this->pos = pos;
}


void ConstraintFixedPos::applyTo(PointMass *o)
{
    o->pos = this->pos;
}
