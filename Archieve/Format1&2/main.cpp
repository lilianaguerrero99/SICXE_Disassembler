#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "opcodeTableBinary.h"

using namespace std;

//These formats will need <ADDRESS, LABEL, INSTRUCTION/BLANK, OPERAND>
vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode){
    opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary to call on the opcode table
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line

    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(op.opTable(sortedAndBinarySTR.substr(0,6)));                                    //Pushes the opcodeTableBinary
    buffer.push_back("");                                                                                               //Pushes empty space for no operand
    buffer.push_back(objectCode);                                                                                       //Pushes the object code to the end

    return buffer;
}

string registers(string key){                                                                                           //This is MNEMONIC and register map
    // empty map container
    map<string, string> registerMNEMONIC;

    //Filling the register table
    registerMNEMONIC.insert(pair<string, string>("0", "A"));
    registerMNEMONIC.insert(pair<string, string>("1", "X"));
    registerMNEMONIC.insert(pair<string, string>("2", "L"));
    registerMNEMONIC.insert(pair<string, string>("3", "B"));
    registerMNEMONIC.insert(pair<string, string>("4", "S"));
    registerMNEMONIC.insert(pair<string, string>("5", "T"));
    registerMNEMONIC.insert(pair<string, string>("6", "F"));
    registerMNEMONIC.insert(pair<string, string>("7", "F"));
    registerMNEMONIC.insert(pair<string, string>("8", "PC"));
    registerMNEMONIC.insert(pair<string, string>("9", "SW"));

    return registerMNEMONIC.at(key);                                                                                    //Returning the value at the wanted key
}

vector<string> format2(string address, string sortedAndBinarySTR, string label, string objectCode){
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line
    string temp;                                                                                                        //Stores the parameters for the R1, R2 part
    opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary so we can utilize the opcode table

    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(op.opTable(sortedAndBinarySTR.substr(0,6)));                                    //Pushes the opcodeTableBinary

    //Next call on K,V pair for register table

    //Checks the first register
    string register1;                                                                                                   //Creates register 1
    register1 = objectCode.at(2);
    temp.append(registers(register1) + ", ");                                                                       //Pushes on the value of what MNEMONIC R1 is

    //Checks the second register
    string register2;                                                                                                   //Creates register 1
    register2 = objectCode.at(3);
    temp.append(registers(register2));                                                                                  //Pushes on the value of what MNEMONIC R2 is

    buffer.push_back(temp);                                                                                             //Pushes the operand onto our buffer
    buffer.push_back(objectCode);                                                                                       //Pushes the object code to the end
    return buffer;
}


//Will return a vector of vectors containing each contents
vector<vector<string>> masterFormat(vector<string> address, vector<string> sortedByFormatSTR, vector<string> sortedAndBinarySTR, vector<string> addressSTR){
    vector<vector<string>> allLines;

    //This will loop through the format sorted vector and then convert by calling each necessary function
    //Passes the string at that line-
    for(int i = 0; i < sortedByFormatSTR.size(); i++){
        if(sortedByFormatSTR[i].length() == 2){                                                                         //Checks for format 1
            allLines.push_back(format1(address[i], sortedAndBinarySTR[i], addressSTR[i], sortedByFormatSTR[i]));
        }
        if(sortedByFormatSTR[i].length() == 4){                                                                         //Checks for format 2
            allLines.push_back(format2(address[i], sortedAndBinarySTR[i], addressSTR[i], sortedByFormatSTR[i]));        //This pushes the format 2 element vector
        }
    }
    return allLines;
}




int main() {
    vector<vector<string>> total;

    //TODO this way would need something to call the master to push the correct values on that line

    //Format 1 test
//    vector<string> allAddresses;                                                                                        //Will always have address
//    allAddresses.push_back("0000");
//    vector<string> sorted;                                                                                              //Will always have obj code
//    sorted.push_back("C4");
//    vector<string> binarySorted;                                                                                        //Will always have binary
//    binarySorted.push_back("11000100");
//
//    //Label
//    vector<string> stringAddresses;                                                                                     //Won't always have a label
//    stringAddresses.push_back("Test");

    //Format 2 test
    vector<string> allAddresses;                                                                                        //Will always have address
    allAddresses.push_back("0000");
    vector<string> sorted;                                                                                              //Will always have obj code
    sorted.push_back("9043");
    vector<string> binarySorted;                                                                                        //Will always have binary
    binarySorted.push_back("1001000001000011");

    //Label
    vector<string> stringAddresses;                                                                                     //Wont always have a label
    stringAddresses.push_back("Test");

    total = masterFormat(allAddresses, sorted, binarySorted, stringAddresses);                                          //Passing the addresses, the format sorted values, the binary format sorted, and the addresses strings
    for(int i = 0; i < total.at(0).size(); i++){
        cout<< total.at(0).at(i);
    }
    return 0;
}
