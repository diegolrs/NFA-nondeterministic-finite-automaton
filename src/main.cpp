#include <iostream>
#include <string>
#include "Utils/MyList.h"
#include "NFA_FileReader.h"

using namespace std;
using namespace NFA_FileReader;

const std::string FILE_ADDRESS = "../afn2.txt";

int main()
{
    NFA_FileReader::ReadFile(FILE_ADDRESS);
}