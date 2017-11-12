#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include "form.h"
#include "form2.h"
#include "form3.h"
#include "form4.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ARAP GUI");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_skipsAnt_editingFinished()
{
    if(ui->skipsAnt->value() > ui->nodos->value()-1){
        ui->skipsAnt->setValue(ui->nodos->value()-1);
        QMessageBox::warning(this, "Advertencia", "El valor de los Saltos de las hormigas debe ser menor al numero de nodos.");
    }

}

static int cnt=0;
//Nuevo rango de data-rate
void MainWindow::on_pushButton_clicked()
{
    Form *rango = new Form(this);
    ui->verticalLayout_3->addWidget(rango);
    rango->setObjectName("datarate"+QString::number(cnt));
    connect(rango, SIGNAL(outlist(QString)), this, SLOT(outlist(QString)));
    cnt++;
}

static int cnt2=0;
//Nuevo rango de app-tiempo-iniciar
void MainWindow::on_pushButton_2_clicked()
{
    Form2 *rango2 = new Form2(this);
    ui->verticalLayout->addWidget(rango2);
    rango2->setObjectName("apptinit"+QString::number(cnt2));
    connect(rango2, SIGNAL(outlist2(QString)), this, SLOT(outlist2(QString)));
    cnt2++;
}

static int cnt3=0;
//Nuevo rango de hormigacarga-cantidad-dist
void MainWindow::on_pushButton_3_clicked()
{
    Form3 *rango3 = new Form3(this);
    ui->verticalLayout_4->addWidget(rango3);
    rango3->setObjectName("hormigacand"+QString::number(cnt3));
    connect(rango3, SIGNAL(outlist3(QString)), this, SLOT(outlist3(QString)));
    cnt3++;
}

static int cnt4=0;
//Nuevo rango de delay-computo-incremento
void MainWindow::on_pushButton_4_clicked()
{
    Form4 *rango4 = new Form4(this);
    ui->verticalLayout_5->addWidget(rango4);
    rango4->setObjectName("delaycominc"+QString::number(cnt4));
    connect(rango4, SIGNAL(outlist4(QString)), this, SLOT(outlist4(QString)));
    cnt4++;
}

static int cnt5=0;
//Nuevo rango de delay-computo-dist
void MainWindow::on_pushButton_5_clicked()
{
    Form3 *rango3 = new Form3(this);
    ui->verticalLayout_6->addWidget(rango3);
    rango3->setObjectName("delaycompd"+QString::number(cnt5));
    connect(rango3, SIGNAL(outlist5(QString)), this, SLOT(outlist5(QString)));
    cnt5++;
}

static int cnt6=0;
//Nuevo rango de hormigacarga-destino-dist
void MainWindow::on_pushButton_6_clicked()
{
    Form3 *rango3 = new Form3(this);
    ui->verticalLayout_7->addWidget(rango3);
    rango3->setObjectName("hormigadesd"+QString::number(cnt6));
    connect(rango3, SIGNAL(outlist6(QString)), this, SLOT(outlist6(QString)));
    cnt6++;
}

static int cnt7=0;
//Nuevo rango de hormigacarga-tiempo-dist
void MainWindow::on_pushButton_7_clicked()
{
    Form3 *rango3 = new Form3(this);
    ui->verticalLayout_8->addWidget(rango3);
    rango3->setObjectName("hormigatd"+QString::number(cnt7));
    connect(rango3, SIGNAL(outlist7(QString)), this, SLOT(outlist7(QString)));
    cnt7++;
}

