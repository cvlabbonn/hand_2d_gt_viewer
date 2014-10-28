#include "mainwindow.h"
#include "ui_mainwindow.h"

bool pairCompare(const std::pair<QString, int>& firstElem, const std::pair<QString, int>& secondElem) {
  return firstElem.second < secondElem.second;

}

void MainWindow::update_BASE_Paths()
{
        PATH_BASE_Base = ui->myTextEdit_PATH->toPlainText();
    if (PATH_BASE_Base.endsWith("/") == false)
        PATH_BASE_Base += "/";

    PATH_BASE_RGB      = QString( PATH_BASE_Base + "rgb"         + "/" );
    PATH_BASE_RGBD     = QString( PATH_BASE_Base + "rgbd"        + "/" );
    PATH_BASE_DepthViz = QString( PATH_BASE_Base + "depth_viz"   + "/" );
    PATH_BASE_Anno     = QString( PATH_BASE_Base + "groundTruth" + "/" );

    QDir().mkdir( PATH_BASE_Anno );

    QStringList myStringListFromPath;
    QRegExp regex("/");
    myStringListFromPath = PATH_BASE_Base.split(regex, QString::SkipEmptyParts);\
    for (int iii=0; iii<(int)myStringListFromPath.size(); iii++)     std::cout << myStringListFromPath[iii].toStdString() << std::endl;
}


void MainWindow::update_path_array(){

    QDir currDir = PATH_BASE_Anno;
    ground_truth_paths.clear();

    if (currDir.exists() == false)
    {
        error_manager(1);
        return;
    }

    QString filterStr = QString( "*.txt"  );

    currDir.setNameFilters( QStringList()<<(filterStr) );

    QFileInfoList files = currDir.entryInfoList();
    foreach (QFileInfo file, files){
        if (!file.isDir()){
            QString filename  = file.fileName();
            int position = filename.section(".",0,0).toInt();
            ground_truth_paths.push_back( std::pair<QString, int>(file.canonicalPath(), position) );
        }
    }
    std::sort(ground_truth_paths.begin(), ground_truth_paths.end(), pairCompare);
}

void MainWindow::update_CURR_Paths()
{
    PATH_CURR_RGB         = QString( PATH_BASE_RGB      + currFrameID_STR + ".png" );
    PATH_CURR_RGBD        = QString( PATH_BASE_RGBD     + currFrameID_STR + ".png" );
    PATH_CURR_DepthViz    = QString( PATH_BASE_DepthViz + currFrameID_STR + ".png" );
    PATH_CURR_Anno        = QString( PATH_BASE_Anno     + currFrameID_STR + ".txt" );
}



void MainWindow::print_CURR_Paths()
{
    std::cout << "PATH_CURR_RGB      - " << PATH_CURR_RGB     .toStdString() << std::endl;
    std::cout << "PATH_CURR_RGBD     - " << PATH_CURR_RGBD    .toStdString() << std::endl;
    std::cout << "PATH_CURR_DepthViz - " << PATH_CURR_DepthViz.toStdString() << std::endl;
    std::cout << "PATH_CURR_Anno     - " << PATH_CURR_Anno    .toStdString() << std::endl;
}

