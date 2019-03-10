#ifndef MWAITBOX_H
#define MWAITBOX_H

#include <QWidget>
#include <QTimer>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>

#define MWB_IMGFILE ":/waitbox/mwaitbox.png"
#define MWB_GIFFILE ":/waitbox/mwaitbox.gif"

namespace Ui {
class MWaitBox;
}

class MWaitBox : public QWidget
{
    Q_OBJECT

public:
    enum MWaitBoxType {
        MWaitBoxTypeWait = 0x01,
        MWaitBoxTypeAffirm = 0x02,
        MMsgBoxTypeCritical = 0x04,
        MMsgBoxTypeWarning = 0x08,
        MMsgBoxTypeQuestion = 0x10
    };

    explicit MWaitBox(QWidget *parent = nullptr, QString text = "", int timeout = 0,
                      MWaitBox::MWaitBoxType type = MWaitBox::MWaitBoxTypeWait);
    ~MWaitBox();

    void SetText(QString text = "");
    void SetType(MWaitBox::MWaitBoxType type = MWaitBox::MWaitBoxTypeWait);
    void SetTimeout(int sec = 0);

public slots:
    void onResize(int x, int y, int w, int h);

private slots:
    void onTimerTimeout();

private:
    void synctime(int sec);

private:
    Ui::MWaitBox *ui;
    QTimer *timer;
    QMovie *movie;
};

#endif // MWAITBOX_H
