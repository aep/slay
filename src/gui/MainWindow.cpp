#include "MainWindow.hpp"
#include <QDebug>


MainWindow::MainWindow(QWidget * parent)
  : QMainWindow(parent)
  ,chat(session)
  ,avatar(session)
  ,inventory(session){
	setupUi(this);
	setStatusBar(0);

    inventoryDock->hide();
    chatDock->hide();
    inventoryView->setModel(&inventory);

    connect(&session,SIGNAL(teleporting(Simulator * )),this,SLOT(session_teleporting(Simulator * )));
    connect(&session,SIGNAL(teleportComplete(Simulator * )),this,SLOT(session_teleportComplete(Simulator * )));
    connect(&session,SIGNAL(disconnected(Session::DisconnectReason)),this,SLOT(session_disconnected(Session::DisconnectReason)));

    connect(&chat,SIGNAL(simulatorMessage(const qtsl::Chat::SimulatorMessage & )),
            this,SLOT   (simulatorMessage(const qtsl::Chat::SimulatorMessage &)));

}

void MainWindow::on_login_submit_clicked(bool){
    session.login(QUrl("http://baal.ibcsolutions.de:9000"),login_first->text(),login_last->text(),login_pass->text());
    loginPageStack->setCurrentIndex(0);
}

void MainWindow::session_teleporting(Simulator *  target){
    inventoryDock->hide();
    chatDock->hide();
    mainStack->setCurrentIndex(1);
    loginPageStack->setCurrentIndex(0);
}

void MainWindow::session_teleportComplete(Simulator *  target){
    mainStack->setCurrentIndex(0);
    inventoryDock->show();
    chatDock->show();
}

void MainWindow::session_disconnected(Session::DisconnectReason reason){
    inventoryDock->hide();
    chatDock->hide();
    loginPageStack->setCurrentIndex(1);
    mainStack->setCurrentIndex(1);
}

void MainWindow::on_chatsend_clicked(bool){
    chat.sendSimulatorMessage(chatline->text(),qtsl::Chat::SimulatorMessage::NormalVolume);
    chatline->clear();
}

void MainWindow::simulatorMessage(const qtsl::Chat::SimulatorMessage & m){
    if(m.chatType==qtsl::Chat::SimulatorMessage::WhisperVolume){
        chatlog->append(m.fromName + " whispers: "+m.message);
    }else if(m.chatType==qtsl::Chat::SimulatorMessage::ShoutVolume){
        chatlog->append(m.fromName + " shouts: "+m.message);
    }else {
        chatlog->append(m.fromName + ": "+m.message);
    }
    chatlog->moveCursor ( QTextCursor::End );
    chatlog->ensureCursorVisible();
}

