#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    this->deleteLater();

    QString nombre = objectName();

    emit outlist(nombre);
}

int Form::getFrom()
{
    int retval = 0;

    retval = ui->desde->value();

    return retval;
}

int Form::getTo()
{
    int retval = 0;

    retval = ui->hasta->value();

    return retval;
}

int Form::getValue()
{
    int retval = 0;

    retval = ui->valor->value();

    return retval;
}
