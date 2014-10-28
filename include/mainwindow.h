#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QImageWriter>
#include <QTextStream>
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <fstream>

struct AnnotationPatch {
    double joint_x;
    double joint_y;
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    QString path_base;
    QString path_rgb;
    QString path_rgbd;
    QString path_depth;
    QString path_annotations;

    QString path_current_rgb;
    QString path_current_rgbd;
    QString path_current_depth;
    QString path_current_annotations;
    QString path_display;

    int frame_step;
    int joint_radius;
    int frames_total;
    int frames_start;

    int id_padding;
    int current_frame_id;
    QString current_frame_id_string;
    QString current_frame_id_short_str;

    cv::Mat current_img;
    cv::Mat source_img;
    QImage qt_img;
    bool ctrl_key;
    bool ctrl_click;
    bool shift_key;
    bool shift_click;
    int sel_mouse_x;
    int sel_mouse_y;

    bool is_sequence_loaded;

    QVector<AnnotationPatch> annotations;
    QVector<std::pair<QString, int> > ground_truth_paths;

    void update_all();
    void update_all( int newFrameID );
    void update_frame_id( int newFrameID );
    void update_image();
    void update_display();
    void update_annotations();
    void update_CURR_Paths();
    void update_BASE_Paths();
    void update_list();

    void annotations_READ_CurrFrames();
    int roundToInt( double num );

    void print_CURR_Paths();

    void colorize_Black();

    int TOTAL_JOINTS__ALL_hands;
    int TOTAL_JOINTS__one_hand;

private slots:
    void on_myButton_Next_clicked();

    void on_myButton_Prev_clicked();

    void on_myButton_UpdateFrameID_clicked();

    void on_myRadioButton_Image_RGB_clicked();

    void on_myRadioButton_Image_DepthVIZ_clicked();

    void on_myRadioButton_Image_RGBD_clicked();

    void Mouse_Pos();
    void Mouse_Left();
    void Mouse_Pressed();
    void Mouse_Release();

    void keyPressEvent( QKeyEvent *myKey );
    void keyReleaseEvent( QKeyEvent *myKey );

    void on_myButton_Update_PATH_clicked();

    void on_fingerList_currentRowChanged( int currentRow );

    void on_fingerList_itemSelectionChanged();

    void on_browse_path_clicked();

private:
    Ui::MainWindow *ui;
    void error_manager( int type );
    void update_path_array();
};

#endif // MAINWINDOW_H
