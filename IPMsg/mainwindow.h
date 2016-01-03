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

private slots:
    void updateUserList();
    void onItemDbClk(QListWidgetItem *);

private:
    void setupUserListTimer();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
