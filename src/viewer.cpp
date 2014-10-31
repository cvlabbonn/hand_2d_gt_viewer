#include "viewer.h"
#include "ui_mainwindow.h"

#include <customlabel.h>

Viewer::Viewer( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ){
    ui->setupUi( this );
    connect( ui->myLabel_IMG, SIGNAL( mouse_position()),  this, SLOT( mouse_position())  );
    connect( ui->myLabel_IMG, SIGNAL( mouse_left()),      this, SLOT( mouse_left())      );
    connect( ui->myLabel_IMG, SIGNAL( mouse_pressed()),   this, SLOT( mouse_pressed())   );
    connect( ui->myLabel_IMG, SIGNAL( mouse_release()),   this, SLOT( mouse_release())   );
    ui->myLabel_IMG->setMouseTracking( true );
    colorize_black();
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


Viewer::~Viewer(){
    delete ui;
}


void Viewer::on_finger_list_currentRowChanged( int current_row ){
    if ( current_row == -1 )
        return;
    ui->finger_x_coord->show();
    ui->finger_y_coord->show();
    ui->x_joints_label->show();
    ui->y_joints_label->show();
    ui->sel_joints_label->show();
    ui->finger_x_coord->setText( QString::number( round_to_int( annotations[current_row].joint_x )));
    ui->finger_y_coord->setText( QString::number( round_to_int( annotations[current_row].joint_y )));

}


void Viewer::on_finger_list_itemSelectionChanged(){
    update_display();
}


int Viewer::round_to_int( double num ){
    return std::floor( num + 0.5 );
}


void Viewer::on_browse_path_clicked(){
    QString filename = QFileDialog::getExistingDirectory( this, tr( "Select Folder" ));

    if ( filename != "" ) {
        ui->path_to_load->setPlainText( filename );
        new_path_selected();
    }

}
