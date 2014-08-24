#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <user.h>
namespace Ui {
class MainWindow;
}

class AccountInfo;
class QTableWidgetItem;
//class User;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void login(int _loginType);
private slots:
    void on_actionLogin_triggered();

    void on_actionAdd_New_Account_triggered();

    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_editButton_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_objectNameChanged(const QString &objectName);

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_cellActivated(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_tableWidget_itemSelectionChanged();

    void on_tableWidget_itemEntered(QTableWidgetItem *item);

    void on_refresh_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    User user;

    int row;
    int col;

    QVector<AccountInfo> *accountList;
    void updateTable();
};

#endif // MAINWINDOW_H
