#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* size){
        emit resetGeometry(0, 0, size->size().width(), size->size().height());
    }

signals:
    void resetGeometry(int x, int y, int w, int h);

private slots:
    void on_MBLineBtnShow_clicked();
    void on_WBLineBtnShow_clicked();

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
    Ui::MainWindow *ui;
    QPoint mousePoint;
    bool mousePressed;
};

#endif // MAINWINDOW_H
