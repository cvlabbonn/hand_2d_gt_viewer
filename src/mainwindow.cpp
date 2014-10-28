#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <customlabel.h>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ){
    ui->setupUi( this );
    connect( ui->myLabel_IMG, SIGNAL( Mouse_Pos()),       this, SLOT( Mouse_Pos())       );
    connect( ui->myLabel_IMG, SIGNAL( Mouse_Left()),      this, SLOT( Mouse_Left())      );
    connect( ui->myLabel_IMG, SIGNAL( Mouse_Pressed()),   this, SLOT( Mouse_Pressed())   );
    connect( ui->myLabel_IMG, SIGNAL( Mouse_Release()),   this, SLOT( Mouse_Release())   );
    ui->myLabel_IMG->setMouseTracking( true );
    colorize_Black();
    ui->myTabWidget->setEnabled( false );
    is_sequence_loaded = false;
    ctrl_key = false;
    ctrl_click = false;
    shift_click = false;
    shift_key = false;
    ui->finger_x_coord->hide();
    ui->finger_y_coord->hide();
    ui->x_joints_label->hide();
    ui->y_joints_label->hide();
    ui->sel_joints_label->hide();

    //load settings
    QSettings settings( "../config/config.ini", QSettings::IniFormat );
    settings.beginGroup( "General" );
    frame_step = settings.value( "frame_step", 1 ).toInt();
    frames_start = settings.value( "start_frame", 0 ).toInt();
    id_padding = settings.value( "name_0padding", 3 ).toInt();
    settings.endGroup();
    settings.beginGroup( "Display" );
    joint_radius = settings.value( "joint_radius" ).toInt();
    settings.endGroup();

}


MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_fingerList_currentRowChanged( int currentRow ){
    if (currentRow == -1)
        return;
    ui->finger_x_coord->show();
    ui->finger_y_coord->show();
    ui->x_joints_label->show();
    ui->y_joints_label->show();
    ui->sel_joints_label->show();
    ui->finger_x_coord->setText( QString::number( roundToInt( annotations[currentRow].joint_x )));
    ui->finger_y_coord->setText( QString::number( roundToInt( annotations[currentRow].joint_y )));

}


void MainWindow::on_fingerList_itemSelectionChanged(){
    update_display();
}


int MainWindow::roundToInt( double num ){
    return std::floor( num + 0.5 );
}


void MainWindow::on_browse_path_clicked(){
    QString filename = QFileDialog::getExistingDirectory( this, tr( "Select Folder" ));

    ui->myTextEdit_PATH->setPlainText( filename );
    on_myButton_Update_PATH_clicked();

}
