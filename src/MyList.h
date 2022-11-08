#pragma once

#include <iostream>
#include "Node.h"

class MyList
{
    private:
        Node *head;
        Node *tail;
        int nElements;
    public:
        MyList();

        bool IsEmpty();
        bool Contains(int value);
        int Length();
        int GetIndexOf(int value);   
        int At(int pos);    

        void PushOnBeginning(int value);
        void Push(int value);
        int RemoveFirst();
        int RemoveLast();
        int RemoveAt(int pos);
};