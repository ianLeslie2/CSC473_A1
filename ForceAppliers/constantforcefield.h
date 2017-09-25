#ifndef CONSTANTFORCEFIELD_H
#define CONSTANTFORCEFIELD_H

#include "forceapplier.h"
#include <QList>
#include <QVector3D>
#include "pointmass.h"

class ConstantForceField : public ForceApplier
{
public:
    ConstantForceField(QVector3D forceV, QList<PointMass*>* pointMassList);

    QVector3D forceV;

    void applyForces();
    void draw();

private:
    QList<PointMass*>* _pointMassList;
};

#endif // CONSTANTFORCEFIELD_H
