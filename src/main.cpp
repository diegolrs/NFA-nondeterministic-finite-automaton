#include <iostream>
#include <string>
#include "MyList.h"

using namespace std;

int main()
{
    MyList<string> *l = new MyList<string>();

    for(int i = 0; i < 10; i++)
        l->Push(to_string(i) + "str");
        //l->PushOnBeginning(i);

    //for(int i = 0; i < 50; i++)
    //    cout << l->GetIndexOf(i) << " ";

    int n = 5;
    for(int ni = n; ni > 0; ni--)
        //l->RemoveFirst();
        //l->RemoveLast();
        //l->RemoveAt(ni);
        l->RemoveAt(3);

    cout << "ja removi" << std::endl;

    for(int i = 0; i < 10-n; i++)
        cout << l->At(i) << " ";

    cout << "finalizei";
}