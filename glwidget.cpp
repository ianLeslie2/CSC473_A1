#include "glwidget.h"
#include <QtMath>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <glbasicshapes.h>
#include "ForceAppliers/constantforcefield.h"
#include "ForceAppliers/angularspring.h"
#include "Constraints/constraintfixedpos.h"
#include "Constraints/constraintorbit.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    camera = glcamera(0.0f,
                       0.0f,
                       6.0f,
                       0.2f,
                       180.0f);
    _keyCheckTimer = new QTimer(this);
    connect(_keyCheckTimer,SIGNAL(timeout()), this, SLOT(updateCamera()));
    _keyCheckTimer->start(30);
    _animStepTimer = new QTimer(this);
    connect(_animStepTimer,SIGNAL(timeout()), this, SLOT(animStep()));
    _animStepTimer->start(30);
    _animPaused = false;

    // Object lists for animation
    _pointMassList = new QList<PointMass*>();
    _forceAppList = new QList<ForceApplier*>();

    _drawAxis = false;
    _drawForceApps = true;
    _drawPointMasses = true;
    _drawVelIndicators = false;
    _drawAcelIndicators = false;

}

bool GLWidget::isKeyDown(int keyCode)
{
    if (_keyDownState.contains(keyCode)){
        return _keyDownState[keyCode];
    }
    return false;
}

void GLWidget::drawAnimObjects()
{
    if(_drawForceApps){
        // Render springs
        for(int i=0; i<_forceAppList->size(); i++){
            _forceAppList->at(i)->draw();
        }
    }

    // Render point masses
    for(int i=0; i<_pointMassList->size(); i++){
        _pointMassList->at(i)->draw(_drawPointMasses,_drawVelIndicators,_drawAcelIndicators);
    }
}

void GLWidget::clearSetup()
{
    //Remove all force-app and point-mass objects
    for(int i=0; i<_forceAppList->size(); i++){
        delete _forceAppList->at(i);
    }

    for(int i=0; i<_pointMassList->size(); i++){
        delete _pointMassList->at(i);
    }
    _forceAppList->clear();
    _pointMassList->clear();

    update();
}

void GLWidget::updateCamera()
{
    float yawIncr = 3.0f;
    float pitchIncr = 1.7f;
    float distIncr = 0.3f;

    bool dirty = false;
    if(isKeyDown(87)){
        //W
        camera.pitch += pitchIncr;
        dirty = true;
    }
    if(isKeyDown(83)){
        //S
        camera.pitch -= pitchIncr;
        dirty = true;
    }
    if(isKeyDown(65)){
        //A
        camera.yaw -= yawIncr;
        dirty = true;
    }
    if(isKeyDown(68)){
        //D
        camera.yaw += yawIncr;
        dirty = true;
    }
    if(isKeyDown(81)){
        //Q
        camera.dist -= distIncr;
        dirty = true;
    }
    if(isKeyDown(69)){
        //E
        camera.dist += distIncr;
        dirty = true;
    }
    if(dirty){
        //Update widget
        update();
    }
}

void GLWidget::animStep()
{
    if(_animPaused){
        return;
    }
    float dv = 1.0f/30.0f;

    // Apply Forces
    for(int i=0; i<_forceAppList->size(); i++){
        _forceAppList->at(i)->applyForces();
    }

    // Update positions
    for(int i=0; i<_pointMassList->size(); i++){
        _pointMassList->at(i)->performStep(dv);
    }

    update();
}

bool GLWidget::eventFilter(QObject *, QEvent *e){
    if ( e->type() == QEvent::KeyPress ) {
        QKeyEvent *k = static_cast<QKeyEvent*>(e);
        _keyDownState[k->key()] = true;
    }
    else if(e->type() == QEvent::KeyRelease){
        QKeyEvent *k = static_cast<QKeyEvent*>(e);
        _keyDownState[k->key()] = false;
    }
    return false;
}

