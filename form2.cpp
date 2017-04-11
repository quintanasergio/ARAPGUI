#include "form2.h"
#include "ui_form2.h"

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
}

Form2::~Form2()
{
    delete ui;
}

void Form2::on_pushButton_clicked()
{
    this->deleteLater();

    QString nombre = objectName();

    emit outlist2(nombre);
}

int Form2::getFrom()
{
    int retval = 0;

    retval = ui->desde->value();

    return retval;
}

int Form2::getTo()
{
    int retval = 0;

    retval = ui->hasta->value();

    return retval;
}

double Form2::getValue()
{
    double retval = 0;

    retval = ui->valor->value();

    return retval;
}
