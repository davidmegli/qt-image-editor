#ifndef HISTORY_H
#define HISTORY_H

#include "command.h"
#include <stack>

using namespace std;

class History
{
public:
    History() {};
    void executeCommand(shared_ptr<Command> command);
    bool undo();
    bool redo();
private:
    stack<shared_ptr<Command>> undoStack;
    stack<shared_ptr<Command>> redoStack;
};

#endif // HISTORY_H