void GLWidget::setUpBasicSprings()
{
    // Remove old objects if there are any
    clearSetup();

    // Setup gravity
    _forceAppList->append(new ConstantForceField(QVector3D(0,-0.3,0),_pointMassList));

    // Setup a few linear springs
    QVector3D anchorBase = QVector3D(-1,1,0);
    QVector3D offsetPerSet = QVector3D(1,0,0);
    QVector3D defAttachOffset = QVector3D(0,-1,0);
    float defMass = 1.0;
    float defSprintRestDist = 1.5;
    float defSpringK = 0.6;
    float defSpringDamper = 0.1;
    int setCount = 3;

    for(int i=0; i<setCount; i++){
        // Basic setup
        PointMass* o1 = new PointMass(defMass,anchorBase + offsetPerSet*i);
        PointMass* o2 = new PointMass(defMass,anchorBase + offsetPerSet*i + defAttachOffset);
        LinearSpring* spring = new LinearSpring(defSpringK,defSpringDamper,defSprintRestDist,o1,o2);
        o1->addConstraint(new ConstraintFixedPos(o1->pos));
        _pointMassList->append(o1);
        _pointMassList->append(o2);
        _forceAppList->append(spring);

        // Set-specific modifications
        if (i==0){
            spring->damper = 0;
        }
        else if(i==1){
            o1->setColor(0.8,0.2,0.2);
            o2->setColor(0.8,0.2,0.2);
        }
        else if(i==2){
            o1->setColor(0.2,0.2,0.8);
            o2->setColor(0.2,0.2,0.8);
            o2->pos += QVector3D(0.3,0,0);
        }
    }
}

void GLWidget::setUpAngleSprings()
{
    // Remove old objects if there are any
    clearSetup();

    // Setup gravity
    _forceAppList->append(new ConstantForceField(QVector3D(0,-0.3,0),_pointMassList));

    QVector3D orbitCenter = QVector3D(0,0,-1);
    QVector3D relPos = QVector3D(1,1,0);
    QVector3D restAxisUV = QVector3D(1,0,0);
    QVector3D orbitAxisUV = QVector3D(0,0,1);
    QVector3D offsetPerSet = QVector3D(0,0,1);
    float mass = 1.0;
    float dist = 1.0;
    float k = 0.6;
    float damper = 0.1f;
    int setCount = 3;

    for(int i=0; i<setCount; i++){
        // Setup default angular spring
        PointMass* obj = new PointMass(mass,orbitCenter + relPos + offsetPerSet*i);
        AngularSpring* spring = new AngularSpring(k,
                                               damper,
                                               obj,
                                               orbitCenter + offsetPerSet*i,
                                               restAxisUV,
                                               orbitAxisUV);
        ConstraintOrbit* constraint = new ConstraintOrbit(orbitCenter + offsetPerSet*i,orbitAxisUV,dist);
        obj->addConstraint(constraint);

        _forceAppList->append(spring);
        _pointMassList->append(obj);

        // Make case-specific changes
        if(i==0){
            spring->damper = 0;
        }
        else if(i==1){
            obj->setColor(0.8,0.2,0.2);
        }
        else if(i==2){
            obj->setColor(0.2,0.2,0.8);
            constraint->dist = 2.0;
        }

    }
}

