#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;


string opcodeTable (string basicString){
    // empty map container
    map<string, string> opcodeTable;

    //Filling the opcodeTableBinary table with Key(opcodeTableBinary number (first 6 bits of their binary form)) and Value (opcodeTableBinary instruction)
    opcodeTable.insert(pair<string, string>("000000", "LDA"));
    opcodeTable.insert(pair<string, string>("000110", "ADD"));
    opcodeTable.insert(pair<string, string>("010110", "ADDF"));
    opcodeTable.insert(pair<string, string>("100100", "ADDR"));

    opcodeTable.insert(pair<string, string>("010000", "AND"));
    opcodeTable.insert(pair<string, string>("101101", "CLEAR"));
    opcodeTable.insert(pair<string, string>("001010", "COMP"));
    opcodeTable.insert(pair<string, string>("100010", "COMPF"));

    opcodeTable.insert(pair<string, string>("101000", "COMPR"));
    opcodeTable.insert(pair<string, string>("001001", "DIV"));
    opcodeTable.insert(pair<string, string>("011001", "DIVF"));
    opcodeTable.insert(pair<string, string>("100111", "DIVR"));

    opcodeTable.insert(pair<string, string>("110001", "FIX"));
    opcodeTable.insert(pair<string, string>("110000", "FLOAT"));
    opcodeTable.insert(pair<string, string>("111101", "HIO"));
    opcodeTable.insert(pair<string, string>("001111", "J"));

    opcodeTable.insert(pair<string, string>("001100", "JEQ"));
    opcodeTable.insert(pair<string, string>("001101", "JGT"));
    opcodeTable.insert(pair<string, string>("001110", "JLT"));
    opcodeTable.insert(pair<string, string>("010010", "JSUB"));

    opcodeTable.insert(pair<string, string>("011010", "LDB"));
    opcodeTable.insert(pair<string, string>("010100", "LDCH"));
    opcodeTable.insert(pair<string, string>("011100", "LDF"));
    opcodeTable.insert(pair<string, string>("000010", "LDL"));

    opcodeTable.insert(pair<string, string>("011011", "LDS"));
    opcodeTable.insert(pair<string, string>("011101", "LDT"));
    opcodeTable.insert(pair<string, string>("000001", "LDX"));
    opcodeTable.insert(pair<string, string>("110100", "LPS"));

    opcodeTable.insert(pair<string, string>("001000", "MUL"));
    opcodeTable.insert(pair<string, string>("011000", "MULF"));
    opcodeTable.insert(pair<string, string>("100110", "MULR"));
    opcodeTable.insert(pair<string, string>("110010", "NORM"));

    opcodeTable.insert(pair<string, string>("010001", "OR"));
    opcodeTable.insert(pair<string, string>("110110", "RD"));
    opcodeTable.insert(pair<string, string>("101011", "RMO"));
    opcodeTable.insert(pair<string, string>("010011", "RSUB"));

    opcodeTable.insert(pair<string, string>("101001", "SHIFTL"));
    opcodeTable.insert(pair<string, string>("101010", "SHIFTR"));
    opcodeTable.insert(pair<string, string>("111100", "SIO"));
    opcodeTable.insert(pair<string, string>("111011", "SSK"));

    opcodeTable.insert(pair<string, string>("000011", "STA"));
    opcodeTable.insert(pair<string, string>("011110", "STB"));
    opcodeTable.insert(pair<string, string>("010101", "STCH"));
    opcodeTable.insert(pair<string, string>("100000", "STF"));

    opcodeTable.insert(pair<string, string>("110101", "STI"));
    opcodeTable.insert(pair<string, string>("000101", "STL"));
    opcodeTable.insert(pair<string, string>("011111", "STS"));
    opcodeTable.insert(pair<string, string>("111010", "STSW"));

    opcodeTable.insert(pair<string, string>("100001", "STT"));
    opcodeTable.insert(pair<string, string>("000100", "STX"));
    opcodeTable.insert(pair<string, string>("000111", "SUB"));
    opcodeTable.insert(pair<string, string>("010111", "SUBF"));

    opcodeTable.insert(pair<string, string>("100101", "SUBR"));
    opcodeTable.insert(pair<string, string>("101100", "SVC"));
    opcodeTable.insert(pair<string, string>("111000", "TD"));
    opcodeTable.insert(pair<string, string>("111110", "TIO"));

    opcodeTable.insert(pair<string, string>("001011", "TIX"));
    opcodeTable.insert(pair<string, string>("101110", "TIXR"));
    opcodeTable.insert(pair<string, string>("110111", "WD"));

    return opcodeTable.at(basicString);                                  //Returns a string of what the opcodeTableBinary instruction is
}

