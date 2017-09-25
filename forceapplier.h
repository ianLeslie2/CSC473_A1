#ifndef FORCEAPPLIER_H
#define FORCEAPPLIER_H

class ForceApplier
{
public:
    virtual ~ForceApplier(){}
    virtual void applyForces()=0;
    virtual void draw()=0;
};

#endif // FORCEAPPLIER_H
