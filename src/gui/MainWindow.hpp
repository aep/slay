#include "QIrrlichtWidget.hpp" 
#include "ui_MainWindow.h"
#include <Session.hpp>
#include <Chat.hpp>
#include <Avatar.hpp>
#include "InventoryModel.hpp"
#include <memory>

using namespace qtsl;

class MainWindow :public QMainWindow, private Ui::MainWindow{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = 0);

protected:
    qtsl::Session session;
    qtsl::Chat chat;
    qtsl::Avatar avatar;
    InventoryModel inventory;

protected slots:
    void on_login_submit_clicked(bool);
    void session_teleporting(Simulator *  target);
    void session_teleportComplete(Simulator *  target);
    void session_disconnected(Session::DisconnectReason reason);

    void on_chatsend_clicked(bool);
    void simulatorMessage(const qtsl::Chat::SimulatorMessage & m);
};
