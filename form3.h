#ifndef FORM3_H
#define FORM3_H

#include <QWidget>

namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT

public:
    explicit Form3(QWidget *parent = 0);
    ~Form3();
    int getFrom();
    int getTo();
    int getIndex();
    float getUnimin();
    float getUnimax();
    float getConstant();
    float getTrimin();
    float getTrimax();
    float getTrimed();
    float getExpomed();
    float getExpolim();
    float getNormed();
    float getNorlim();
    float getNorvar();



signals:
    void outlist3(QString);
    void outlist5(QString);
    void outlist6(QString);
    void outlist7(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form3 *ui;
};

#endif // FORM3_H
