#include <iostream>
#include <fstream>
#include <ostream>
#include <iterator>
#include "mysource.cpp"
using namespace std;
int main() {
    string x;
    cout<<"Whats your file? ";
    cin>>x;
    ifstream file;

    file.open(x);



    
    if(!file.is_open()){
        cout<<"FILE IS NOT OPEN";
    }
    else{
        int lineNumber = 1;
        LexItem tok;
        while ((tok = getNextToken(file, lineNumber)) != DONE && tok != ERR)
        {   
            cout << tok << endl;
        }
        cout << tok << endl;
       
    }
    file.close();



    return 0;
}
