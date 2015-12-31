#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "ipmessage.h"

RegisterDialog::RegisterDialog(const QString &sAddr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->_AddrEditor->setText(sAddr);

    connect(ui->_ButtonBox, SIGNAL(accepted()), SLOT(onAccept()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

QString RegisterDialog::getName() const
{
    return ui->_NameEditor->text();
}

void RegisterDialog::onAccept()
{
    QString sName = ui->_NameEditor->text();
    QString sPwd = ui->_PwdEditor->text();
    QString sAddr = ui->_AddrEditor->text();
    if (IPMsgInstance()->registerUser(sName, sPwd, sAddr))
        accept();
}