void GLWidget::setUpCloth()
{
    // Remove old objects if there are any
    clearSetup();

    // Setup gravity
    _forceAppList->append(new ConstantForceField(QVector3D(0,-0.3,0),_pointMassList));

    float spacingScale = 0.1;
    int cols = 14;
    int rows = 10;
    float pMass = 0.1;
    float springK = 2.2f;
    float springDamper = 0.1f;
    QVector3D midP = QVector3D(1,1,0);
    QVector3D nextColV = spacingScale*QVector3D(1,0,0);
    QVector3D nextRowV = spacingScale*QVector3D(0,0.2,-1).normalized();
    QVector3D topLeft = midP -0.5*((cols-1)*nextColV + (rows-1)*nextRowV);

    // Create points in cloth
    int startIdx = _pointMassList->size();
    for(int i=0; i < cols; i++){
        for(int j=0; j<rows; j++){
            PointMass *obj = new PointMass(pMass,topLeft + i*nextColV + j*nextRowV);
            _pointMassList->append(obj);

            //Fix vertices on one side
            if(i==0){
                obj->addConstraint(new ConstraintFixedPos(obj->pos));
            }
        }
    }

    // Adds horizontal, vertical, and diagonal springs
    float colDist = nextColV.length();
    float rowDist = nextRowV.length();
    float diagDist = qSqrt(colDist*colDist + rowDist*rowDist);
    // Add most springs
    for(int i=1; i<cols; i++){
        for(int j=1; j<rows; j++){
            PointMass *topLeft  = _pointMassList->at(startIdx + (i-1)*rows + (j-1));
            PointMass *topRight = _pointMassList->at(startIdx + (i-0)*rows + (j-1));
            PointMass *botLeft  = _pointMassList->at(startIdx + (i-1)*rows + (j-0));
            PointMass *mainP    = _pointMassList->at(startIdx + (i-0)*rows + (j-0));

            _forceAppList->append(new LinearSpring(springK,springDamper,colDist, mainP,botLeft));
            _forceAppList->append(new LinearSpring(springK,springDamper,rowDist, mainP,topRight));
            _forceAppList->append(new LinearSpring(springK,springDamper,diagDist,mainP,topLeft));
            _forceAppList->append(new LinearSpring(springK,springDamper,diagDist,topRight,botLeft));
        }
    }
    // Add some springs missed by the last loop that lie on the boundary
    for(int i=1; i<cols; i++){
        PointMass *p1 = _pointMassList->at(startIdx + (i-1)*rows);
        PointMass *p2 = _pointMassList->at(startIdx + (i-0)*rows);
        _forceAppList->append(new LinearSpring(springK,springDamper,colDist,p1,p2));
    }
    for(int j=1; j<rows; j++){
        PointMass *p1 = _pointMassList->at(startIdx + (j-1));
        PointMass *p2 = _pointMassList->at(startIdx + (j-0));
        _forceAppList->append(new LinearSpring(springK,springDamper,rowDist,p1,p2));
    }

    // Add 'bending' springs
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            PointMass *mainP = _pointMassList->at(startIdx + (i-0)*rows + (j-0));
            if(i > 1){
                PointMass *leftP = _pointMassList->at(startIdx + (i-2)*rows + (j-0));
                _forceAppList->append(new LinearSpring(springK,springDamper,colDist*2.0f,mainP,leftP));
            }
            if(j > 1){
                PointMass *topP = _pointMassList->at(startIdx + (i-0)*rows + (j-2));
                _forceAppList->append(new LinearSpring(springK,springDamper,rowDist*2.0f,mainP,topP));
            }
        }
    }


}

void GLWidget::pauseTimer()
{
    _animPaused = true;
}

void GLWidget::resumeTimer()
{
    _animPaused = false;
}

void GLWidget::setShowAxisState(bool b)
{
    _drawAxis = b;
    update();
}

void GLWidget::setShowForceAppsState(bool b)
{
    _drawForceApps = b;
    update();
}

void GLWidget::setShowPointMassesState(bool b)
{
    _drawPointMasses = b;
    update();
}

void GLWidget::setShowVelState(bool b)
{
    _drawVelIndicators = b;
    update();
}

void GLWidget::setShowAcelState(bool b)
{
    _drawAcelIndicators = b;
    update();
}

void GLWidget::initializeGL(){
    glClearColor(0.6,0.6,0.6,1.0);
}

void GLWidget::paintGL(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.applyModelTransform();

    if(_drawAxis){
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        // X-axis
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        // Y-axis
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);
        // Z-axis
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
        glEnd();
        glEnable(GL_LIGHTING);
    }

    drawAnimObjects();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = float(w)/float(h);
    float fov = M_PI/8.0f;
    float n = 0.1f;
    float f = 100.0f;
    float nearPlaneRad = n*qTan(fov);
    glFrustum(nearPlaneRad*ratio,
              -nearPlaneRad*ratio,
              -nearPlaneRad,
              nearPlaneRad,
              n,
              f);
}
