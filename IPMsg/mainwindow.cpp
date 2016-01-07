#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"
#include "ipmessage.h"
#include "chatdialog.h"
#include <QListWidgetItem>
#include <QTimer>
#include "chatmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateUserList();
    setupUserListTimer();

    connect( ui->_UserList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), SLOT(onItemDbClk(QListWidgetItem *)) );
    connect( ChatManagerInstance(), SIGNAL(recvMsg(QString)), SLOT(onRecvMsg(QString)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUserList()
{
    //SignalLocker locker(ui->_UserList);

    ui->_UserList->clear();
    QStringList asUser = IPMsgInstance()->getOnlineUsers();

    QStringListIterator iter(asUser);
    while (iter.hasNext())
    {
        QString sName = iter.next();
        QListWidgetItem *item = new QListWidgetItem(sName, ui->_UserList);
        item->setTextColor(Qt::red);
    }
}

void MainWindow::onItemDbClk(QListWidgetItem *item)
{
    QString sPeerUser = item->text();

    ChatDialog *pDlg = new ChatDialog(sPeerUser, this);

    connect(pDlg, SIGNAL(consumeMsg(QString)), this, SLOT(onConsumeMsg(QString)) );

    pDlg->show();

    onConsumeMsg(sPeerUser);
}

void MainWindow::onRecvMsg(QString sPeer)
{
    QList<QListWidgetItem*> aItem = ui->_UserList->findItems(sPeer, Qt::MatchExactly);
    if (aItem.size() == 1)
    {
        //aItem[0]->setText("dd");
        aItem[0]->setTextColor(Qt::red);
        aItem[0]->setBackgroundColor(Qt::red);
        ui->_UserList->update();
        emit recvMsg(sPeer);
    }
}

void MainWindow::onConsumeMsg(QString sPeer)
{
    QList<QListWidgetItem*> aItem = ui->_UserList->findItems(sPeer, Qt::MatchExactly);
    if (aItem.size() == 1)
    {
        aItem[0]->setTextColor(Qt::black);
    }
}

void MainWindow::setupUserListTimer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUserList()));
    timer->start(1000 * 10);
}


