#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool flag = false;

class UndoStack
{
private:
    stack<string> undoStack;
    stack<string> redoStack;

public:
    UndoStack(){};
    void readTheTree();
    void undo();
    void redo();
    void addNodeToTree(string);
};

void UndoStack::readTheTree() 
{
    stack<string> temp;

    while(!undoStack.empty()) {
        
    }
}

void UndoStack::undo() 
{
    
}

void UndoStack::redo() 
{
    
}

void UndoStack::addNodeToTree(string) 
{
    
}



void textEditor()
{
    UndoStack undoStack;
    int lastCmd = -1;
    while (true)
    {
        int type;
        cin >> type;
        string output;
        switch (type)
        {
        case 0:
            /* read the sentence */
            undoStack.readTheTree();
            break;
        case 1:
            /* adding to the file struct */
            cin >> output;
            undoStack.addNodeToTree(output);
            break;
        case 2:
            /* undo operation */
            flag = lastCmd == 2 ? true : false;
            undoStack.undo();
            break;
        case 3:
            /* redo operation */
            undoStack.redo();
            break;
        default:
            /* if none of the above, terminate */
            type = 4;
            break;
        }

        if (type == 4)
            break;

        lastCmd = type;
    }
}

int main(){
    textEditor();
return 0;
}