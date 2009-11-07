#include <QApplication>
#include <QGLWidget>
#include "scene.hpp"

#include <QLabel>
#include <QGraphicsItem>
#include <QDialog>
#include <QGridLayout>
#include <QTreeView>
#include <QDirModel>
#include <QGraphicsProxyWidget>

class DirDialog : public QDialog{
public:
    DirDialog()
        :QDialog()
        ,layout(this){
        layout.addWidget(&view,1,1,1,1);
        layout.setContentsMargins ( 0,0,0,0);
        view.setModel(&model);
        setWindowOpacity(0.8);
        view.setFrameStyle(QFrame::NoFrame);
    }
    QGridLayout layout;
    QTreeView view;
    QDirModel model;
};



QLabel * fpslabel;

int main(int argc, char **argv){
    QApplication    app(argc, argv);

    fpslabel=new QLabel();
    fpslabel->show();


    QGraphicsScene scene;
    Scene view;
    view.setScene(&scene);

	scene.addWidget(new DirDialog());
    //	scene.addWidget(fpslabel)->resize(100,20);;

    foreach (QGraphicsItem *item, scene.items()) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    }

    view.show();
    return app.exec();
}
