#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        LoginDialog zLoginDlg;
        if (zLoginDlg.exec() != QDialog::Accepted)
            return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
