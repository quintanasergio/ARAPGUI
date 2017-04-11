#include "form3.h"
#include "ui_form3.h"

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3)
{
    ui->setupUi(this);
}

Form3::~Form3()
{
    delete ui;
}

void Form3::on_pushButton_clicked()
{
    this->deleteLater();

    QString nombre = objectName();

    emit outlist3(nombre);
    emit outlist5(nombre);
    emit outlist6(nombre);
    emit outlist7(nombre);
}

int Form3::getFrom()
{
    int retval = 0;

    retval = ui->desde->value();

    return retval;
}

int Form3::getTo()
{
    int retval = 0;

    retval = ui->hasta->value();

    return retval;
}

int Form3::getIndex()
{
    int retval = 0;

    retval = ui->comboBox->currentIndex();

    return retval;
}

float Form3::getUnimin()
{
    float retval = 0;

    retval = ui->unimin->value();

    return retval;
}

float Form3::getUnimax()
{
    float retval = 0;

    retval = ui->unimax->value();

    return retval;
}

float Form3::getConstant()
{
    float retval = 0;

    retval = ui->constant->value();

    return retval;
}

float Form3::getTrimin()
{
    float retval = 0;

    retval = ui->trimin->value();

    return retval;
}

float Form3::getTrimax()
{
    float retval = 0;

    retval = ui->trimax->value();

    return retval;
}

float Form3::getTrimed()
{
    float retval = 0;

    retval = ui->trimed->value();

    return retval;
}

float Form3::getExpomed()
{
    float retval = 0;

    retval = ui->expomed->value();

    return retval;
}

float Form3::getExpolim()
{
    float retval = 0;

    retval = ui->expolim->value();

    return retval;
}

float Form3::getNormed()
{
    float retval = 0;

    retval = ui->normed->value();

    return retval;
}

float Form3::getNorlim()
{
    float retval = 0;

    retval = ui->norlim->value();

    return retval;
}

float Form3::getNorvar()
{
    float retval = 0;

    retval = ui->norvar->value();

    return retval;
}


