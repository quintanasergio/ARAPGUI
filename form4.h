#ifndef FORM4_H
#define FORM4_H

#include <QWidget>

namespace Ui {
class Form4;
}

class Form4 : public QWidget
{
    Q_OBJECT

public:
    explicit Form4(QWidget *parent = 0);
    ~Form4();
    int getFrom();
    int getTo();
    double getValue();

signals:
    void outlist4(QString);

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::Form4 *ui;
};

#endif // FORM4_H
