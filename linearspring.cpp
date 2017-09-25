#include "linearspring.h"
#include "GL/gl.h"
#include "glbasicshapes.h"
#include "QDebug"

LinearSpring::LinearSpring(float k, float damper, float relaxedDist, PointMass *obj1, PointMass *obj2)
{
    this->k = k;
    this->damper = damper;
    this->relaxedDist = relaxedDist;
    this->obj1 = obj1;
    this->obj2 = obj2;
}

void LinearSpring::applyForces()
{
    float curDist = obj1->pos.distanceToPoint(obj2->pos);
    // Directional unit vector from object 1 to object 2
    QVector3D dirUV = (obj2->pos - obj1->pos).normalized();
    // Calculates rate of spring expansion based on current velocity of attached objects
    float expandVelocity = QVector3D::dotProduct(dirUV,obj2->vel) + QVector3D::dotProduct(-dirUV,obj1->vel);

    float fMag = k*(curDist - relaxedDist) + damper*expandVelocity;
    obj1->netF += fMag*dirUV;
    obj2->netF -= fMag*dirUV;
}

void LinearSpring::draw()
{
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    GLBasicShapes::qVertexWrap(&obj1->pos);
    GLBasicShapes::qVertexWrap(&obj2->pos);
    glEnd();
}
