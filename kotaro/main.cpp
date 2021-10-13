#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <bitset>

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
        return "";
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

void calculateRegister(int registerValue);

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

//Calculates the hex value into its respective string
string calculateRegisterNewValue(int registerValue) {
    stringstream ss3;
    ss3 << setfill('0') << setw(4) << hex << registerValue;
    string result = ss3.str();
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

//TODO REMOVE POST mabye
string GetBinaryStringFromHexString (string sHex)
{
    string hexToBinary = "";
    for (int i = 0; i < sHex.length (); ++i)
    {
        switch (sHex [i])
        {
            case '0': hexToBinary.append ("0000"); break;
            case '1': hexToBinary.append ("0001"); break;
            case '2': hexToBinary.append ("0010"); break;
            case '3': hexToBinary.append ("0011"); break;
            case '4': hexToBinary.append ("0100"); break;
            case '5': hexToBinary.append ("0101"); break;
            case '6': hexToBinary.append ("0110"); break;
            case '7': hexToBinary.append ("0111"); break;
            case '8': hexToBinary.append ("1000"); break;
            case '9': hexToBinary.append ("1001"); break;
            case 'A': hexToBinary.append ("1010"); break;
            case 'B': hexToBinary.append ("1011"); break;
            case 'C': hexToBinary.append ("1100"); break;
            case 'D': hexToBinary.append ("1101"); break;
            case 'E': hexToBinary.append ("1110"); break;
            case 'F': hexToBinary.append ("1111"); break;
        }
    }
    return hexToBinary;
}

//TODO REMOVE POST mabye
string GetHexStringFromBinaryString (string sBin)
{
    int n = stoi(sBin, 0, 2);
    stringstream ss;
    ss<< hex << n;
    string hex = ss.str();
    return hex;
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

    //Pushes the object code to the end
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //New additions
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Setting the registers
    string register1;
    register1 = objectCode.at(2);
    string register2;
    register2 = objectCode.at(3);

    //Checks the first register
    string opInst = opcodeTable(sortedAndBinarySTR.substr(0, 6));
    if (opInst.compare("CLEAR") == 0 || opInst.compare("SVC") == 0 || opInst.compare("TIXR") == 0) {           //  CLEAR, SVC, TIXR
        temp.append(registers(register1));

    } else if(opInst.compare("SHIFTL") == 0 || opInst.compare("SHIFTR") == 0){                                    // SHIFTL SHIFTR
        stringstream ss5;
        int regis2;
        ss5 << reg.getValue(registers(register2));
        ss5 >> hex >> regis2;

        temp.append(registers(register1) + ", ");
        temp.append(to_string(regis2));
    }else {                                                                                                             // ADDR, COMPR, DIVR, MULR, RMO, SUBR
        temp.append(registers(register1) + ", ");                                                                   //Pushes on the value of what MNEMONIC R1 is
        temp.append(registers(register2));
    }
    buffer.push_back(temp);
    string instruction = buffer.at(2);

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //New additions
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Register calculations
    string contentsOfReg1 = reg.getValue(registers(register1));
    string contentsOfReg2 = reg.getValue(registers(register2));

    stringstream ss1;
    stringstream ss2;

    int reg1;
    int reg2;

    ss1 << contentsOfReg1;
    ss1 >> hex >> reg1;

    ss2 << contentsOfReg2;
    ss2 >> hex >> reg2;

    // ADDR r1,r2     r2 = (r2) + (r2)
    if(instruction.compare("ADDR") == 0){
        reg2 = reg2 + reg1;
        reg.setValue(registers(register2), calculateRegisterNewValue(reg2));
    }

    //CLEAR r1     r1 <-- 0
    if(instruction.compare("CLEAR") == 0){
        reg1 = 0;
        reg.setValue(registers(register1), calculateRegisterNewValue(reg1));
    }

    //COMPR r1,r2   (r1) : (r2)

    //DIVR r1,r2    (r2) <-- (r2)/(r1)
    if(instruction.compare("DIVR") == 0){
        reg2 = reg2 / reg1;
        reg.setValue(registers(register2), calculateRegisterNewValue(reg2));
    }

    //MULR r1,r2    r2 <-- (r2) * (r1)
    if(instruction.compare("MULR") == 0){
        reg2 = reg2 * reg1;
        reg.setValue(registers(register2), calculateRegisterNewValue(reg2));
    }

    //RMO r1,r2     r2 <-- (r1)
    if(instruction.compare("RMO") == 0){
        reg2 = reg1;
        reg.setValue(registers(register2), calculateRegisterNewValue(reg2));
    }

    // SHIFTL r1,n   r1 <-- (r1); left circ shift n
    // left circular shift n bits. [for assembled instruction, r2 is n-1]
    // ASSUMPTION R2 is N
    if(instruction.compare("SHIFTL") == 0){
        string binaryReg1 = GetBinaryStringFromHexString(reg.getValue(registers(register1)));       //Contains the binary of R1
        int n = stoi(reg.getValue(registers(register2)), 0, 16);                         //Contains the n of how much R2 is

        for(int i = 0; i < n; i++){                                                                 //Function that appends the 0s to the right
            binaryReg1.append("0");
        }

        int lengthPost = binaryReg1.length();
        binaryReg1 = binaryReg1.substr(n, lengthPost);
        cout<<binaryReg1<<endl;
        reg.setValue(registers(register1), GetHexStringFromBinaryString(binaryReg1));               //Sends the hex converted number
    }

    //SHIFTR r1,n   r1 <-- (r1); right shift n
    //r1 ← (r1); right shift n bits with vacated bit positions set equal to leftmost bit of (r1) [for assembled instruction, r2 is n-1]
    if(instruction.compare("SHIFTR") == 0){
        string binaryReg1 = GetBinaryStringFromHexString(reg.getValue(registers(register1)));       //Contains the binary of R1
        int n = stoi(reg.getValue(registers(register2)), 0, 16);                         //Contains the n of how much R2 is
        string temp = "";
        for(int i = 0; i < n; i++){                                                                 //Function that appends the 0s to the right
            temp.append("0");
        }

        temp.append(binaryReg1);                                                                    //Appends it after new 0's have been inserted

        int lengthPost = binaryReg1.length();
        binaryReg1 = binaryReg1.substr(0, lengthPost - n);
        reg.setValue(registers(register1), GetHexStringFromBinaryString(binaryReg1));
    }

    //SUBR r1, r2   r2 <-- (r2) - (r1)
    if(instruction.compare("SUBR") == 0){
        reg2 = reg2 - reg1;
        string result = calculateRegisterNewValue(reg2);

        //This gets rid of the extra FFFF in the front
        if(reg2 < 0) {
            result = result.substr(4,8);
        }
        reg.setValue(registers(register2), result);
    }

    //SVC n         Generate SVC interupt

    //TIXR r1       X <-- (X) + 1; (X) : (r1)
    if(instruction.compare("TIXR") == 0){
        stringstream ss4;
        int regXI;

        ss4 << reg.getValue("X");
        ss4 >> hex >> regXI;

        regXI = regXI + 1;
        reg.setValue("X", calculateRegisterNewValue(regXI));
    }

    return buffer;
}

int main() {
    reg.setValue("A", "0010");
    reg.setValue("X", "0008");
    //vector<string> test = format2("0000", "100100000000001", "TEST", "9001"); //ADDR
    //vector<string> test = format2("0000", "101101", "TEST", "B401"); //CLEAR
    //vector<string> test = format2("0000", "100111", "TEST", "9C01"); //DIVR
    //vector<string> test = format2("0000", "100110", "TEST", "9801"); //MULR
    //vector<string> test = format2("0000", "101011", "TEST", "AC01"); //RMO

    //vector<string> test = format2("0000", "101001000000001", "TEST", "A401"); //SHIFTL

    //TODO this one returns 0 since all bits are shifted off, should we have it remain as 0?
    //vector<string> test = format2("0000", "101010000000001", "TEST", "A801"); //SHIFTR
    //vector<string> test = format2("0000", "100101", "TEST", "9401"); //SUBR
    vector<string> test = format2("0000", "101110", "TEST", "B801"); //TIXR
    //cout << reg.getValue("A") << endl;      //This is register 1
    //cout << reg.getValue("X") << endl;      //This is register 2
    for(int i = 0; i < test.at(0).size(); i++){
        cout<< test.at(i) << endl;
    }

}
