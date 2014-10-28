#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::annotations_READ_CurrFrames()
{

    QFile fileIN( PATH_CURR_Anno );
    fileIN.open(QIODevice::ReadOnly);
    if (fileIN.size() == 0)
    {
        std::cout << "Current Frame - Empty annotation file" << std::endl;
        fileIN.close();
        return;
    }

    annotations.clear();
    QTextStream myStreamIN(&fileIN);

    while(!myStreamIN.atEnd())
    {
        AnnotationPatch temp;
        int           dummyInt;
        myStreamIN >> dummyInt;
        myStreamIN >> temp.joint_X;
        myStreamIN >> temp.joint_Y;
        annotations.push_back(temp);
    }

    fileIN.close();

}

