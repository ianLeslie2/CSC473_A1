#ifndef CONSTRAINT_H
#define CONSTRAINT_H

class PointMass;

class Constraint
{
public:
    virtual ~Constraint(){}
    virtual void applyTo(PointMass*)=0;
};

#endif // CONSTRAINT_H
