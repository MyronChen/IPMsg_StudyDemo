#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "ipmessage.h"
#include "util.h"
#include "chatmanager.h"

ChatDialog::ChatDialog(const QString &peer, MainWindow *parent) :
    QDialog(parent),
    _peer(peer),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    _pSession = ChatManagerInstance()->getChatSession(peer);
    new QListWidgetItem(peer, ui->_PeerList);

    readMsg();

    connect(ui->_SendBtn, SIGNAL(pressed()), SLOT(onSend()) );
    connect(parent, SIGNAL(recvMsg(QString)), SLOT(onRecvMsg(QString)) );

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

    QString log = formatMsg(IPMsgInstance()->getCurUser(), text);
    ui->_ChatBrowser->append(log);
}

void ChatDialog::onRecvMsg(QString sPeer)
{
    if (_peer != sPeer)
        return;
    readMsg();
}

void ChatDialog::readMsg()
{
    if (_pSession)
    {
        QString sPeer, sMsg;
        if (_pSession->deQueueUnreadMsg(sPeer, sMsg))
        {
            ui->_ChatBrowser->append(formatMsg(sPeer, sMsg));
            emit consumeMsg(sPeer);
        }
    }
}

QString ChatDialog::formatMsg(const QString &peer, const QString &text) const
{
    return QString(peer) + ":\n" + text + '\n';
}
