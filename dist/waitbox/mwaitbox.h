#ifndef MWAITBOX_H
#define MWAITBOX_H

#include <QTimer>
#include <QMovie>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>

#define MWB_IMGFILE ":/dist/waitbox/mwaitbox.png"
#define MWB_GIFFILE ":/dist/waitbox/mwaitbox.gif"

namespace Ui {
class MWaitBox;
}

class MWaitBox : public QWidget
{
    Q_OBJECT

public:
    enum MWaitBoxType {
        MWaitBoxTypeWait = 0x01,    // 等待
        MWaitBoxTypeAffirm = 0x02,  // 成功
        MMsgBoxTypeCritical = 0x04, // 错误
        MMsgBoxTypeWarning = 0x08,  // 警告
        MMsgBoxTypeQuestion = 0x10  // 疑问
    };

    /**
     * @brief GetInstance - 获取单实例
     * @param parent: 父类
     * @return 返回单实例
     */
    static MWaitBox *GetInstance(QWidget *parent = nullptr);


    /**
     * @brief Show - 显示窗口
     * @param text: 显示的内容
     * @param timeout: 窗口显示的时间, 单位秒, 默认不关闭
     * @param type: 窗口的类型, 默认为等待窗口
     */
    void Show(QString text = "", int timeout = 0, MWaitBox::MWaitBoxType type = MWaitBox::MWaitBoxTypeWait);

    /**
     * @brief Hide - 隐藏窗口
     */
    void Hide();

    /**
     * @brief SetText - 设置提示信息
     * @param text: 提示信息
     */
    void SetText(QString text = "");

    /**
     * @brief SetType - 设置提示类型
     * @param type: 提示类型，参见 MWaitBox::MWaitBoxType
     */
    void SetType(MWaitBox::MWaitBoxType type = MWaitBox::MWaitBoxTypeWait);

    /**
     * @brief SetTimeout - 设置超时关闭时间
     * @param sec: 关闭时间，单位为秒
     */
    void SetTimeout(int sec = 0);

public slots:
    void onResize(int x, int y, int w, int h);

private slots:
    void onTimerTimeout();

private:
    /**
     * @brief MWaitBox - 等待窗口
     * @param parent: 父窗口类型
     * @param text: 提示信息
     * @param timeout: 自动关闭时间，单位为秒，默认不关闭
     * @param type: 类型，参见 MWaitBox::MWaitBoxType
     *
     * 类型的表示方式也是图标
     */
    explicit MWaitBox(QWidget *parent = nullptr, QString text = "", int timeout = 0,
                      MWaitBox::MWaitBoxType type = MWaitBox::MWaitBoxTypeWait);
    ~MWaitBox();

    /**
     * @brief synctime - 同步定时器时间
     * @param sec: 定时时间，单位为秒
     */
    void synctime(int sec);

private:
    Ui::MWaitBox *ui;
    MWaitBox *_this;
    QTimer *timer;
    QMovie *movie;
};

#endif // MWAITBOX_H
