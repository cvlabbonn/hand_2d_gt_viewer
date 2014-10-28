#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::error_manager( int type ){

    QMessageBox messageBox;

    switch (type) {
    case 1:
        messageBox.critical( 0, "Error", "The folder doesn't exist or doesn't contain a valid annotation" );
        break;
    case 2:
        messageBox.critical( 0, "Error", "The annotation file is empty." );
        break;
    default:
        break;
    }
}
