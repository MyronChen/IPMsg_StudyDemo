#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "chatsession.h"
#include <boost/shared_ptr.hpp>
#include "mainwindow.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(const QString &peer, MainWindow *parent = 0);
    ~ChatDialog();

signals:
    void consumeMsg(QString);

private slots:
    void onSend();
    void onRecvMsg(QString);

private:
    void readMsg();

    QString formatMsg(const QString &peer, const QString &text) const;
private:
    QString _peer;
    Ui::ChatDialog *ui;
    boost::shared_ptr<ChatSession> _pSession;

};

#endif // CHATDIALOG_H
