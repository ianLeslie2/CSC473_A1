#include "pointmass.h"
#include "GL/gl.h"
#include "glutility.h"
#include "Constraints/constraint.h"

PointMass::PointMass(float mass, QVector3D pos)
{
    this->mass = mass;
    this->pos = pos;

    vel = QVector3D(0,0,0);
    acel = QVector3D(0,0,0);
    netF = QVector3D(0,0,0);

    _constraintList = new QList<Constraint*>();
    _hasOldPos = false;

    setColor(0.3,0.8,0.3);
}

PointMass::~PointMass()
{
    for(int i=0; i<_constraintList->size(); i++){
        delete _constraintList->at(i);
    }
    delete _constraintList;
}

PointMass* PointMass::setColor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    return this;
}

PointMass *PointMass::addConstraint(Constraint *obj)
{
    _constraintList->append(obj);
    obj->applyTo(this);
    return this;
}

// Using Verlet integration as it is described here:
// https://en.wikipedia.org/wiki/Verlet_integration
void PointMass::performStep(float dt)
{
   // Save position & velocity so it can be used to
   // calculate the true velocity and acelleration later
   QVector3D startPos = pos;
   QVector3D startVel = vel;

   acel = netF/mass;
   if(!_hasOldPos){
       // First step of verlet integration
       pos = pos + vel*dt + 0.5f*acel*dt*dt;
       _hasOldPos = true;
   }
   else{
       // Normal verlet step
       pos = 2*pos - _oldPos + acel*dt*dt;
   }
   // Store position we had before this step
   _oldPos = startPos;

   // Apply constraints
   for(int i=0; i<_constraintList->size(); i++){
       _constraintList->at(i)->applyTo(this);
   }

   // Set true velocity based on positional change
   vel = (pos - startPos)/dt;

   // Set true acelleration based on velocity change
   acel = (vel - startVel)/dt;

   // Reset net-force tracker
   netF = QVector3D(0,0,0);
}

void PointMass::draw(bool showMain, bool showVel, bool showAcel)
{
    glPushMatrix();
    glTranslatef(pos.x(),pos.y(),pos.z());

    if(showMain){
        glColor3f(r,g,b);
        GLUtility::renderBox(0.1);
    }

    if(showVel || showAcel){
        // Draw velocity & accelleration indicators
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);

        if (showVel){
            glColor3f(0,0,1);
            glVertex3f(0,0,0);
            GLUtility::qVertexWrap(&vel);
        }
        if (showAcel){
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            GLUtility::qVertexWrap(&acel);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}
