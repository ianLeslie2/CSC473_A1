#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMap>
#include <QList>
#include <QTimer>
#include "pointmass.h"
#include "linearspring.h"
#include "glcamera.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    glcamera camera;

private:
    QMap<int,bool> _keyDownState;
    QTimer* _keyCheckTimer;
    QTimer* _animStepTimer;
    bool _animPaused;

    bool _drawAxis;
    bool _drawForceApps;
    bool _drawPointMasses;
    bool _drawVelIndicators;
    bool _drawAcelIndicators;

    QList<PointMass*>* _pointMassList;
    QList<ForceApplier*>* _forceAppList;

    bool isKeyDown(int keyCode);
    void drawAnimObjects();

private slots:
    void updateCamera();
    void animStep();

protected:
    bool eventFilter(QObject *o, QEvent *e);

signals:

public slots:
    void clearSetup();
    void setUpBasicSprings();
    void setUpAngleSprings();
    void setUpCloth();

    void pauseTimer();
    void resumeTimer();
    void setShowAxisState(bool b);
    void setShowForceAppsState(bool b);
    void setShowPointMassesState(bool b);
    void setShowVelState(bool b);
    void setShowAcelState(bool b);

};

#endif // GLWIDGET_H
