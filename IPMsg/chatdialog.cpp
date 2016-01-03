#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "util.h"

ChatDialog::ChatDialog(const QString &peer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    _pSession = boost::make_shared<ChatSession>(peer);
    new QListWidgetItem(peer, ui->_PeerList);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
