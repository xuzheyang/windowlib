#include "mwaitbox.h"
#include "ui_mwaitbox.h"

MWaitBox *MWaitBox::GetInstance(QWidget *parent) {
    static MWaitBox *_this = nullptr;
    if (!_this) {
        _this = new MWaitBox(parent);
    }
    return _this;
}

void MWaitBox::Show(QString text, int timeout, MWaitBox::MWaitBoxType type)
{
    this->SetText(text);
    this->SetTimeout(timeout);
    this->SetType(type);
    this->show();
}

void MWaitBox::Hide()
{
    this->hide();
}

MWaitBox::MWaitBox(QWidget *parent, QString text, int timeout,
                   MWaitBox::MWaitBoxType type) :
    QWidget(parent),
    ui(new Ui::MWaitBox),
    timer(nullptr),
    movie(nullptr)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->hide();

    onResize(0, 0, parent->width(), parent->height());

    this->setWindowOpacity(0.9);
    this->setStyleSheet("background:transparent;");
//    ui->MWBBody->setStyleSheet("background: transparent;");
    ui->MWBBody->setWindowOpacity(0.9);
    ui->MWBIcon->setStyleSheet("background:transparent;");
    ui->MWBText->setStyleSheet("color: white; background: transparent;");
    ui->MWBBackground->setStyleSheet("background: rgba(58, 58, 58, 0.5); border-radius:10px;");

    this->SetText(text);
    this->SetTimeout(timeout);
    this->SetType(type);
}

MWaitBox::~MWaitBox()
{
    if (timer)
        delete timer;

    if (movie)
        delete movie;

    delete ui;
}

void MWaitBox::SetText(QString text)
{
    if (text.isEmpty()) {
        ui->MWBText->hide();
    } else {
        ui->MWBText->show();
        ui->MWBText->setText(text);
    }
}

void MWaitBox::SetType(MWaitBox::MWaitBoxType type)
{
    QPixmap pix(MWB_IMGFILE);
    switch (type) {
    case MWaitBox::MWaitBoxTypeWait:
        movie = new QMovie(MWB_GIFFILE);
        ui->MWBIcon->setScaledContents(true);
        ui->MWBIcon->setMovie(movie);
        movie->start();
        break;

    case MWaitBox::MWaitBoxTypeAffirm:
        ui->MWBIcon->setPixmap(pix.copy(0, 0, 128, 128));
        break;

    case MWaitBox::MMsgBoxTypeCritical:
        ui->MWBIcon->setPixmap(pix.copy(128, 0, 128, 128));
        break;

    case MWaitBox::MMsgBoxTypeWarning:
        ui->MWBIcon->setPixmap(pix.copy(256, 0, 128, 128));
        break;

    case MWaitBox::MMsgBoxTypeQuestion:
        ui->MWBIcon->setPixmap(pix.copy(384, 0, 128, 128));
        break;
    }
}

void MWaitBox::SetTimeout(int sec)
{
    if (sec)
        synctime(sec * 1000);
    else
        timer->stop();
}

void MWaitBox::onResize(int x, int y, int w, int h)
{
    this->setGeometry(x, y, w, h);
}

void MWaitBox::onTimerTimeout()
{
    this->close();
}

void MWaitBox::synctime(int sec)
{
    timer->stop();
    timer->start(sec);
}
