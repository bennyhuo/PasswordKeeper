#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtSql>
#include "QSqlDatabase"
#include <QSqlError>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