//Escribe los parámetros a un archivo y comienza la simulación
void MainWindow::on_Finish_clicked()
{
    QString direc = QDir::homePath() + "/Documentos/simulador-arap-v1.0-master/arap-dir/"+ ui->nombreex->text() +".txt";
    QFile file(direc);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "error", "File not open");
    }
    QTextStream out(&file);

    out << "nodos " << ui->nodos->value() << "\n";

    out << "semilla " << ui->seedNumber->value() << "\n";

    if(ui->checkBox_2->isChecked())
    {out << "usar-trazas 1" << "\n";} else {
     out << "usar-trazas 0" << "\n";
    }

    out << "saltos " << ui->skipsAnt->value() << "\n";

    out << "puerto " << ui->port->value() <<"\n";

    out << "tamanio-hormiga " << ui->antSize->value() <<"\n";

    out << "intervalo-exploradoras " << ui->doubleSpinBox->value() <<"\n";

    out << "data-rate " << ui->datarate_from->value() << " " << ui->datarate_to->value() << " " << ui->datarate_val->value() << "\n";
    for(int i=0; i<cnt; i++){
        Form* aux = ui->scrollAreaWidgetContents_3->findChild<Form*>("datarate"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        int ret3 = aux->getValue();
        out << "data-rate "<< ret1 <<" "<< ret2 << " " << ret3 << "\n";

    }

    out << "app-tiempo-iniciar " << ui->appinit_from->value() << " " << ui->appinit_to->value() << " " << ui->appinit_val->value() << "\n";
    for(int i=0; i<cnt2; i++){
        Form2* aux = ui->scrollAreaWidgetContents->findChild<Form2*>("apptinit"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        double ret3 = aux->getValue();
        out << "app-tiempo-iniciar " << ret1 <<" "<< ret2 << " " << ret3 << "\n";
    }

    out << "tiempo-detener-simulador " << ui->simulat->value() << "\n";

    out << "delay-enlaces-intervalo " << ui->delaychange->value() << "\n";

    out << "delay-enlaces-dist ";
    switch (ui->indexdist1->currentIndex())
            {
                case 0:
                    out << "UniformRandomVariable " << ui->distuni_min->value() <<" "<< ui->distuni_max->value() << "\n";
                    break;

                case 1:
                    out << "ConstantRandomVariable " << ui->distconst->value() << "\n";
                    break;

                case 2:
                    out << "TriangularRandomVariable " << ui->disttri_min->value() << " "
                        << ui->disttri_max->value() << " " << ui->disttri_med->value() << "\n" ;
                    break;

                case 3:
                    out << "ExponentialRandomVariable " << ui->distexpo_med->value() << " "
                        << ui->distexpo_lim->value()<< "\n";
                    break;

                default:
                    out << "NormalRandomVariable " << ui->distnormal_med->value() << " "
                        << ui->distnormal_var->value() << " " << ui->distnormal_lim->value() << "\n";
                    break;
            }

    out << "delay-computo-dist "<< ui->dist2from->value() <<" "<< ui->dist2to->value();
    switch (ui->indexdist2->currentIndex())
            {
                case 0:
                    out << " UniformRandomVariable " << ui->d2unimin->value() <<" "<< ui->d2unimax->value() << "\n";
                    break;

                case 1:
                    out << " ConstantRandomVariable " << ui->d2constant->value() << "\n";
                    break;

                case 2:
                    out << " TriangularRandomVariable " << ui->d2trimin->value() << " "<< ui->d2trimax->value() << " " << ui->d2trimed->value() << "\n" ;
                    break;

                case 3:
                    out << " ExponentialRandomVariable " << ui->d2expomed->value() << " "<< ui->d2expolim->value()<< "\n";
                    break;

                default:
                    out << "NormalRandomVariable " << ui->d2normed->value() << " "<< ui->d2norvar->value() << " " << ui->d2norlim->value() << "\n";
                    break;
            }
    for(int i=0; i<cnt5; i++){
        Form3* aux = ui->scrollAreaWidgetContents_5->findChild<Form3*>("delaycompd"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        int ret3 = aux->getIndex();
        out << "delay-computo-dist "<< ret1 <<" "<< ret2;
        switch (ret3)
                {
                    case 0:
                        out << " UniformRandomVariable " << aux->getUnimin() <<" "<< aux->getUnimax() << "\n";
                        break;

                    case 1:
                        out << " ConstantRandomVariable " << aux->getConstant() << "\n";
                        break;

                    case 2:
                        out << " TriangularRandomVariable " << aux->getTrimin() << " "
                            << aux->getTrimax() << " " << aux->getTrimed() << "\n" ;
                        break;

                    case 3:
                        out << " ExponentialRandomVariable " << aux->getExpomed() << " "
                            << aux->getExpolim() << "\n";
                        break;

                    default:
                        out << " NormalRandomVariable " << aux->getNormed() << " "
                            << aux->getNorvar() << " " << aux->getNorlim() << "\n";
                        break;
                }
    }


    out << "delay-computo-incremento " << ui->delayinc_from->value() <<" "<< ui->delayinc_to->value()
        <<" " << ui->delayinc_val->value() << "\n";
    for(int i=0; i<cnt4; i++){
        Form4* aux = ui->scrollAreaWidgetContents_2->findChild<Form4*>("delaycominc"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        double ret3 = aux->getValue();
        out << "delay-computo-incremento " << ret1 <<" "<< ret2 << " " << ret3 << "\n";
    }


    if(ui->checkBox->isChecked())
    {out << "habilitar-exploradoras 1" << "\n";} else {
     out << "habilitar-exploradoras 0" << "\n";
    }

    out << "tamanio-cola " << ui->queuesize->value() << "\n";

    out << "tamanio-segmento " << ui->segsize->value() <<"\n";

    out << "path-manager " << ui->pathmanager->text() <<"\n";

    out << "imprimir-tablas-intervalo " << ui->printinterval->value() <<"\n";

    out << "hormigacarga-tiempo-dist "<< ui->hormigatd_from->value() <<" "<< ui->hormigatd_to->value();
    switch (ui->indexdist3->currentIndex())
            {
                case 0:
                    out << " UniformRandomVariable " << ui->d3unimin->value() <<" "<< ui->d3unimax->value() << "\n";
                    break;

                case 1:
                    out << " ConstantRandomVariable " << ui->d3constant->value() << "\n";
                    break;

                case 2:
                    out << " TriangularRandomVariable " << ui->d3trimin->value() << " "<< ui->d3trimax->value() << " " << ui->d3trimed->value() << "\n" ;
                    break;

                case 3:
                    out << " ExponentialRandomVariable " << ui->d3expomed->value() << " "<< ui->d3expolim->value()<< "\n";
                    break;

                default:
                    out << "NormalRandomVariable " << ui->d3normed->value() << " "<< ui->d3norvar->value() << " " << ui->d3norlim->value() << "\n";
                    break;
            }
    for(int i=0; i<cnt7; i++){
        Form3* aux = ui->scrollAreaWidgetContents_7->findChild<Form3*>("hormigatd"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        int ret3 = aux->getIndex();
        out << "hormigacarga-tiempo-dist "<< ret1 <<" "<< ret2;
        switch (ret3)
                {
                    case 0:
                        out << " UniformRandomVariable " << aux->getUnimin() <<" "<< aux->getUnimax() << "\n";
                        break;

                    case 1:
                        out << " ConstantRandomVariable " << aux->getConstant() << "\n";
                        break;

                    case 2:
                        out << " TriangularRandomVariable " << aux->getTrimin() << " "
                            << aux->getTrimax() << " " << aux->getTrimed() << "\n" ;
                        break;

                    case 3:
                        out << " ExponentialRandomVariable " << aux->getExpomed() << " "
                            << aux->getExpolim() << "\n";
                        break;

                    default:
                        out << " NormalRandomVariable " << aux->getNormed() << " "
                            << aux->getNorvar() << " " << aux->getNorlim() << "\n";
                        break;
                }
    }


    out << "hormigacarga-cantidad-dist "<< ui->hormigacd_from->value() <<" "<< ui->hormigacd_to->value();
    switch (ui->indexdist4->currentIndex())
            {
                case 0:
                    out << " UniformRandomVariable " << ui->d4unimin->value() <<" "<< ui->d4unimax->value() << "\n";
                    break;

                case 1:
                    out << " ConstantRandomVariable " << ui->d4constant->value() << "\n";
                    break;

                case 2:
                    out << " TriangularRandomVariable " << ui->d4trimin->value() << " "<< ui->d4trimax->value() << " " << ui->d4trimed->value() << "\n" ;
                    break;

                case 3:
                    out << " ExponentialRandomVariable " << ui->d4expomed->value() << " "<< ui->d4expolim->value()<< "\n";
                    break;

                default:
                    out << "NormalRandomVariable " << ui->d4normed->value() << " "<< ui->d4norvar->value() << " " << ui->d4norlim->value() << "\n";
                    break;
            }
    for(int i=0; i<cnt3; i++){
        Form3* aux = ui->scrollAreaWidgetContents_4->findChild<Form3*>("hormigacand"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        int ret3 = aux->getIndex();
        out << "hormigacarga-cantidad-dist "<< ret1 <<" "<< ret2;
        switch (ret3)
                {
                    case 0:
                        out << " UniformRandomVariable " << aux->getUnimin() <<" "<< aux->getUnimax() << "\n";
                        break;

                    case 1:
                        out << " ConstantRandomVariable " << aux->getConstant() << "\n";
                        break;

                    case 2:
                        out << " TriangularRandomVariable " << aux->getTrimin() << " "
                            << aux->getTrimax() << " " << aux->getTrimed() << "\n" ;
                        break;

                    case 3:
                        out << " ExponentialRandomVariable " << aux->getExpomed() << " "
                            << aux->getExpolim() << "\n";
                        break;

                    default:
                        out << " NormalRandomVariable " << aux->getNormed() << " "
                            << aux->getNorvar() << " " << aux->getNorlim() << "\n";
                        break;
                }
    }

    out << "hormigacarga-destino-dist "<< ui->hormigadd_from->value() <<" "<< ui->hormigadd_to->value();
    switch (ui->indexdist5->currentIndex())
            {
                case 0:
                    out << " UniformRandomVariable " << ui->d5unimin->value() <<" "<< ui->d5unimax->value() << "\n";
                    break;

                case 1:
                    out << " ConstantRandomVariable " << ui->d5constant->value() << "\n";
                    break;

                case 2:
                    out << " TriangularRandomVariable " << ui->d5trimin->value() << " "<< ui->d5trimax->value() << " " << ui->d5trimed->value() << "\n" ;
                    break;

                case 3:
                    out << " ExponentialRandomVariable " << ui->d5expomed->value() << " "<< ui->d5expolim->value()<< "\n";
                    break;

                default:
                    out << "NormalRandomVariable " << ui->d5normed->value() << " "<< ui->d5norvar->value() << " " << ui->d5norlim->value() << "\n";
                    break;
            }
    for(int i=0; i<cnt6; i++){
        Form3* aux = ui->scrollAreaWidgetContents_6->findChild<Form3*>("hormigadesd"+QString::number(i));
        int ret1 = aux->getFrom();
        int ret2 = aux->getTo();
        int ret3 = aux->getIndex();
        out << "hormigacarga-destino-dist "<< ret1 <<" "<< ret2;
        switch (ret3)
                {
                    case 0:
                        out << " UniformRandomVariable " << aux->getUnimin() <<" "<< aux->getUnimax() << "\n";
                        break;

                    case 1:
                        out << " ConstantRandomVariable " << aux->getConstant() << "\n";
                        break;

                    case 2:
                        out << " TriangularRandomVariable " << aux->getTrimin() << " "
                            << aux->getTrimax() << " " << aux->getTrimed() << "\n" ;
                        break;

                    case 3:
                        out << " ExponentialRandomVariable " << aux->getExpomed() << " "
                            << aux->getExpolim() << "\n";
                        break;

                    default:
                        out << " NormalRandomVariable " << aux->getNormed() << " "
                            << aux->getNorvar() << " " << aux->getNorlim() << "\n";
                        break;
                }
    }


    file.flush();
    file.close();
    /*FIN DE ARCHIVO*/

    /*Ejecuta un programa que ordena archivos y a su vez ejectuta simulador ARAP con los parametros de nombre nombreex*/

    QString towrite;
    towrite = "../../Proyectos/build-consola-Desktop_Qt_5_7_0_GCC_64bit-Release/consola "+ ui->nombreex->text() +" "+ui->cantEjec->text()+" &";
    system(towrite.toLatin1().data());

}


//Extrae un número de un String
int getNumberFromQString(const QString &myString)
{
    QString numero;
    for (int var = 0; var < myString.length(); ++var) {
        if (myString.at(var).isDigit()){
            numero.append(myString.at(var));
        }
    }
    return numero.toInt();
}

//Funciones para sacar elementos de la lista de rangos
void MainWindow::outlist(QString name)
{
    int lim = 0;
    if(name.contains("datarate")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt-2; i++){
    Form* auxw = ui->scrollAreaWidgetContents_3->findChild<Form*>("datarate"+QString::number(i+1));
    auxw->setObjectName("datarate"+QString::number(i));
    }
    cnt--;
    }
}
void MainWindow::outlist2(QString name)
{
    int lim = 0;
    if(name.contains("apptinit")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt2-2; i++){
    Form2* auxw = ui->scrollAreaWidgetContents->findChild<Form2*>("apptinit"+QString::number(i+1));
    auxw->setObjectName("apptinit"+QString::number(i));
    }
    cnt2--;
    }
}
void MainWindow::outlist3(QString name)
{
    int lim = 0;
    if(name.contains("hormigacand")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt3-2; i++){
    Form3* auxw = ui->scrollAreaWidgetContents_4->findChild<Form3*>("hormigacand"+QString::number(i+1));
    auxw->setObjectName("hormigacand"+QString::number(i));
    }
    cnt3--;
    }
}
void MainWindow::outlist4(QString name)
{
    int lim = 0;
    if(name.contains("delaycominc")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt4-2; i++){
    Form4* auxw = ui->scrollAreaWidgetContents_2->findChild<Form4*>("delaycominc"+QString::number(i+1));
    auxw->setObjectName("delaycominc"+QString::number(i));
    }
    cnt4--;
    }
}
void MainWindow::outlist5(QString name)
{
    int lim = 0;
    if(name.contains("delaycompd")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt5-2; i++){
    Form3* auxw = ui->scrollAreaWidgetContents_5->findChild<Form3*>("delaycompd"+QString::number(i+1));
    auxw->setObjectName("delaycompd"+QString::number(i));
    }
    cnt5--;
    }
}
void MainWindow::outlist6(QString name)
{
    int lim = 0;
    if(name.contains("hormigadesd")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt6-2; i++){
    Form3* auxw = ui->scrollAreaWidgetContents_6->findChild<Form3*>("hormigadesd"+QString::number(i+1));
    auxw->setObjectName("hormigadesd"+QString::number(i));
    }
    cnt6--;
    }
}
void MainWindow::outlist7(QString name)
{
    int lim = 0;
    if(name.contains("hormigatd")){
    lim = getNumberFromQString(name);
    for(int i = lim; i<=cnt7-2; i++){
    Form3* auxw = ui->scrollAreaWidgetContents_7->findChild<Form3*>("hormigatd"+QString::number(i+1));
    auxw->setObjectName("hormigatd"+QString::number(i));
    }
    cnt7--;
    }
}

//navegacion entre tabs

void MainWindow::on_next_0_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_next_1_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_next_2_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_next_3_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}

void MainWindow::on_next_4_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}

void MainWindow::on_next_5_clicked()
{
    ui->tabWidget->setCurrentIndex(6);
}

void MainWindow::on_next_6_clicked()
{
    ui->tabWidget->setCurrentIndex(7);
}

void MainWindow::on_prev_1_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_prev_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_prev_3_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_prev_4_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void MainWindow::on_prev_5_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}

void MainWindow::on_prev_6_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}

void MainWindow::on_prev_7_clicked()
{
    ui->tabWidget->setCurrentIndex(6);
}

/*Cambia el máximo número de nodo en los rangos de nodos al cambiar el numero de nodos*/
void MainWindow::on_nodos_editingFinished()
{
    int arg1 = ui->nodos->value() - 1;
    ui->hormigacd_to->setValue(arg1);
    ui->hormigadd_to->setValue(arg1);
    ui->hormigatd_to->setValue(arg1);
    ui->appinit_to->setValue(arg1);
    ui->datarate_to->setValue(arg1);
    ui->delayinc_to->setValue(arg1);
    ui->dist2to->setValue(arg1);
    ui->d5unimax->setValue(arg1);
}
