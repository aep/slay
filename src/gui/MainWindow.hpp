#include "ui_MainWindow.h"
#include <Session.hpp>
#include <Avatar.hpp>
#include "InventoryDialog.hpp"
#include "ChatDialog.hpp"
#include "scene.hpp"
#include <memory>

using namespace qtsl;

class MainWindow :public QMainWindow, private Ui::MainWindow{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    qtsl::Session session;
    qtsl::Avatar avatar;
    InventoryDialog inventory;
    ChatDialog chat;
    Scene *scene;

protected slots:
    void on_login_submit_clicked(bool);
    void session_teleporting(Simulator *  target);
    void session_teleportComplete(Simulator *  target);
    void session_disconnected(Session::DisconnectReason reason);
};
