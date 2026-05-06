#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QSlider>
#include <QAbstractSlider>
#include "qcustomplot.h"

#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private:
    Ui::SecDialog *ui;
    void setupQuadraticDemo(QCustomPlot *customPlot);
    QCustomPlot *customPlot;

};

#endif // SECDIALOG_H
