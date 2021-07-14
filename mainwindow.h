#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "command.h"
#include "history.h"
#include <QMainWindow>
#include <QGraphicsScene>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawLine(QPoint begin, QPoint end); //disegna una linea da begin a end
    void drawLine();
    QPoint getBeginPoint();
    QPoint getEndPoint();
    QColor getPenColor();
    int getPenSize();
    void setPen(QColor color, int size);
    QImage getImage();
    void setImage(QImage image);
    void updatePen();
    void updatePainter();
    void setCommand();
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private slots:
    void on_actionSize_triggered();
    void on_actionColor_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

private:
    void init();
    Ui::MainWindow *ui;
    History undoRedoHistory;
    shared_ptr<Command> currentCommand;
    shared_ptr<QGraphicsView> view;
    shared_ptr<QPainter> painter;
    shared_ptr<QImage> image;
    shared_ptr<QPoint> beginPoint;
    shared_ptr<QPoint> endPoint;
    QPen pen;
    int penSize;
    //int brushSize;
    QColor penColor;
    //QColor brushColor;
    bool mouseDown;
};
#endif // MAINWINDOW_H
