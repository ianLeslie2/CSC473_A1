#ifndef GLBASICSHAPES_H
#define GLBASICSHAPES_H
#include <QVector3D>

class GLBasicShapes
{
public:
    GLBasicShapes();
    static void renderBox(float scale);
    static void renderTetrahedron(float scale);
    static void renderPointMarker(float scale);

    static void setNormalFromTriangle(QVector3D* v0,
                                      QVector3D* v1,
                                      QVector3D* v2);

    static void qVertexWrap(QVector3D* vect);
    static void qNormalWrap(QVector3D* vect);
};

#endif // GLBASICSHAPES_H
