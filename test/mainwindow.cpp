#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mmsgbox.h"
#include "mwaitbox.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/test/mainwindows.css");
    file.open(QIODevice::ReadOnly);
    this->setStyleSheet(file.readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MBLineBtnShow_clicked()
{
    QString title = ui->MBLineEditTitle->text();
    QString text = ui->MBLineEditText->text();

    MMsgBox::MMsgBoxType type = MMsgBox::MMsgBoxTypeNone;
    int itype = ui->MBComboBoxType->currentIndex();
    switch (itype) {
        case 0: type = MMsgBox::MMsgBoxTypeNone; break;
        case 1: type = MMsgBox::MMsgBoxTypeCritical; break;
        case 2: type = MMsgBox::MMsgBoxTypeQuestion; break;
        case 3: type = MMsgBox::MMsgBoxTypeWarning; break;
    }

    MMsgBox::MMsgBoxButtons button = MMsgBox::MMsgBoxButtonNone;
    if (ui->MBCheckBoxBtnCancel->isChecked()) {
        button = (button | MMsgBox::MMsgBoxButtonCancel);
    }

    if (ui->MBCheckBoxBtnAffirm->isChecked()) {
        button = (button | MMsgBox::MMsgBoxButtonAffirm);
    }

    if (ui->MBCheckBoxBtnClose->isChecked()) {
        button = (button | MMsgBox::MMsgBoxButtonClose);
    }

    MMsgBox *box = new MMsgBox(nullptr, title, text, ":/other/ico.icns", type, button);
    box->exec();
}

void MainWindow::on_WBLineBtnShow_clicked()
{
    MWaitBox::MWaitBoxType type;
    int itype = ui->WBComboBoxType->currentIndex();
    switch (itype) {
    case 0: type = MWaitBox::MWaitBoxTypeWait; break;
    case 1: type = MWaitBox::MWaitBoxTypeAffirm; break;
    case 2: type = MWaitBox::MMsgBoxTypeCritical; break;
    case 3: type = MWaitBox::MMsgBoxTypeWarning; break;
    case 4: type = MWaitBox::MMsgBoxTypeQuestion; break;
    }

    QString text = ui->WBLineEditText->text();

    MWaitBox *box = new MWaitBox(this, text, 2, type);
//    connect(this, SIGNAL(resetGeometry(int, int, int, int)), box, SLOT(onResize(int, int, int, int)));
    box->show();
}
