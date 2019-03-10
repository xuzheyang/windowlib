#ifndef MMSGBOX_H
#define MMSGBOX_H

#include <QDialog>
#include <QMouseEvent>

#define MMB_IMGFILE ":/msgbox/mmsgbox.png"
#define MMB_QSSFILE ":/msgbox/mmsgbox.css"

namespace Ui {
class MMsgBox;
}

class MMsgBox : public QDialog
{
    Q_OBJECT

public:

    enum MMsgBoxButton {
        MMsgBoxButtonNone = 0x00,
        MMsgBoxButtonCancel = 0x01,
        MMsgBoxButtonAffirm = 0x02,
        MMsgBoxButtonClose = 0x04,
        MMsgBoxButtonAll = (MMsgBoxButtonCancel | MMsgBoxButtonAffirm | MMsgBoxButtonClose)
    };
    Q_DECLARE_FLAGS(MMsgBoxButtons, MMsgBoxButton)

    enum MMsgBoxKeyboard {
        MMsgBoxKeyboardNone = 0x00,
        MMsgBoxKeyboardEsc = 0x01,
        MMsgBoxKeyboardSpace = 0x02,
        MMsgBoxKeyboardEnter1 = 0x04,   // Enter 按键
        MMsgBoxKeyboardEnter2 = 0x08    // 小键盘 Enter 按键
    };

    enum MMsgBoxType {
        MMsgBoxTypeNone = 0x00,
        MMsgBoxTypeCritical = 0x01,
        MMsgBoxTypeWarning = 0x02,
        MMsgBoxTypeQuestion = 0x04,
        MMsgBoxTypeAbout = MMsgBoxTypeNone
    };

    explicit MMsgBox(QWidget *parent = nullptr, QString title = "", QString text = "", QString icon = "",
                     MMsgBox::MMsgBoxType type = MMsgBox::MMsgBoxTypeNone,
                     MMsgBox::MMsgBoxButtons button = MMsgBox::MMsgBoxButtonAll);
    ~MMsgBox();

    void SetIcon(QString file, int width = 32, int height = 32);
    void SetTitle(QString title = "提示");
    void SetType(MMsgBox::MMsgBoxType type = MMsgBox::MMsgBoxTypeNone);
    void SetText(QString text = "");
    void SetButton(MMsgBox::MMsgBoxButtons button = MMsgBox::MMsgBoxButtonAll);
    void SetKeyboard(MMsgBox::MMsgBoxKeyboard keyboard = MMsgBox::MMsgBoxKeyboardNone);

private slots:
    void on_MMBBtnClose_clicked();
    void on_MMBBtnCancel_clicked();
    void on_MMBBtnAffirm_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *e)
    {
        if (mousePressed && (e->buttons() && Qt::LeftButton)) {
            this->move(e->globalPos() - mousePoint);
            e->accept();
        }
    }
    void mousePressEvent(QMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = e->globalPos() - this->pos();
            e->accept();
        }
    }
    void mouseReleaseEvent(QMouseEvent *)
    {
        mousePressed = false;
    }

private:
    void loadStyle(QString file);

private:
    Ui::MMsgBox *ui;
    QPoint mousePoint;
    bool mousePressed;
};

#endif // MMSGBOX_H
