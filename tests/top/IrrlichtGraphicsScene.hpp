#ifndef QIRRLICHTSCENE_H
#define QIRRLICHTSCENE_H

#include <QGLWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTime>
#include <irrlicht.h>



class IrrlichtGraphicsView : public QGLWidget {
    Q_OBJECT;
public:

    IrrlichtGraphicsView();
    ~IrrlichtGraphicsView();

    irr::IrrlichtDevice         * device;
    irr::scene::ISceneManager   * scene;
    irr::video::IVideoDriver    * driver;


    void setScene ( QGraphicsScene * scene );

protected:

    virtual void resizeGL ( int width, int height );
    virtual void paintGL ();
    virtual void initializeGL ();

    virtual void initializeIrrlichtScene()=0;
    virtual void updateIrrlichtScene()=0;

    void setDirty(){}

    QGLWidget * view;
    QGraphicsScene * qgs;
    QGraphicsView * qgv;

private:



    QTime m_time;
    int fps;
};



#endif
