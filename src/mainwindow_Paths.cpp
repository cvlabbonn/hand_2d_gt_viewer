#include "mainwindow.h"
#include "ui_mainwindow.h"

bool pairCompare( const std::pair<QString, int>& firstElem, const std::pair<QString, int>& secondElem ){
    return firstElem.second < secondElem.second;

}


void MainWindow::update_BASE_Paths(){
    path_base = ui->myTextEdit_PATH->toPlainText();
    if (path_base.endsWith( "/" ) == false)
        path_base += "/";

    path_rgb      = QString( path_base + "rgb"         + "/" );
    path_rgbd     = QString( path_base + "rgbd"        + "/" );
    path_depth = QString( path_base + "depth_viz"   + "/" );
    path_annotations     = QString( path_base + "groundTruth" + "/" );

    QDir().mkdir( path_annotations );

    QStringList myStringListFromPath;
    QRegExp regex( "/" );
    myStringListFromPath = path_base.split( regex, QString::SkipEmptyParts ); \
    for (int iii = 0; iii < (int)myStringListFromPath.size(); iii++) std::cout << myStringListFromPath[iii].toStdString() << std::endl;
}


void MainWindow::update_path_array(){

    QDir currDir = path_annotations;

    ground_truth_paths.clear();

    if (currDir.exists() == false) {
        error_manager( 1 );
        return;
    }

    QString filterStr = QString( "*.txt" );

    currDir.setNameFilters( QStringList() << (filterStr) );

    QFileInfoList files = currDir.entryInfoList();
    foreach( QFileInfo file, files ){
        if (!file.isDir()) {
            QString filename  = file.fileName();
            int position = filename.section( ".", 0, 0 ).toInt();
            ground_truth_paths.push_back( std::pair<QString, int>( file.canonicalPath(), position ) );
        }
    }
    std::sort( ground_truth_paths.begin(), ground_truth_paths.end(), pairCompare );
}


void MainWindow::update_CURR_Paths(){
    path_current_rgb         = QString( path_rgb      + current_frame_id_string + ".png" );
    path_current_rgbd        = QString( path_rgbd     + current_frame_id_string + ".png" );
    path_current_depth    = QString( path_depth + current_frame_id_string + ".png" );
    path_current_annotations        = QString( path_annotations     + current_frame_id_string + ".txt" );
}


void MainWindow::print_CURR_Paths(){
    std::cout << "PATH_CURR_RGB      - " << path_current_rgb.toStdString() << std::endl;
    std::cout << "PATH_CURR_RGBD     - " << path_current_rgbd.toStdString() << std::endl;
    std::cout << "PATH_CURR_DepthViz - " << path_current_depth.toStdString() << std::endl;
    std::cout << "PATH_CURR_Anno     - " << path_current_annotations.toStdString() << std::endl;
}
