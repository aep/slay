#include <QMetaType>
#include <QTimer>
#include "IrrlichtGraphicsScene.hpp"
#include <irrlicht.h>
#include <QPainter>
#include <QPaintEngine>
#include <QtOpenGL>
#include <QGLWidget>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtGraphicsView::IrrlichtGraphicsView()
    :QGLWidget()
    ,device(0)
    ,view(this)
    ,fps(0)
    ,qgs(0)
    ,qgv(new QGraphicsView)
{
    setAutoFillBackground(false);
    qgv->setAutoFillBackground(false);
    qgv->setAttribute(Qt::WA_NoSystemBackground);
}

IrrlichtGraphicsView::~IrrlichtGraphicsView() {
    if(device){
        device->closeDevice();
        device->run();
        device->drop();
    }
    m_time.start();
    update();
}


void IrrlichtGraphicsView::setScene ( QGraphicsScene * scene ){
    qgs=scene;
    qgv->setScene(qgs);
}


void IrrlichtGraphicsView::resizeGL ( int w, int h ){
    if(device){
        irr::core::dimension2d<uint> size;
        size.Width = w;
        size.Height = h;
        device->getVideoDriver()->OnResize(size);
    }

}

#include <QLabel>
extern QLabel * fpslabel;


void IrrlichtGraphicsView::initializeGL (){
    if(!device){
        SIrrlichtCreationParameters createParams;
        createParams.DriverType = irr::video::EDT_OPENGL;
        createParams.IgnoreInput = true;
        createParams.WindowId = ( void * ) winId();
        device = createDeviceEx( createParams );
        if(!device){
            qFatal("failed to initialise irrlicht");
            return;
        }
        driver= device->getVideoDriver();
        scene= device->getSceneManager();
        initializeIrrlichtScene();
    }
}


void IrrlichtGraphicsView::paintGL() {
    int cfps=1000/m_time.restart();
    if(fps!=cfps){
        fps=(fps+cfps)/2;
    }

    fpslabel->setText(QString::number(fps)+"fps");


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    driver->beginScene( false, false, SColor( 255, 128, 128, 128 ));

    updateIrrlichtScene();
    scene->drawAll();

    if(qgs){
        ((QWidget*)qgv)->render(context()->device(),QPoint(),QRegion(),DrawChildren);
            //QPainter painter(context()->device());
        //        qgs->render (&painter );
    }

    driver->endScene();



    QTimer::singleShot(20, this, SLOT(updateGL()));
    return;

    glDisable (GL_LIGHTING);

    //    glPushMatrix();

    //glPopMatrix();

    // switch to projection mode
    glMatrixMode(GL_PROJECTION);
    // save previous matrix which contains the
    //settings for the perspective projection
        //    glPushMatrix();
    // reset matrix
    glLoadIdentity();
    // set a 2D orthographic projection
    gluOrtho2D(0, width(), 0, height());
    // invert the y axis, down is positive
    glScalef(1, -1, 1);
    // mover the origin from the bottom left corner
    // to the upper left corner
    glTranslatef(0, -height(), 0);

    //    glMatrixMode(GL_MODELVIEW);


    QTimer::singleShot(20, this, SLOT(updateGL()));
}
