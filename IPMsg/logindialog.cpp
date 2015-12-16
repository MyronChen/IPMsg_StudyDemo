#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->_ButtonBox, SIGNAL(accepted()), SLOT(onAccept()));
    connect(ui->_RegisterBtn, SIGNAL(clicked()), SLOT(onRegister()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getName() const
{
    return ui->_NameEditor->text();
}

void LoginDialog::onAccept()
{
    if  (!ui->_NameEditor->text().isEmpty())
    {
        accept();
    }
}

void LoginDialog::onRegister()
{
    QString sAddr = ui->_AddrEditor->text();
    if (sAddr.isEmpty())
        return;

    RegisterDialog zRegisterDlg(sAddr, this);
    if (zRegisterDlg.exec() == QDialog::Accepted)
    {
        ui->_NameEditor->setText(zRegisterDlg.getName());
    }
}
