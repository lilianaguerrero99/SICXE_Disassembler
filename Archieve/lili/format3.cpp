//code for format 3
#include <iostream>
#include <vector>
#include "opcodeTableBinary.h"
#include "master.cpp"
#include <sstream>
#include <bitset>

using namespace std;

string indr = "10";
string immd = "01";
string x,b,p = "1";

//vector<string> format3 (vector<string>sort, vector<string>binsort){
vector<string> format3(){
    vector<string>v;
    opcodeTableBinary op;
    string example = "001011110010000000001010"; //2F200A
    string example2 = "2F200A";
    v.push_back(op.opTable((example.substr(0, 6))));
    if(example.substr(6,2).compare(indr)==0){
        v.push_back(" @");
    }
    else if(example.substr(6,2).compare(immd)==0){
        v.push_back(" #");
    }
    else{
        v.push_back("simple");
        if(example.substr(8,1).compare(x) == 0){
            v.push_back("index");
        }
    }
    if(example.substr(9,1).compare(b) == 0){
        v.push_back("base");
    }
    else if(example.substr(10,1).compare(p) == 0){
        v.push_back("pc");
    }
    else{
        v.push_back("direct");
    }

    stringstream str;
    string s1 = example2.substr(3,3);
    str << s1;
    int value;
    str >> hex >> value;
    cout<< value << endl;

    stringstream str1;
    string s2 = "013";
    str1 << s2;
    int value1;
    str1 >> hex >> value1;
    cout<< value1 << endl;

    int addr = value + value1;
    //cout<< uppercase << hex << addr << endl;
    stringstream stream;
    stream<< hex << addr;
    string result("00" + stream.str());
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    cout<< result<<endl;

   cout<<getLabel(getSymTable("sample.sym"), result)<<endl;
    //getSymTable = 00A + address (i + 1)
    v.push_back(getLabel(getSymTable("sample.sym"), result));
    cout<<" "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v.at(i)<<endl;
    }
    return v;
}

//symtable means it is direct addressing

int main(){

    vector<string>hi = format3();
}