#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "ipmessage.h"
#include "util.h"
#include "chatmanager.h"

ChatDialog::ChatDialog(const QString &peer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    _pSession = ChatManagerInstance()->getChatSession(peer);
    new QListWidgetItem(peer, ui->_PeerList);

    connect(ui->_SendBtn, SIGNAL(pressed()), SLOT(onSend()) );
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::onSend()
{
    QString text = ui->_InputEditor->toPlainText();
    ui->_InputEditor->clear();

    if (!text.isEmpty())
        _pSession->sendText(text);

    QString log = IPMsgInstance()->getCurUser() + ":\n" + text + '\n';
    ui->_ChatBrowser->append(log);
}
