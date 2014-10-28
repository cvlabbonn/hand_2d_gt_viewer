#include "mainwindow.h"
#include "ui_mainwindow.h"




void MainWindow::on_myButton_Update_PATH_clicked(){

    try{

        update_BASE_Paths();
        update_path_array();
        QDir currDir = path_annotations;

        if (currDir.exists() == false) {
            error_manager( 1 );
            return;
        }

        QString filterStr = QString( "*.txt" );
        currDir.setNameFilters( QStringList() << (filterStr) );
        QStringList fileList = currDir.entryList();
        frames_total = fileList.size();
        ui->myLabel_Img_TotalNumb->setText( QString::number( frames_total ) );
        ui->myTabWidget->setEnabled( true );
        update_all( frames_start );
        is_sequence_loaded = true;

    }
    catch (...) {
        error_manager( 1 );
    }

}


void MainWindow::on_myButton_Next_clicked(){
    update_all( current_frame_id + frame_step );
}


void MainWindow::on_myButton_Prev_clicked(){
    update_all( current_frame_id - frame_step );
}


void MainWindow::on_myButton_UpdateFrameID_clicked(){
    update_all( ui->myTextEdit_FrameID->toPlainText().toInt() );
}


void MainWindow::on_myRadioButton_Image_RGB_clicked(){
    update_all();
}


void MainWindow::on_myRadioButton_Image_RGBD_clicked(){
    update_all();
}


void MainWindow::on_myRadioButton_Image_DepthVIZ_clicked(){
    update_all();
}


void MainWindow::colorize_Black(){
    cv::Mat temp = cv::Mat::zeros( ui->myLabel_IMG->height(), ui->myLabel_IMG->width(), CV_8UC3 );

    ui->myLabel_IMG->setPixmap( QPixmap::fromImage( QImage((uchar*)temp.data, temp.cols, temp.rows, QImage::Format_RGB888 ) ) );
}
