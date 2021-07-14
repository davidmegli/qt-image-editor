#ifndef COMMAND_H
#define COMMAND_H
#include <stack>
#include <iostream>
#include <memory>

class Command {
  public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    //virtual bool mergeWith(Command* command) = 0;
    virtual ~Command() {};
};

#endif // COMMAND_H
