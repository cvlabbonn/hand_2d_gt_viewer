#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::update_CURR_THINGS( int newFrameID )
{
    update_CURR_frameID( newFrameID );
    update_CURR_THINGS(  true       );
}

void MainWindow::update_CURR_THINGS( bool removeAnnotationsALL )
{

    update_CURR_Paths();
    update_CURR_Image();

    update_CURR_Display();

    update_list();

    ui->myLabel_Img_CurrID->setText( QString::number( currFrameID ).rightJustified(ID_NUMB_OF_DIGITS, '0', false) );
    ui->myTextEdit_FrameID->setPlainText( currFrameID_STRshort );

    ui->myLabel_ImgFullPath->setText( PATH_CURR_DISPLAY );
}

void MainWindow::update_CURR_Display(bool spin_box)
{

    if (imgCV.empty()) {
        std::cout << "MainWindow::update_CURR_Display - EMPTY image !!!" << std::endl;
        //FIXME: add error here
        return;
    }
    imgCV = imgCV_source.clone();
    annotations_READ_CurrFrames();

    update_CURR_AnnotationsOVERLAY();

    cv::Mat tmpCvRGB;
    cv::cvtColor(imgCV, tmpCvRGB, CV_BGR2RGB);

    // create selection box
    if (ctrl_click || shift_click) {
        cv::Rect rect(cv::Point(selMouseX, selMouseY), cv::Point(ui->myLabel_IMG->mouse_X, ui->myLabel_IMG->mouse_Y));
        cv::rectangle(tmpCvRGB, rect, cv::Scalar(0, 0, 0));
    }

    imgQT = QImage((uchar*)tmpCvRGB.data, tmpCvRGB.cols, tmpCvRGB.rows, QImage::Format_RGB888);

    if ( ui->myLabel_IMG->size().width()  != imgCV.cols &&
         ui->myLabel_IMG->size().height() != imgCV.rows  )
        ui->myLabel_IMG->resize(imgCV.cols, imgCV.rows  );


    ui->myLabel_IMG->clear();
    ui->myLabel_IMG->setPixmap( QPixmap::fromImage(imgQT) );

}

void MainWindow::update_list()
{
    ui->fingerList->clear();
    QString side[] = { "Right", "Left" };
    QString fingers[] = { "Little", "Ring", "Middle", "Pointer", "Thumb" };

    ui->selFingerX->setMinimum(0);
    ui->selFingerX->setMaximum(imgCV.cols);
    ui->selFingerY->setMinimum(0);
    ui->selFingerY->setMaximum(imgCV.rows);
    ui->selFingerX->setEnabled(false);
    ui->selFingerY->setEnabled(false);

    for (int iii = 0; iii < annotations.size(); iii++) {
        if (iii < 14)
            ui->fingerList->addItem(side[0] + " hand - " + fingers[iii / 3] + " finger - joint " + QString::number(iii % 3));
        else
            ui->fingerList->addItem(side[1] + " hand - " + fingers[(iii - 14) / 3] + " finger - joint " + QString::number((iii - 14) % 3));
    }
}

void MainWindow::update_CURR_AnnotationsOVERLAY()
{

    int radius = joint_radius;

    for (int iii = 0; iii < annotations.size(); iii++) {
        if (annotations[iii].joint_X == 0  ||  annotations[iii].joint_Y == 0) continue;

        cv::Point center;
        center.x = roundToInt(annotations[iii].joint_X);
        center.y = roundToInt(annotations[iii].joint_Y);

        if (ui->fingerList->count() > iii && ui->fingerList->item(iii)->isSelected())
            cv::circle(imgCV, center, radius, cv::Scalar(0, 0, 255), radius * 2);
        else
            cv::circle(imgCV, center, radius, cv::Scalar(0, 255, 0), radius * 2);
    }

}




void MainWindow::update_CURR_frameID( int newFrameID )
{
    if (newFrameID < 0) currFrameID = 0;
    else if (newFrameID > (int)ground_truth_paths.size() - 1) currFrameID = (int)ground_truth_paths.size() - 1;
    else currFrameID = newFrameID;

    currFrameID_STR      = QString::number( ground_truth_paths[ currFrameID ].second).rightJustified(ID_NUMB_OF_DIGITS, '0', false);
    currFrameID_STRshort = QString::number( currFrameID);

}



void MainWindow::update_CURR_Image()
{

    if (ui->myRadioButton_Image_DepthVIZ->isChecked()) PATH_CURR_DISPLAY = PATH_CURR_DepthViz;
    else if (ui->myRadioButton_Image_RGB->isChecked()) PATH_CURR_DISPLAY = PATH_CURR_RGB;
    else if (ui->myRadioButton_Image_RGBD->isChecked()) PATH_CURR_DISPLAY = PATH_CURR_RGBD;

    imgCV_source = cv::imread( PATH_CURR_DISPLAY.toStdString() );
    imgCV = imgCV_source.clone();
}


