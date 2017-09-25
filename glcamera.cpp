#include "glcamera.h"
#include <QtMath>
#include <GL/gl.h>

glcamera::glcamera(float yaw,
                   float pitch,
                   float dist,
                   float minDist,
                   float pitchRange
                   )
{
    this->yaw = yaw;
    this->pitch = pitch;
    this->dist = dist;
    this->minDist = minDist;
    this->pitchRange = pitchRange;
}

void glcamera::clampValues(){
    pitch = qBound(-pitchRange/2.0f,pitch,pitchRange/2.0f);
    dist = qMax(minDist,dist);
}

void glcamera::applyModelTransform()
{
    this->clampValues();

    glTranslatef(0,0,-dist);
    glRotatef(pitch,1,0,0);
    glRotatef(yaw,0,1,0);
}





