#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(const QString &sAddr, QWidget *parent = 0);
    ~RegisterDialog();

    QString getName() const;

private slots:
    void onAccept();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
