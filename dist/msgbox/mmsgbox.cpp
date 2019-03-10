#include "mmsgbox.h"
#include "ui_mmsgbox.h"

#include <QDebug>

MMsgBox::MMsgBox(QWidget *parent, QString title, QString text, QString icon,
                 MMsgBox::MMsgBoxType type, MMsgBox::MMsgBoxButtons button) :
    QDialog(parent),
    ui(new Ui::MMsgBox)
{
    ui->setupUi(this);

    ui->MMBIcon->clear();
    ui->MMBBtnAffirm->hide();
    ui->MMBBtnCancel->hide();
    ui->MMBBtnClose->hide();
    ui->MMBBtnClose->setText("");
    ui->MMBBtnClose->setIcon(QIcon(QPixmap(MMB_IMGFILE).copy(144, 0, 48, 48)));
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->SetTitle(title);
    this->SetText(text);
    this->SetIcon(icon);
    this->SetType(type);
    this->SetButton(button);

    QFile qssfile(MMB_QSSFILE);
    if (!qssfile.open(QIODevice::ReadOnly))
        return ;

    QString qssstr = qssfile.readAll();
    if (qssstr.isEmpty())
        return ;

    this->setStyleSheet(qssstr);
}

MMsgBox::~MMsgBox()
{
    delete ui;
}

void MMsgBox::SetTitle(QString title)
{
    if (title.isEmpty())
        ui->MMBTitle->setText("提示");
    else
        ui->MMBTitle->setText(title);
}

void MMsgBox::SetType(MMsgBox::MMsgBoxType type)
{
    QPixmap pix(MMB_IMGFILE);

    switch (type) {
    case MMsgBox::MMsgBoxTypeNone:
        ui->MMBBodyIcon->hide();
        break;

    case MMsgBox::MMsgBoxTypeCritical:
        ui->MMBBodyIcon->setPixmap(pix.copy(0, 0, 48, 48));
        break;

    case MMsgBox::MMsgBoxTypeWarning:
        ui->MMBBodyIcon->setPixmap(pix.copy(48, 0, 48, 48));
        break;

    case MMsgBox::MMsgBoxTypeQuestion:
        ui->MMBBodyIcon->setPixmap(pix.copy(96, 0, 48, 48));
        break;
    }
}

void MMsgBox::SetText(QString text)
{
    ui->MMBBodyText->setText(text);
}

void MMsgBox::SetButton(MMsgBox::MMsgBoxButtons button)
{
    if (button == MMsgBox::MMsgBoxButtonNone) {
        ui->MMBBtnAffirm->hide();
        ui->MMBBtnCancel->hide();
        ui->MMBBtnClose->hide();
    } else if (button == MMsgBox::MMsgBoxButtonAll) {
        ui->MMBBtnAffirm->show();
        ui->MMBBtnCancel->show();
        ui->MMBBtnClose->show();
    } else {
        if ((button & MMsgBox::MMsgBoxButtonAffirm) == MMsgBox::MMsgBoxButtonAffirm) {
            ui->MMBBtnAffirm->show();
        }

        if ((button & MMsgBox::MMsgBoxButtonCancel) == MMsgBox::MMsgBoxButtonCancel) {
            ui->MMBBtnCancel->show();
        }

        if ((button & MMsgBox::MMsgBoxButtonClose) == MMsgBox::MMsgBoxButtonClose) {
            ui->MMBBtnClose->show();
        }
    }
}

void MMsgBox::SetKeyboard(MMsgBox::MMsgBoxKeyboard keyboard)
{
    switch (keyboard) {
    case MMsgBox::MMsgBoxKeyboardNone:
        break;

    case MMsgBox::MMsgBoxKeyboardEsc:
        break;

    case MMsgBox::MMsgBoxKeyboardSpace:
        break;

    case MMsgBox::MMsgBoxKeyboardEnter1:
        break;

    case MMsgBox::MMsgBoxKeyboardEnter2:
        break;
    }
}

void MMsgBox::SetIcon(QString file, int width, int height)
{
    if (file.isEmpty()) {
        ui->MMBIcon->hide();
    } else {
        QPixmap pix(file);
        ui->MMBIcon->setPixmap(pix.scaled(QSize(width, height), Qt::KeepAspectRatio));
    }
}

void MMsgBox::on_MMBBtnClose_clicked()
{
    this->reject();
}

void MMsgBox::on_MMBBtnCancel_clicked()
{
    this->reject();
}

void MMsgBox::on_MMBBtnAffirm_clicked()
{
    this->accept();
}
