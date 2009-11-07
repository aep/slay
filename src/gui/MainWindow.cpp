#include "MainWindow.hpp"
#include <QDebug>
#include "InventoryDialog.hpp"
#include <QGraphicsProxyWidget>

MainWindow::MainWindow(QWidget * parent)
  : QMainWindow(parent)
  ,chat(session)
  ,avatar(session)
  ,inventory(session)
{
	setupUi(this);
	setStatusBar(0);

    scene=new Scene(view);
    view->setScene(scene);

    connect(&session,SIGNAL(teleporting(Simulator * )),this,SLOT(session_teleporting(Simulator * )));
    connect(&session,SIGNAL(teleportComplete(Simulator * )),this,SLOT(session_teleportComplete(Simulator * )));
    connect(&session,SIGNAL(disconnected(Session::DisconnectReason)),this,SLOT(session_disconnected(Session::DisconnectReason)));

    QGraphicsProxyWidget * d = scene->addWidget(&inventory);
    d->setFlag(QGraphicsItem::ItemIsMovable);
    d->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    d = scene->addWidget(&chat);
    d->setFlag(QGraphicsItem::ItemIsMovable);
    d->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

}

MainWindow::~MainWindow(){
    delete view;
}

void MainWindow::on_login_submit_clicked(bool){
    session.login(QUrl("http://osgrid.org:8002"),login_first->text(),login_last->text(),login_pass->text());
    loginPageStack->setCurrentIndex(0);
}

void MainWindow::session_teleporting(Simulator *  target){
    mainStack->setCurrentIndex(1);
    loginPageStack->setCurrentIndex(0);
}

void MainWindow::session_teleportComplete(Simulator *  target){
    mainStack->setCurrentIndex(0);
}

void MainWindow::session_disconnected(Session::DisconnectReason reason){
    loginPageStack->setCurrentIndex(1);
    mainStack->setCurrentIndex(1);
}
