#include "addacountdialog.h"
#include "ui_addacountdialog.h"
#include "datamanager.h"
#include "QMessageBox"
#include <QCryptographicHash>
#include <QDebug>

void AddAcountDialog::changeType(int _type)
{
    type = _type;
    switch(type){
    case 2:
        ui->commandLinkButton->setVisible(false);
    case 0:
        ui->login->setText("Login");
        ui->title->setText("Login");
        ui->commandLinkButton->setText("Create a User..");
        break;
    case 3:
        ui->commandLinkButton->setVisible(false);
    case 1:
        ui->login->setText("OK");
        ui->title->setText("Create a User");
        ui->commandLinkButton->setText("Back to Login..");
        break;
    default :
        break;
    }
}

AddAcountDialog::AddAcountDialog(int _type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAcountDialog)
{
    ui->setupUi(this);
    ui->hint->setVisible(false);

    changeType(_type);
}

AddAcountDialog::~AddAcountDialog()
{
    delete ui;
}

QString AddAcountDialog::getUserName(){
    return ui->uname->text();
}

QString AddAcountDialog::getPassword(){
    return ui->upass->text();
}

void AddAcountDialog::accept(){
    accepted = true;
    QDialog::accept();
}

void AddAcountDialog::reject(){
    accepted = false;
    QDialog::reject();
}

bool AddAcountDialog::isAccepted(){
    return accepted;
}

void AddAcountDialog::on_login_clicked()
{
    QString uname = getUserName();
    QString password = getPassword();
    if(uname==""||password==""){
        ui->hint->setText("Username or password cannot be empty.");
        ui->hint->setVisible(true);
    }else{
        QString md5password;
        QByteArray ba,bb;
        QCryptographicHash md(QCryptographicHash::Md5);
        ba.append(password);
        md.addData(ba);
        bb = md.result();
        md5password.append(bb.toHex());
        qDebug() << md5password;

        if(type%2==0){
            if(DataManager::getInstance().login(uname,md5password)){
                accepted = true;
                QDialog::accept();
            }else{
                accepted = false;
                ui->hint->setText("Username or password error.");
                ui->hint->setVisible(true);
            }
        }else{
            if(DataManager::getInstance().createUser(uname,md5password)){
                QDialog::accept();
            }else{
                ui->hint->setText("Username is existed.");
                ui->hint->setVisible(true);
            }
        }
    }
}

void AddAcountDialog::on_cancel_clicked()
{
    accepted = false;
    QDialog::reject();
}

void AddAcountDialog::on_commandLinkButton_clicked()
{
    if(type==0){
        changeType(1);
    }else if(type==1){
        changeType(0);
    }
}
