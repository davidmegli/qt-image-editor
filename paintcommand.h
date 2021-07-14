#ifndef PAINTCOMMAND_H
#define PAINTCOMMAND_H
#include "command.h"
#include "mainwindow.h"

class PaintCommand : public Command
{ //TODO: Unit Test
private:
    MainWindow* mainWin; //il riferimento alla MainWindow mi serve per richiamarne i metodi
    QImage image; //contiene l'immagine prima della modifica
    QPoint begin; //begin e end sono informazioni necessarie per effettuare l'execute (redo)
    QPoint end;
    QColor penColor;
    int penSize;

public:
    PaintCommand(MainWindow* mainWin);
    void execute() override;
    void undo() override;
};

#endif // PAINTCOMMAND_H
