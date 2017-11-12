#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_skipsAnt_editingFinished();

private slots:
    
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_next_0_clicked();

    void on_next_1_clicked();

    void on_next_2_clicked();

    void on_next_3_clicked();

    void on_next_4_clicked();

    void on_next_5_clicked();

    void on_next_6_clicked();

    void on_prev_1_clicked();

    void on_prev_2_clicked();

    void on_prev_3_clicked();

    void on_prev_4_clicked();

    void on_prev_5_clicked();

    void on_prev_6_clicked();

    void on_prev_7_clicked();

    void on_pushButton_3_clicked();

    void on_Finish_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void outlist(QString name);

    void outlist2(QString name);

    void outlist3(QString name);

    void outlist4(QString name);

    void outlist5(QString name);

    void outlist6(QString name);

    void outlist7(QString name);

    void on_indexdist3_currentIndexChanged(int index);

    void on_nodos_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
