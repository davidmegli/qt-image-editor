#include "paintcommand.h"
#include "command.h"
#include <QPainter>
#include <QDebug>

using std::shared_ptr;

PaintCommand::PaintCommand(MainWindow* mainWin)
{
    this->mainWin = mainWin;
    this->image = mainWin->getImage();
    this->begin = mainWin->getBeginPoint();
    this->end = mainWin->getEndPoint();
    this->penColor = mainWin->getPenColor();
    this->penSize = mainWin->getPenSize();
}

void PaintCommand::execute()
{
    mainWin->setImage(image.copy());
    mainWin->setPen(penColor,penSize);
    mainWin->drawLine(begin,end);
    mainWin->update();
    /*
    this->image = mainWin->getImage();
    this->begin = mainWin->getBeginPoint();
    this->end = mainWin->getEndPoint();
    mainWin->drawLine();
    mainWin->update();*/
}

void PaintCommand::undo()
{
    mainWin->setImage(image.copy());
    mainWin->update();
}
