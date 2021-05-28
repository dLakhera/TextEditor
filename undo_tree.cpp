#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

/*
*
    Guiding example:

    <0> This is Deepak Lakhera [timestamp:: 10:012]  {Done first}
    <1> This is Deepak Sharma  [timestamp:: 10:015]  {Done second}

    The tree looks like follows:

                             Lakhera <0>
                             /
                            /
    This ---> is ---> Deepak 
                            \
                             \
                             Sharma <1>
*                               
*/

bool flag = false;

struct node
{
    vector<node *> next;
    node *prev;
    string data;
    int posInNext = -1;
};

class tree
{
private:
    /* data */
    node *root;
    node *curr;

public:
    tree()
    {
        root = NULL;
        curr = NULL;
    };
    void readTheTree();
    void undo();
    void redo();
    node *addNodeToTree(string);
};

void tree::readTheTree()
{
    stack<string> stk;
    node* ptr = curr;
    while (curr != NULL)
    {
        stk.push(curr->data);
        curr = curr->prev;
    }

    while (!stk.empty())
    {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout<<"\n";
    this->curr = ptr;
    return;
}

void tree::undo()
{
    int pos = --(this->curr->posInNext);

    if (flag && pos == -1)
    {
        /*  
            This case when we are the end of the next array and undo was pressed
            reset posInNext to (next.size() - 1) and return the node previous to current
         */
        this->curr->posInNext = this->curr->next.size() - 1;

        if (this->curr->prev != NULL)
            this->curr = this->curr->prev;

        return;
    }
    else if (flag)
    {
        /*  
            This case when we still have nodes in next left to visit
            so go to the node next in sequence
         */
        if (this->curr->prev != NULL)
            this->curr = this->curr->next[pos];
        return;
    }

    /* 
        If is not a repeat undo command(not consecutive)
        then run this
     */
    if (this->curr->prev != NULL)
        this->curr = this->curr->prev;
    return;
}

void tree::redo()
{
    /* This operation makes */
    int pos = this->curr->posInNext;

    /* If we are the end of next array, then no redo more to go, so return as is */
    if ((pos + 1) == this->curr->next.size())
        return;

    this->curr->posInNext = (pos + 1) % (this->curr->next.size());
    this->curr = this->curr->next[this->curr->posInNext];
    return;
}

node *tree::addNodeToTree(string str)
{
    try
    {
        node *ptr = new node;

        ptr->data = str;
        ptr->posInNext++;
        if (curr == nullptr && root == nullptr)
        {
            root = ptr;
            curr = ptr;
            return this->root;
        }

        /* Set the previous of ptr(new node) to point to the current front node*/
        ptr->prev = this->curr;

        /* Add this new node(ptr) for the next array of current front node */
        this->curr->next.push_back(ptr);

        /* Increase the location of posInNext, so we know which node to fall back to on undo operations */
        this->curr->posInNext++;

        /* Update the current front node, make it ptr */
        this->curr = ptr;

        return this->root;
    }
    catch (std::bad_alloc &ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what();
    };

    return this->curr;
}

void textEditor()
{

    tree document;
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
            document.readTheTree();
            break;
        case 1:
            /* adding to the file struct */
            cin >> output;
            document.addNodeToTree(output);
            break;
        case 2:
            /* undo operation */
            flag = lastCmd == 2 ? true : false;
            document.undo();
            break;
        case 3:
            /* redo operation */
            document.redo();
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

int main()
{
    cout << "Key"
         << "\t"
         << "Function\n";
    cout << "0: "
         << "\t"
         << "Read the document\n";
    cout << "1: "
         << "\t"
         << "Add to the document\n";
    cout << "2: "
         << "\t"
         << "Undo in document\n";
    cout << "3: "
         << "\t"
         << "Redo in document\n";
    cout << "4: "
         << "\t"
         << "Terminate\n";
    textEditor();
    return 0;
}