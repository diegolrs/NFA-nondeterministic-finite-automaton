#include <iostream>
#include <string>
#include "MyList.h"

using namespace std;

int main()
{
    MyList *l = new MyList();

    for(int i = 0; i < 10; i++)
        l->Push(i);
        //l->PushOnBeginning(i);

    //for(int i = 0; i < 50; i++)
    //    cout << l->GetIndexOf(i) << " ";

    int n = 5;
    for(int ni = 0; ni < n; ni++)
        //l->RemoveFirst();
        //l->RemoveLast();
        l->RemoveAt(1);

    cout << "ja removi" << std::endl;

    for(int i = 0; i < 10-n; i++)
        cout << l->At(i) << " ";

    cout << "finalizei";
}