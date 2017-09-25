#include "angularspring.h"
#include <QtMath>
#include <GL/gl.h>
#include "glutility.h"

AngularSpring::AngularSpring(float k,
                             float damper,
                             PointMass *obj,
                             QVector3D orbitCenter,
                             QVector3D restAxisUV,
                             QVector3D orbitAxisUV)
{
    this->k = k;
    this->damper = damper;
    this->obj = obj;
    this->orbitCenter = orbitCenter;
    this->restAxisUV = restAxisUV;
    this->orbitAxisUV = orbitAxisUV;
}

void AngularSpring::applyForces()
{
    float dist = obj->pos.distanceToPoint(orbitCenter);
    float circumference = 2.0f*M_PI*dist;

    QVector3D relV = obj->pos - orbitCenter;
    QVector3D dirUV = relV.normalized();
    float angle = qAcos(QVector3D::dotProduct(dirUV,restAxisUV));

    QVector3D restoreUV = QVector3D::crossProduct(dirUV,orbitAxisUV);
    if(QVector3D::dotProduct(restoreUV,restAxisUV) < 0){
        // Restorative UV is pointing wrong direction
        restoreUV *= -1;
    }
    float restoreMag = QVector3D::dotProduct(restoreUV,obj->vel);
    float angleVel = -(restoreMag/circumference)*2.0*M_PI;

    // Calculate restorative torque force
    float torque = k*angle + damper*angleVel;
    QVector3D restoreV = restoreUV*torque/dist;
    obj->netF += restoreV;
}

void AngularSpring::draw()
{
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    GLUtility::qVertexWrap(&orbitCenter);
    GLUtility::qVertexWrap(&obj->pos);

    GLUtility::qVertexWrap(&orbitCenter);
    QVector3D temp = orbitCenter + restAxisUV;
    GLUtility::qVertexWrap(&temp);
    glEnd();
}
