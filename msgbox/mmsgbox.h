#ifndef MMSGBOX_H
#define MMSGBOX_H

#include <QDialog>
#include <QMouseEvent>

#define MMB_IMGFILE ":/msgbox/mmsgbox.png"  // 图片所在位置
#define MMB_QSSFILE ":/msgbox/mmsgbox.css"  // 样式所在位置

namespace Ui {
class MMsgBox;
}

class MMsgBox : public QDialog
{
    Q_OBJECT

public:

    enum MMsgBoxButton {
        MMsgBoxButtonNone = 0x00,   // 没有按钮
        MMsgBoxButtonCancel = 0x01, // 取消按钮
        MMsgBoxButtonAffirm = 0x02, // 确定按钮
        MMsgBoxButtonClose = 0x04,  // 关闭按钮
        // 所有按钮
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
        MMsgBoxTypeNone = 0x00,     // 没有提示图标
        MMsgBoxTypeCritical = 0x01, // 错误图标
        MMsgBoxTypeWarning = 0x02,  // 警告图标
        MMsgBoxTypeQuestion = 0x04, // 疑问图标
        MMsgBoxTypeAbout = MMsgBoxTypeNone  // 关于图标
    };

    /**
     * @brief MMsgBox - 提示窗口
     * @param parent: 父窗口
     * @param title: 标题
     * @param text: 内容
     * @param icon: 图标
     * @param type: 提示图标（内容前）
     * @param button：生成按钮
     *
     * icon默认大小是 32x32 其他大小利用 SetIcon() 设置
     */
    explicit MMsgBox(QWidget *parent = nullptr, QString title = "", QString text = "", QString icon = "",
                     MMsgBox::MMsgBoxType type = MMsgBox::MMsgBoxTypeNone,
                     MMsgBox::MMsgBoxButtons button = MMsgBox::MMsgBoxButtonAll);
    ~MMsgBox();

    /**
     * @brief SetIcon - 设置左上角图标
     * @param file: 图片文件所在位置
     * @param width: 设置图标宽度，设置实际大小而不是图标本身大小，下同
     * @param height: 设置图标高度
     */
    void SetIcon(QString file, int width = 32, int height = 32);

    /**
     * @brief SetTitle - 设置标题
     * @param title: 标题
     */
    void SetTitle(QString title = "提示");

    /**
     * @brief SetType - 设置窗口类型
     * @param type: 类型，参见 MMsgBox::MMsgBoxType
     *
     * 类型的表现为 “提示内容” 前面的图标
     */
    void SetType(MMsgBox::MMsgBoxType type = MMsgBox::MMsgBoxTypeNone);

    /**
     * @brief SetText - 设置提示内容
     * @param text: 提示内容
     */
    void SetText(QString text = "");

    /**
     * @brief SetButton - 需要显示的按键
     * @param button: 按键，参见 MMsgBox::MMsgBoxButtons
     */
    void SetButton(MMsgBox::MMsgBoxButtons button = MMsgBox::MMsgBoxButtonAll);

    /**
     * @brief SetKeyboard - 设置屏蔽键盘按键
     * @param keyboard: 按键
     *
     * 此函数未实现
     */
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
