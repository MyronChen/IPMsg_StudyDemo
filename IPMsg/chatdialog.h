#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "chatsession.h"
#include <boost/shared_ptr.hpp>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(const QString &peer, QWidget *parent = 0);
    ~ChatDialog();

private:
    Ui::ChatDialog *ui;
    boost::shared_ptr<ChatSession> _pSession;
};

#endif // CHATDIALOG_H
