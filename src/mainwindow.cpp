#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <customlabel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(   ui->myLabel_IMG, SIGNAL(Mouse_Pos()),       this, SLOT(Mouse_Pos())       );
    connect(   ui->myLabel_IMG, SIGNAL(Mouse_Left()),      this, SLOT(Mouse_Left())      );
    connect(   ui->myLabel_IMG, SIGNAL(Mouse_Pressed()),   this, SLOT(Mouse_Pressed())   );
    connect(   ui->myLabel_IMG, SIGNAL(Mouse_Release()),   this, SLOT(Mouse_Release())   );
    ui->myLabel_IMG->setMouseTracking(true);
    colorize_Black();
    ui->myTabWidget->setEnabled(false);
    isSequenceLoaded = false;
    ctrl_key = false;
    ctrl_click = false;
    shift_click = false;
    shift_key = false;

    //load settings
    QSettings settings("../config/config.ini", QSettings::IniFormat);
    settings.beginGroup("General");
    frame_step = settings.value("frame_step",1).toInt();
    FRAMES_ID_START = settings.value("start_frame",0).toInt();
    ID_NUMB_OF_DIGITS = settings.value("name_0padding",3).toInt();
    settings.endGroup();
    settings.beginGroup("Display");
    joint_radius = settings.value("joint_radius").toInt();
    settings.endGroup();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fingerList_currentRowChanged(int currentRow)
{
    if(currentRow == -1)
        return;
    ui->selFingerX->setEnabled(true);
    ui->selFingerY->setEnabled(true);
    ui->selFingerX->setValue(roundToInt(annotations[currentRow].joint_X));
    ui->selFingerY->setValue(roundToInt(annotations[currentRow].joint_Y));

}

void MainWindow::on_selFingerX_valueChanged(int arg1)
{
    annotations[roundToInt(ui->fingerList->currentRow())].joint_X = arg1;
    update_CURR_Image();
    update_CURR_Display(true);
}

void MainWindow::on_selFingerY_valueChanged(int arg1)
{
    annotations[roundToInt(ui->fingerList->currentRow())].joint_Y = arg1;
    update_CURR_Image();
    update_CURR_Display(true);
}

void MainWindow::on_fingerList_itemSelectionChanged()
{
    update_CURR_Display();
}

int MainWindow::roundToInt(double num){
    return std::floor(num + 0.5);
}

void MainWindow::on_browse_path_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, tr("Select Folder"));
    ui->myTextEdit_PATH->setPlainText(filename);
    on_myButton_Update_PATH_clicked();

}
