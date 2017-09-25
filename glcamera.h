#ifndef GLCAMERA_H
#define GLCAMERA_H
#include <QVector3D>

class glcamera
{
public:
    glcamera();
    glcamera(float yaw,
             float pitch,
             float dist,
             float minDist,
             float pitchRange);

    float dist;
    float minDist;
    float yaw;
    float pitch;
    float pitchRange;

    void clampValues();
    void applyModelTransform();

private:



};

#endif // GLCAMERA_H
