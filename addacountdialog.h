#ifndef ADDACOUNTDIALOG_H
#define ADDACOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class AddAcountDialog;
}

class AddAcountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAcountDialog(int _type,QWidget *parent = 0);
    ~AddAcountDialog();

    QString getUserName();

    QString getPassword();

    bool isAccepted();
    void changeType(int _type);
private slots:
    void accept();
    void reject();

    void on_login_clicked();

    void on_cancel_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::AddAcountDialog *ui;

    bool accepted;
    int type;
};

#endif // ADDACOUNTDIALOG_H
