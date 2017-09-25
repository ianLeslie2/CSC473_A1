#ifndef ANGULARSPRING_H
#define ANGULARSPRING_H

#include "forceapplier.h"
#include <QVector3D>
#include "pointmass.h"

class AngularSpring : public ForceApplier
{
public:
    AngularSpring(float k,
                  float damper,
                  PointMass* obj,
                  QVector3D orbitCenter,
                  QVector3D restAxisUV,
                  QVector3D orbitAxisUV);
    void applyForces();
    void draw();

    float k;
    float damper;
    PointMass* obj;
    QVector3D orbitCenter;
    QVector3D restAxisUV;
    QVector3D orbitAxisUV;
};

#endif // ANGULARSPRING_H
