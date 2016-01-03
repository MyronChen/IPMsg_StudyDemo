#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"
#include "ipmessage.h"
#include "chatdialog.h"
#include <QListWidgetItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateUserList();
    setupUserListTimer();

    connect( ui->_UserList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), SLOT(onItemDbClk(QListWidgetItem *)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUserList()
{
    SignalLocker locker(ui->_UserList);

    ui->_UserList->clear();
    QStringList asUser = IPMsgInstance()->getOnlineUsers();

    QStringListIterator iter(asUser);
    while (iter.hasNext())
    {
        QString sName = iter.next();
        new QListWidgetItem(sName, ui->_UserList);
    }
}

void MainWindow::onItemDbClk(QListWidgetItem *item)
{
    QString sPeerUser = item->text();

    ChatDialog *pDlg = new ChatDialog(sPeerUser, this);
    pDlg->show();
}

void MainWindow::setupUserListTimer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUserList()));
    timer->start(1000 * 10);
}


