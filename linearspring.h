#ifndef LINEARSPRING_H
#define LINEARSPRING_H
#include "pointmass.h"
#include "forceapplier.h"

class LinearSpring : public ForceApplier
{
public:
    LinearSpring(float k, float damper, float relaxedDist, PointMass* obj1, PointMass* obj2);

    void applyForces();
    void draw();

    PointMass* obj1;
    PointMass* obj2;

    float k;
    float damper;
    float relaxedDist;
};

#endif // LINEARSPRING_H
