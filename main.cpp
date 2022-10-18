#include <iostream>
#include <fstream>
#include <ostream>
#include <iterator>
#include "mysource.cpp"
using namespace std;
int main() {
    string file,word;
    ifstream  file2;
    cout<<"Whats your file?";  //later on change into inline arguments
    cin>> file;

    fstream myfile;

    myfile.open(file);
    int x=0;
    while(myfile >> word){
        LexItem myitem = id_or_kw(word,x);

        cout<<myitem.GetLexeme()<<" " <<myitem.GetToken()<<endl;
        x++;
    }
    cout<<x;





    return 0;
}
