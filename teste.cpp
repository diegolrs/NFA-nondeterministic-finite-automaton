#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]){
    string symbols;
 
    cout << "Digite os elementos da cadeia: " << endl;
    getline(cin, symbols);

    /*for (int i = 0; i < symbols.size(); i++){
        cout << "ola" << endl;
    }*/
    

    for(int i = 0; i < symbols.size(); ++i) {
        
        //string symbol;
        //symbol.push_back(symbols[i]);

        string symbol(1, symbols[i]);
        cout << symbol << endl;

    }
    return 0;
}
