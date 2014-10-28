#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

////////////////////////////////////////////////
// http://www.youtube.com/watch?v=d0CDMtfefB4 //
////////////////////////////////////////////////

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    int mouse_X;
    int mouse_Y;

signals:
    void Mouse_Pos();
    void Mouse_Left();
    void Mouse_Pressed();
    void Mouse_Release();
    
public slots:
    
};

#endif // CUSTOMLABEL_H
