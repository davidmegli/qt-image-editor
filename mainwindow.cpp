#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintcommand.h"
#include <QScreen>
#include <QPaintEvent>
#include <QPainter>
#include <QApplication>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QDebug>

#define DEFAULT_PEN_SIZE 5

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int height = 1080;
    int width = 1920;
    //TODO: handle height & width in a class, make a menu to edit them
    //TODO: container for image
    //TODO: make scrollbars

    image = std::make_shared<QImage>(width,height,QImage::Format_ARGB32_Premultiplied);
    painter = std::make_shared<QPainter>(image.get());
    beginPoint = std::make_shared<QPoint>();
    endPoint = std::make_shared<QPoint>();
    setCommand();                //TODO: create command class for brush, rectangle, eraser, etc..
    mouseDown = false;
    penColor = QColor(Qt::black);
    penSize = DEFAULT_PEN_SIZE;  //TODO: create default pen size as static value of class Pen

    setWindowTitle("QT Image Editor");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLine(QPoint begin, QPoint end)
{
    qDebug()<<"painter!!!";
    qDebug()<<"begin: "<<begin.x()<<begin.y();
    qDebug()<<"end: "<<end.x()<<end.y();
    qDebug()<<painter.use_count();
    qDebug()<<image.use_count();
    painter->drawLine(begin,end);
}

void MainWindow::drawLine()
{
    QPoint p1(*beginPoint);
    QPoint p2(*endPoint);
    drawLine(p1,p2);
}

QPoint MainWindow::getBeginPoint()
{
    QPoint point(beginPoint->x(),beginPoint->y());
    return point;
}

QPoint MainWindow::getEndPoint()
{
    QPoint point(endPoint->x(),endPoint->y());
    return point;
}

QImage MainWindow::getImage()
{
    return image->copy();
}

void MainWindow::setImage(QImage image)
{
    painter.reset();
    this->image.reset();
    this->image = make_shared<QImage>(image.copy());
    updatePainter();
}

void MainWindow::updatePainter()
{
    painter.reset();
    painter = make_shared<QPainter>(image.get());
}

void MainWindow::setCommand()
{
    qDebug()<<"setCommand";
    currentCommand = std::make_shared<PaintCommand>(this);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(image->rect(), Qt::white);
    painter.drawImage(0,0,*image);
    e->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mouseDown = true;
    *beginPoint = e->pos();
    setCommand();
    e->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"mouseMoveEvent";
    if(mouseDown)
    {
        QPen pen(penColor);
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidth(penSize);
        *endPoint = e->pos();
        painter->setPen(pen);
        setCommand();
        undoRedoHistory.executeCommand(currentCommand);
        *beginPoint = *endPoint;
    }
    e->accept();
    return;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    setCommand();
    mouseDown = false;
    e->accept();
}


void MainWindow::on_actionSize_triggered()
{
    penSize = QInputDialog::getInt(this,"Pen Size","Insert Size:",penSize,1);
}


void MainWindow::on_actionColor_triggered()
{
    penColor = QColorDialog::getColor(penColor,this,"Pen Color");
}


void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Exit","Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No );
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    if (!fileName.isEmpty())
    {
      image->save(fileName);
    }
}


void MainWindow::on_actionUndo_triggered()
{
    undoRedoHistory.undo();
}


void MainWindow::on_actionRedo_triggered()
{
    undoRedoHistory.redo();
}

