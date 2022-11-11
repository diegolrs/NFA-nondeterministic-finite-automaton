#include <iostream>
#include <string>
#include "Utils/MyList.h"
#include "NFA_FileReader.h"

using namespace std;
using namespace NFA_FileReader;

const std::string FILE_ADDRESS = "../afn2.txt";

#include "Symbol.h"
int main()
{
    NFA_FileReader::ReadFile(FILE_ADDRESS);

    Symbol s = Symbol("batata");
    cout << s.GetValue();

    Symbol* s3;
    s3 = &s;

    cout << s3->GetValue();
}