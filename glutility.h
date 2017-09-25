#ifndef GLUTILITY_H
#define GLUTILITY_H
#include <QVector3D>

class GLUtility
{
public:
    static void renderBox(float scale);
    static void renderTetrahedron(float scale);

    static void setNormalFromTriangle(QVector3D* v0,
                                      QVector3D* v1,
                                      QVector3D* v2);

    static void qVertexWrap(QVector3D* vect);
    static void qNormalWrap(QVector3D* vect);
};

#endif // GLUTILITY_H
