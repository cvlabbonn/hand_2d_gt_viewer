#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::keyPressEvent( QKeyEvent *myKey ){

    if (myKey->key() == Qt::Key_Escape) this->close();
    else if (myKey->key() == Qt::Key_L) on_myButton_Update_PATH_clicked();
    else if (is_sequence_loaded == false) return;
    else if (myKey->key() == Qt::Key_Left && !ctrl_key) on_myButton_Prev_clicked();
    else if (myKey->key() == Qt::Key_Right && !ctrl_key) on_myButton_Next_clicked();
    else if (myKey->key() == Qt::Key_U) on_myButton_UpdateFrameID_clicked();

    else if (myKey->key() == Qt::Key_R) {
        ui->myRadioButton_Image_RGB->setChecked( true );
        on_myRadioButton_Image_RGB_clicked();
    }else if (myKey->key() == Qt::Key_T) {
        ui->myRadioButton_Image_RGBD->setChecked( true );
        on_myRadioButton_Image_RGBD_clicked();
    }else if (myKey->key() == Qt::Key_D) {
        ui->myRadioButton_Image_DepthVIZ->setChecked( true );
        on_myRadioButton_Image_DepthVIZ_clicked();
    }


}


void MainWindow::keyReleaseEvent( QKeyEvent *myKey ){
    if (myKey->key() == Qt::Key_Shift) shift_key = false;
}


void MainWindow::Mouse_Pos(){
    ui->myLabel_Mouse_X->setText( QString::number( ui->myLabel_IMG->mouse_X ) );
    ui->myLabel_Mouse_Y->setText( QString::number( ui->myLabel_IMG->mouse_Y ) );
    if (ctrl_click || shift_click)
        update_display();
}


void MainWindow::Mouse_Pressed(){
    if (is_sequence_loaded == false) return;
}


void MainWindow::Mouse_Release(){
    if (annotations.size() == 0)
        return;
    ui->fingerList->clearSelection();
    double best_dist = 999999999;
    int best_id = -1;
    // find the closest point to the clicked position
    for (int i = 0; i < (int)annotations.size(); i++) {
        // calculate distance
        double dist = sqrt( pow((double)ui->myLabel_IMG->mouse_X - annotations[i].joint_x, 2 ) + pow((double)ui->myLabel_IMG->mouse_Y - annotations[i].joint_y, 2 ));
        if (dist < best_dist) {
            best_id = i;
            best_dist = dist;
        }
    }
    // select the closest point
    ui->fingerList->setCurrentRow( best_id, QItemSelectionModel::Toggle );
    update_display();

}


void MainWindow::Mouse_Left(){
}
