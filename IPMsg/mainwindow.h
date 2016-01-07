#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void recvMsg(QString);

private slots:
    void updateUserList();
    void onItemDbClk(QListWidgetItem *);
    void onRecvMsg(QString);
    void onConsumeMsg(QString);

private:
    void setupUserListTimer();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
