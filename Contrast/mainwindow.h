#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalScrollBar_valueChanged(int value);
    void on_horizontalScrollBar_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    unsigned char    *imgChar=NULL;
    QImage             *image=NULL;
    QGraphicsPixmapItem *item=NULL;
    QGraphicsScene     *scene=NULL;
};

#endif // MAINWINDOW_H
