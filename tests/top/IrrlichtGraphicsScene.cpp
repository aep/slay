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
    if(qgs){
        qgs->setSceneRect(0,0,w-20,h-20);
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
    //driver->beginScene( false, false, SColor( 255, 128, 128, 128 ));

    updateIrrlichtScene();
    //    scene->drawAll();

    if(qgs){
        glDisable (GL_LIGHTING);
        //((QWidget*)qgv)->render(context()->device(),QPoint(),QRegion(),DrawChildren);
                QPainter painter(context()->device());
                qgs->render (&painter );
    }

    //driver->endScene();
    glFinish();
    QTimer::singleShot(20, this, SLOT(updateGL()));
}
