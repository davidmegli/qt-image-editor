#include "paintcommand.h"
#include "command.h"
#include <QPainter>
#include <QDebug>

using std::shared_ptr;

PaintCommand::PaintCommand(MainWindow* mainWin)
{
    this->mainWin = mainWin;
}

void PaintCommand::execute()
{
    this->image = mainWin->getImage();
    this->begin = mainWin->getBeginPoint();
    this->end = mainWin->getEndPoint();
    mainWin->drawLine();
    mainWin->update();
}

void PaintCommand::undo()
{
    mainWin->setImage(image.copy());
    mainWin->updatePainter();
    mainWin->update();
}
