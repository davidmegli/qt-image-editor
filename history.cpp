#include "history.h"

#include <QDebug>

void History::executeCommand(shared_ptr<Command> command)
{
    redoStack = stack<shared_ptr<Command>>();
    command->execute();
    undoStack.push(command);
}

bool History::undo()
{
    bool result = false;
    if(!undoStack.empty())
    {
        undoStack.top()->undo();
        redoStack.push(undoStack.top());
        undoStack.pop();
        result = true;
    }
    return result;
}

bool History::redo()
{
    bool result = false;
    if(!redoStack.empty())
    {
        redoStack.top()->execute();
        undoStack.push(redoStack.top());
        redoStack.pop();
        result = true;
    }
    return result;
}
