#include "ChatDialog.hpp"

ChatDialog::ChatDialog(qtsl::Session& session)
    :QDialog()
    ,layout(this)
    ,send("Send")
    ,chat(session){
    layout.addWidget(&log,1,1,1,2);
    layout.addWidget(&input,2,1,1,1);
    layout.addWidget(&send,2,2,1,1);

    setWindowTitle("Chat");
    layout.setContentsMargins ( 0,0,0,0);
    setWindowOpacity(0.8);
    resize(200,60);

    log.setReadOnly(true);

    connect(&chat,SIGNAL(simulatorMessage(const qtsl::Chat::SimulatorMessage & )),
            this,SLOT   (simulatorMessage(const qtsl::Chat::SimulatorMessage &)));

    connect(&input,SIGNAL(returnPressed ()),&send,SLOT(click()));
    connect(&send,SIGNAL(clicked(bool)),this,SLOT(chatsend_clicked(bool)));

}
ChatDialog::~ChatDialog(){
}


void ChatDialog::chatsend_clicked(bool){
    chat.sendSimulatorMessage(input.text(),qtsl::Chat::SimulatorMessage::NormalVolume);
    input.clear();
}

void ChatDialog::simulatorMessage(const qtsl::Chat::SimulatorMessage & m){
    if(m.chatType==qtsl::Chat::SimulatorMessage::WhisperVolume){
        log.append(m.fromName + " whispers: "+m.message);
    }else if(m.chatType==qtsl::Chat::SimulatorMessage::ShoutVolume){
        log.append(m.fromName + " shouts: "+m.message);
    }else if(m.chatType==qtsl::Chat::SimulatorMessage::NormalVolume){
        log.append(m.fromName + ": "+m.message);
    }
    log.moveCursor ( QTextCursor::End );
    log.ensureCursorVisible();
}

