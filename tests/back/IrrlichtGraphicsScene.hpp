#ifndef QIRRLICHTSCENE_H
#define QIRRLICHTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <irrlicht.h>

class IrrlichtGraphicsView : public QGraphicsView {
public:
    IrrlichtGraphicsView(QWidget * parent=0);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    class GLWidget;
    friend class GlWidget;
    friend class IrrlichtGraphicsScene;
};


class IrrlichtGraphicsScene : public QGraphicsScene {
    Q_OBJECT;
public:

    IrrlichtGraphicsScene(IrrlichtGraphicsView * view);
    ~IrrlichtGraphicsScene();

    void setSceneRect ( const QRectF & rect );
    void setSceneRect ( qreal x, qreal y, qreal w, qreal h );

    irr::IrrlichtDevice         * device;
    irr::scene::ISceneManager   * scene;
    irr::video::IVideoDriver    * driver;


protected:

    virtual void drawBackground(QPainter *painter, const QRectF &);

    virtual void initializeIrrlichtScene()=0;
    virtual void updateIrrlichtScene()=0;
    void setDirty(){}

    IrrlichtGraphicsView * view;

private:

    QTime m_time;
    int fps;

    friend class IrrlichtGraphicsView::GLWidget;
};



#endif
