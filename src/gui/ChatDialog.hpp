#ifndef CHAT_DIALOG
#define CHAT_DIALOG

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <Chat.hpp>

class ChatDialog : public QDialog{
    Q_OBJECT;
public:
    ChatDialog(qtsl::Session&);
    ~ChatDialog();
private:
    QGridLayout layout;
    QLineEdit input;
    QPushButton send;
    QTextEdit log;
    qtsl::Chat chat;
private slots:
    void chatsend_clicked(bool);
    void simulatorMessage(const qtsl::Chat::SimulatorMessage & m);

};

#endif
