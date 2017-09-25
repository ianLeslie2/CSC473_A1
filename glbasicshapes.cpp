#include "glbasicshapes.h"
#include <GL/gl.h>
#include <QVector3D>
#include <QtMath>
#include <QDebug>

GLBasicShapes::GLBasicShapes()
{
}

void GLBasicShapes::renderBox(float scale)
{
    QVector3D p[8];
    for(int i=0; i<8; i++){
        p[i] = QVector3D(
                    i<4     ? scale : -scale,
                    i%4 < 2 ? scale : -scale,
                    i%2==0  ? scale : -scale
                    );
    }
    glBegin(GL_QUADS);
    // Face 1
    setNormalFromTriangle(&p[0],&p[1],&p[2]);
    qVertexWrap(&p[0]);
    qVertexWrap(&p[1]);
    qVertexWrap(&p[3]);
    qVertexWrap(&p[2]);
    // Face 2
    setNormalFromTriangle(&p[4],&p[6],&p[7]);
    qVertexWrap(&p[4]);
    qVertexWrap(&p[6]);
    qVertexWrap(&p[7]);
    qVertexWrap(&p[5]);

    // Face 3
    setNormalFromTriangle(&p[1],&p[5],&p[7]);
    qVertexWrap(&p[1]);
    qVertexWrap(&p[5]);
    qVertexWrap(&p[7]);
    qVertexWrap(&p[3]);
    // Face 4
    setNormalFromTriangle(&p[0],&p[2],&p[6]);
    qVertexWrap(&p[0]);
    qVertexWrap(&p[2]);
    qVertexWrap(&p[6]);
    qVertexWrap(&p[4]);

    // Face 5
    setNormalFromTriangle(&p[4],&p[5],&p[1]);
    qVertexWrap(&p[4]);
    qVertexWrap(&p[5]);
    qVertexWrap(&p[1]);
    qVertexWrap(&p[0]);
    // Face 6
    setNormalFromTriangle(&p[3],&p[7],&p[6]);
    qVertexWrap(&p[3]);
    qVertexWrap(&p[7]);
    qVertexWrap(&p[6]);
    qVertexWrap(&p[2]);
    glEnd();
}

void GLBasicShapes::renderTetrahedron(float scale)
{
    QVector3D p[4];
    p[0] = QVector3D(0.0f,scale,0.0f);
    float alpha = 0.33887f;
    float faceY = -qSin(alpha);
    for(int i=1; i<4; i++){
        float ang = -(2.0f*M_PI)*float(i)/3.0f;
        p[i] = scale*QVector3D(qCos(alpha)*qCos(ang),faceY,qCos(alpha)*qSin(ang));
    }

    glBegin(GL_TRIANGLES);
    //Face 1
    setNormalFromTriangle(&p[0],&p[2],&p[1]);
    qVertexWrap(&p[0]);
    qVertexWrap(&p[2]);
    qVertexWrap(&p[1]);

    //Face 2
    setNormalFromTriangle(&p[0],&p[3],&p[2]);
    qVertexWrap(&p[0]);
    qVertexWrap(&p[3]);
    qVertexWrap(&p[2]);

    //Face 3
    setNormalFromTriangle(&p[0],&p[1],&p[3]);
    qVertexWrap(&p[0]);
    qVertexWrap(&p[1]);
    qVertexWrap(&p[3]);

    //Face 4
    setNormalFromTriangle(&p[1],&p[2],&p[3]);
    qVertexWrap(&p[1]);
    qVertexWrap(&p[2]);
    qVertexWrap(&p[3]);
    glEnd();
}

void GLBasicShapes::renderPointMarker(float scale)
{
    glPushMatrix();

    for(int i=0; i<4; i++){
        renderBox(scale);
        glRotatef(50,1,0,0);
        glRotatef(30,0,1,0);
        glRotatef(10,0,0,1);
    }

    glPopMatrix();
}

void GLBasicShapes::setNormalFromTriangle(QVector3D *v0, QVector3D *v1, QVector3D *v2)
{
    QVector3D vect1 = *v0 - *v1;
    QVector3D vect2 = *v2 - *v1;
    QVector3D normalV = QVector3D::crossProduct(vect1,vect2).normalized();
    qNormalWrap(&normalV);
}

void GLBasicShapes::qNormalWrap(QVector3D *vect){
    glNormal3f(vect->x(),vect->y(),vect->z());
}

void GLBasicShapes::qVertexWrap(QVector3D *vect){
    glVertex3f(vect->x(),vect->y(),vect->z());
}
