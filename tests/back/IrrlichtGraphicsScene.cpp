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

IrrlichtGraphicsScene::IrrlichtGraphicsScene(IrrlichtGraphicsView * v)
    :QGraphicsScene()
    ,device(0)
    ,view(v)
    ,fps(0)
{
}

IrrlichtGraphicsScene::~IrrlichtGraphicsScene() {
    if(device){
        device->closeDevice();
        device->run();
        device->drop();
    }
    m_time.start();
}


#include <QLabel>
extern QLabel * fpslabel;


void IrrlichtGraphicsScene::drawBackground(QPainter *painter, const QRectF &){
    if(!device){
        SIrrlichtCreationParameters createParams;
        createParams.DriverType = irr::video::EDT_OPENGL;
        createParams.IgnoreInput = true;
        createParams.WindowId = ( void * ) view->winId();
        device = createDeviceEx( createParams );
        if(!device){
            qFatal("failed to initialise irrlicht");
                return;
        }
        driver= device->getVideoDriver();
        scene= device->getSceneManager();
        initializeIrrlichtScene();
        if (painter->paintEngine()->type() != QPaintEngine::OpenGL) {
            qFatal("IrrlichtGraphicsScene: you need to set the QGraphicsView viewport to a QGlWidget");
            return;
        }
    }


    int cfps=1000/m_time.restart();
    if(fps!=cfps){
        fps=(fps+cfps)/2;
    }


    fpslabel->setText(QString::number(fps)+"fps");


    glEnable (GL_DEPTH_TEST);
    //    driver->beginScene(false,false);
    updateIrrlichtScene();
    scene->drawAll();

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
    glFinish();


    QTimer::singleShot(20, this, SLOT(update()));
}

void IrrlichtGraphicsScene::setSceneRect ( const QRectF & rect ){
    setSceneRect(rect.x(),rect.y(),rect.width(),rect.height());
}
void IrrlichtGraphicsScene::setSceneRect ( qreal x, qreal y, qreal w, qreal h ){
    if(device){
        irr::core::dimension2d<uint> size;
        size.Width = w;
        size.Height = h;
        device->getVideoDriver()->OnResize(size);
    }
    IrrlichtGraphicsScene::setSceneRect(x,y,w,h);
}



IrrlichtGraphicsView::IrrlichtGraphicsView(QWidget * parent)
 :QGraphicsView(parent){
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
     setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void IrrlichtGraphicsView::resizeEvent(QResizeEvent *event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
}




