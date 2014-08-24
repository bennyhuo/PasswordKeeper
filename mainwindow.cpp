#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "addacountdialog.h"
#include "QDebug"
#include <QMessageBox>
#include "accountinfo.h"
#include <datamanager.h>
#include <QStandardItem>
#include <utils.h>
#include <QPixmap>
#include <aboutdialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),accountList(0)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QStringList headList;
    headList << "Username" << "Password" << "WebsiteName";
    ui->tableWidget->setHorizontalHeaderLabels(headList);

    login(0);
    //    QPixmap pixmap = QPixmap("mainbackground.png").scaled(this->size());
    //    QPalette palette(this->palette());
    //    palette.setBrush(QPalette::Background, QBrush(QColor(60,90,150)));
    //    this->setPalette(palette);

    //    QPalette pll = ui->tableWidget->palette();
    //    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    //    ui->tableWidget->setPalette(pll);

    //    ui->tableWidget->horizontalHeader()->setStyleSheet(
    //                "QHeaderView::section{border:2px groove gray;border-radius:0px;padding:2px 4px;background-color: rgb(230,220, 255)}");
    //    ui->tableWidget->verticalHeader()->setStyleSheet(
    //                "QHeaderView::section{border:2px groove gray;border-radius:0px;padding:2px 4px;background-color: rgb(230, 220, 255)}");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete accountList;
}

void MainWindow::login(int _loginType)
{
    AddAcountDialog dialog(_loginType);

    dialog.exec();

    if(dialog.isAccepted()){
        QString username = dialog.getUserName();
        user = DataManager::getInstance().getUserByName(username);
        user.password = dialog.getPassword();

        ui->welcome->setText("Hello, "+username);
        //trigger a method..show all the password
        updateTable();

        ui->addButton->setEnabled(true);
        ui->refresh->setEnabled(true);
        ui->delButton->setEnabled(true);
        ui->editButton->setEnabled(true);
    }
}

void MainWindow::on_actionLogin_triggered()
{
    login(2);
}

void MainWindow::updateTable()
{
    static bool isRecursive = false;
    if(isRecursive==false){
        isRecursive = true;
        if(accountList!=0){
            delete accountList;
        }

        accountList = DataManager::getInstance().getDataList(user.id,user.password);

        //fill the table..
        ui->tableWidget->setRowCount(accountList->size());
        for(int i = 0; i < accountList->size();i++){
            AccountInfo account = accountList->value(i);

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(account.username));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(account.password));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(account.websitename));
        }
        ui->tableWidget->show();
        ui->tableWidget->resizeColumnsToContents();

        isRecursive = false;
    }
}

void MainWindow::on_actionAdd_New_Account_triggered()
{
    AddAcountDialog dialog(3);

    dialog.exec();

    if(dialog.isAccepted()){
        QString username = dialog.getUserName();
        user = DataManager::getInstance().getUserByName(username);
        ui->welcome->setText("Hello, "+username);
        //trigger a method..show all the password
        updateTable();
    }
}

void MainWindow::on_addButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void MainWindow::on_delButton_clicked()
{
    QMessageBox::StandardButton bid = QMessageBox::warning(this,"Delete","Do you want to delete this?",QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
    if(bid == QMessageBox::Yes){
        int row  = ui->tableWidget->currentRow();
        int id = accountList->at(row).id;
        DataManager::getInstance().delAccountById(id);
        updateTable();
    }
}

void MainWindow::on_editButton_clicked()
{
    ui->tableWidget->edit(ui->tableWidget->currentIndex());
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    qDebug(" tableWidget clicked:%d,%d", index.row(), index.column());
}

void MainWindow::on_tableWidget_objectNameChanged(const QString &objectName)
{
    qDebug() << "on_tableWidget_objectNameChanged :" << objectName;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    static bool isRecursive = false;
    if(isRecursive==false){
        isRecursive = true;
        qDebug(" on_tableWidget_cellChanged:%d,%d", row, column);
        qDebug() << "text:" << ui->tableWidget->item(row,column)->text();

        if(user.id!=-1){
            AccountInfo account;
            account.userid = user.id;
            if(row < accountList->size()){
                account = accountList->at(row);
            }else{

            }
            account.changeAccount(column,ui->tableWidget->item(row,column)->text());
            DataManager::getInstance().modifyAccount(account,user.password);
            updateTable();
            isRecursive = false;
        }
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    qDebug(" on_tableWidget_cellClicked:%d,%d", row, column);
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    qDebug(" on_tableWidget_itemClicked:%d,%d", item->row(), item->column());
}

void MainWindow::on_tableWidget_cellActivated(int , int )
{
    qDebug("on_tableWidget_cellActivated");
}

void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    qDebug("on_tableWidget_cellDoubleClicked");
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    qDebug() << "on_tableWidget_itemSelectionChanged";
}

void MainWindow::on_tableWidget_itemEntered(QTableWidgetItem *item)
{
    qDebug() << "on_tableWidget_itemEntered" << item->column() << ";" << item->row();
}

void MainWindow::on_refresh_clicked()
{
    updateTable();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}
