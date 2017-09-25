#ifndef POINTMASS_H
#define POINTMASS_H

#include <QVector3D>
#include <QList>

class Constraint;

class PointMass
{
public:
    PointMass(float mass, QVector3D pos);

    ~PointMass();

    float mass;
    QVector3D pos;
    QVector3D vel;
    QVector3D acel;


    // Draw color
    float r,g,b;

    QVector3D netF;

    PointMass* setColor(float r, float g, float b);
    PointMass* addConstraint(Constraint *obj);
    void performStep(float dt);
    void draw(bool showMain, bool showVel, bool showAcel);

private:
    bool _hasOldPos;
    QVector3D _oldPos;
    QList<Constraint*>* _constraintList;
};

#endif // POINTMASS_H