class registersFormat {
private:
    string regA;
    string regX;
    string regL;
    string regB;
    string regS;
    string regT;
    string regF;
    string regPC;
    string regSW;
public:
    string getValue(string regVal){
        if(regVal.compare("A") == 0){
            return regA;
        }
        if(regVal.compare("X") == 0){
            return regX;
        }
        if(regVal.compare("L") == 0){
            return regL;
        }
        if(regVal.compare("B") == 0){
            return regB;
        }
        if(regVal.compare("S") == 0){
            return regS;
        }
        if(regVal.compare("T") == 0){
            return regT;
        }
        if(regVal.compare("F") == 0){
            return regF;
        }
        if(regVal.compare("PC") == 0){
            return regPC;
        }
        if(regVal.compare("SW") == 0){
            return regSW;
        }
    }

    void setValue(string reg, string newVal){
        if(reg.compare("A") == 0){
            regA = newVal;
        }
        if(reg.compare("X") == 0){
            regX = newVal;
        }
        if(reg.compare("L") == 0){
            regL = newVal;
        }
        if(reg.compare("B") == 0){
            regB = newVal;
        }
        if(reg.compare("S") == 0){
            regS = newVal;
        }
        if(reg.compare("T") == 0){
            regT = newVal;
        }
        if(reg.compare("F") == 0){
            regF = newVal;
        }
        if(reg.compare("PC") == 0){
            regPC = newVal;
        }
        if(reg.compare("SW") == 0){
            regSW = newVal;
        }
    }
    registersFormat(){
        regA  = "0000";
        regX  = "0000";
        regL  = "0000";
        regB  = "0000";
        regS  = "0000";
        regT  = "0000";
        regF  = "0000";
        regPC = "0000";
        regSW = "0000";
    }
};

registersFormat reg;

string registers(string key) {                                                                                           //This is MNEMONIC and register map
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


vector<string> format2(string address, string sortedAndBinarySTR, string label, string objectCode) {
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line
    string temp;                                                                                                        //Stores the parameters for the R1, R2 part
    //opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary so we can utilize the opcode table
    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(opcodeTable(sortedAndBinarySTR.substr(0, 6)));                                    //Pushes the opcodeTableBinary
    //Next call on K,V pair for register table
    //Checks the first register
    string register1;                                                                                                   //Creates register 1
    register1 = objectCode.at(2);
    temp.append(registers(register1) + ",");                                                                       //Pushes on the value of what MNEMONIC R1 is

    //Checks the second register
    string register2;                                                                                                   //Creates register 1
    register2 = objectCode.at(3);
    temp.append(registers(register2));                                                                                  //Pushes on the value of what MNEMONIC R2 is

    //Gives the opcode instruction
    string instruction = buffer.at(2);

    buffer.push_back(temp);                                                                                             //Pushes the operand onto our buffer
    buffer.push_back(objectCode);                                                                                       //Pushes the object code to the end


    string contentsOfReg1 = reg.getValue(registers(register1));
    string contentsOfReg2 = reg.getValue(registers(register2));

    stringstream ss1;
    stringstream ss2;
    stringstream ss3;

    int reg1;
    int reg2;

    ss1 << contentsOfReg1;
    ss1 >> hex >> reg1;

    ss2 << contentsOfReg2;
    ss2 >> hex >> reg2;

   // ADDR r1,r2     r2 = (r2) + (r2)
    if(instruction.compare("ADDR") == 0){
        reg2 = reg2 + reg1;
        ss3 << setfill('0') << setw(4) << hex << reg2;
        string result = ss3.str();
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        reg.setValue(registers(register2), result);
    }

    return buffer;
}

int main() {
    reg.setValue("A", "0015");
    reg.setValue("X", "0016");
    vector<string> test = format2("0000", "100100000000001", "TEST", "9001");
    cout << reg.getValue("X") << endl;
}

