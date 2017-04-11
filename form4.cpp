#include "form4.h"
#include "ui_form4.h"

Form4::Form4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form4)
{
    ui->setupUi(this);
}

Form4::~Form4()
{
    delete ui;
}

void Form4::on_pushButton_4_clicked()
{
    this->deleteLater();

    QString nombre = objectName();

    emit outlist4(nombre);
}

int Form4::getFrom()
{
    int retval = 0;

    retval = ui->desde->value();

    return retval;
}

int Form4::getTo()
{
    int retval = 0;

    retval = ui->hasta->value();

    return retval;
}

double Form4::getValue()
{
    double retval = 0;

    retval = ui->valor->value();

    return retval;
}
