#include "constantforcefield.h"

ConstantForceField::ConstantForceField(QVector3D forceV, QList<PointMass*>* pointMassList)
{
    this->forceV = forceV;
    _pointMassList = pointMassList;
}

void ConstantForceField::applyForces(){
    for(int i=0; i<_pointMassList->size(); i++){
        PointMass* oRef = _pointMassList->at(i);
        oRef->netF += oRef->mass * forceV;
    }
}

void ConstantForceField::draw(){
    // Has no graphic representation
}
