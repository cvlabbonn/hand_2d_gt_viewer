#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::update_all( int newFrameID ){
    update_frame_id( newFrameID );
    update_all( );
}


void MainWindow::update_all( ){

    update_CURR_Paths();
    update_image();
    update_display();
    update_list();

    ui->myLabel_Img_CurrID->setText( QString::number( current_frame_id ).rightJustified( id_padding, '0', false ) );
    ui->myTextEdit_FrameID->setPlainText( current_frame_id_short_str );
    ui->myLabel_ImgFullPath->setText( path_display );
}


void MainWindow::update_display(){

    if (current_img.empty())
        return;
    current_img = source_img.clone();
    annotations_READ_CurrFrames();

    update_annotations();

    cv::Mat tmpCvRGB;
    cv::cvtColor( current_img, tmpCvRGB, CV_BGR2RGB );

    // create selection box
    if (ctrl_click || shift_click) {
        cv::Rect rect( cv::Point( sel_mouse_x, sel_mouse_y ), cv::Point( ui->myLabel_IMG->mouse_X, ui->myLabel_IMG->mouse_Y ));
        cv::rectangle( tmpCvRGB, rect, cv::Scalar( 0, 0, 0 ));
    }

    qt_img = QImage((uchar*)tmpCvRGB.data, tmpCvRGB.cols, tmpCvRGB.rows, QImage::Format_RGB888 );

    if ( ui->myLabel_IMG->size().width()  != current_img.cols &&
         ui->myLabel_IMG->size().height() != current_img.rows  )
        ui->myLabel_IMG->resize( current_img.cols, current_img.rows );


    ui->myLabel_IMG->clear();
    ui->myLabel_IMG->setPixmap( QPixmap::fromImage( qt_img ) );

}


void MainWindow::update_list(){
    ui->fingerList->clear();
    ui->finger_x_coord->hide();
    ui->finger_y_coord->hide();
    ui->x_joints_label->hide();
    ui->y_joints_label->hide();
    ui->sel_joints_label->hide();

    QString side[] = { "Right", "Left" };
    QString fingers[] = { "Little", "Ring", "Middle", "Pointer", "Thumb" };

    for (int iii = 0; iii < annotations.size(); iii++) {
        if (iii < 14)
            ui->fingerList->addItem( side[0] + " hand - " + fingers[iii / 3] + " finger - joint " + QString::number( iii % 3 ));
        else
            ui->fingerList->addItem( side[1] + " hand - " + fingers[(iii - 14) / 3] + " finger - joint " + QString::number((iii - 14) % 3 ));
    }
}


void MainWindow::update_annotations(){

    int radius = joint_radius;

    for (int iii = 0; iii < annotations.size(); iii++) {
        if (annotations[iii].joint_x == 0  ||  annotations[iii].joint_y == 0) continue;

        cv::Point center;
        center.x = roundToInt( annotations[iii].joint_x );
        center.y = roundToInt( annotations[iii].joint_y );

        if (ui->fingerList->count() > iii && ui->fingerList->item( iii )->isSelected())
            cv::circle( current_img, center, radius, cv::Scalar( 0, 0, 255 ), radius * 2 );
        else
            cv::circle( current_img, center, radius, cv::Scalar( 0, 255, 0 ), radius * 2 );
    }

}


void MainWindow::update_frame_id( int newFrameID ){
    if (newFrameID < 0) current_frame_id = 0;
    else if (newFrameID > (int)ground_truth_paths.size() - 1) current_frame_id = (int)ground_truth_paths.size() - 1;
    else current_frame_id = newFrameID;

    current_frame_id_string      = QString::number( ground_truth_paths[ current_frame_id ].second ).rightJustified( id_padding, '0', false );
    current_frame_id_short_str = QString::number( current_frame_id );

}


void MainWindow::update_image(){

    if (ui->myRadioButton_Image_DepthVIZ->isChecked()) path_display = path_current_depth;
    else if (ui->myRadioButton_Image_RGB->isChecked()) path_display = path_current_rgb;
    else if (ui->myRadioButton_Image_RGBD->isChecked()) path_display = path_current_rgbd;

    source_img = cv::imread( path_display.toStdString() );
    current_img = source_img.clone();
}
