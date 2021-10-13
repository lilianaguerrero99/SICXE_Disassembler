#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string opTable(string opcode){
    
    // empty map container 
    map<string, string> opcodeTable; 

    //Filling the opcode table with Key(opcode number) and Value (opcode instruction)
    opcodeTable.insert(pair<string, string>("00", "LDA")); 
    opcodeTable.insert(pair<string, string>("18", "ADD")); 
    opcodeTable.insert(pair<string, string>("58", "ADDF")); 
    opcodeTable.insert(pair<string, string>("90", "ADDR")); 
    
    opcodeTable.insert(pair<string, string>("40", "AND")); 
    opcodeTable.insert(pair<string, string>("B4", "CLEAR")); 
    opcodeTable.insert(pair<string, string>("28", "COMP")); 
    opcodeTable.insert(pair<string, string>("88", "COMPF")); 

    opcodeTable.insert(pair<string, string>("A0", "COMPR")); 
    opcodeTable.insert(pair<string, string>("24", "DIV")); 
    opcodeTable.insert(pair<string, string>("64", "DIVF")); 
    opcodeTable.insert(pair<string, string>("9C", "DIVR")); 

    opcodeTable.insert(pair<string, string>("C4", "FIX")); 
    opcodeTable.insert(pair<string, string>("C0", "FLOAT")); 
    opcodeTable.insert(pair<string, string>("F4", "HIO")); 
    opcodeTable.insert(pair<string, string>("3C", "J")); 
    
    opcodeTable.insert(pair<string, string>("30", "JEQ")); 
    opcodeTable.insert(pair<string, string>("34", "JGT")); 
    opcodeTable.insert(pair<string, string>("38", "JLT")); 
    opcodeTable.insert(pair<string, string>("48", "JSUB")); 

    opcodeTable.insert(pair<string, string>("68", "LDB")); 
    opcodeTable.insert(pair<string, string>("50", "LDCH")); 
    opcodeTable.insert(pair<string, string>("70", "LDF")); 
    opcodeTable.insert(pair<string, string>("08", "LDL")); 

    opcodeTable.insert(pair<string, string>("6C", "LDS")); 
    opcodeTable.insert(pair<string, string>("74", "LDT")); 
    opcodeTable.insert(pair<string, string>("04", "LDX")); 
    opcodeTable.insert(pair<string, string>("D0", "LPS")); 
    
    opcodeTable.insert(pair<string, string>("20", "MUL")); 
    opcodeTable.insert(pair<string, string>("60", "MULF")); 
    opcodeTable.insert(pair<string, string>("98", "MULR")); 
    opcodeTable.insert(pair<string, string>("C8", "NORM")); 

    opcodeTable.insert(pair<string, string>("44", "OR")); 
    opcodeTable.insert(pair<string, string>("D8", "RD")); 
    opcodeTable.insert(pair<string, string>("AC", "RMO")); 
    opcodeTable.insert(pair<string, string>("4C", "RSUB")); 

    opcodeTable.insert(pair<string, string>("A4", "SHIFTL")); 
    opcodeTable.insert(pair<string, string>("A8", "SHIFTR")); 
    opcodeTable.insert(pair<string, string>("F0", "SIO")); 
    opcodeTable.insert(pair<string, string>("EC", "SSK")); 
    
    opcodeTable.insert(pair<string, string>("0C", "STA")); 
    opcodeTable.insert(pair<string, string>("78", "STB")); 
    opcodeTable.insert(pair<string, string>("54", "STCH")); 
    opcodeTable.insert(pair<string, string>("80", "STF")); 

    opcodeTable.insert(pair<string, string>("D4", "STI")); 
    opcodeTable.insert(pair<string, string>("14", "STL")); 
    opcodeTable.insert(pair<string, string>("7C", "STS")); 
    opcodeTable.insert(pair<string, string>("E8", "STSW")); 

    opcodeTable.insert(pair<string, string>("84", "STT")); 
    opcodeTable.insert(pair<string, string>("10", "STX")); 
    opcodeTable.insert(pair<string, string>("1C", "SUB")); 
    opcodeTable.insert(pair<string, string>("5C", "SUBF")); 

    opcodeTable.insert(pair<string, string>("94", "SUBR")); 
    opcodeTable.insert(pair<string, string>("B0", "SVC")); 
    opcodeTable.insert(pair<string, string>("E0", "TD")); 
    opcodeTable.insert(pair<string, string>("F8", "TIO")); 

    opcodeTable.insert(pair<string, string>("2C", "TIX")); 
    opcodeTable.insert(pair<string, string>("B8", "TIXR")); 
    opcodeTable.insert(pair<string, string>("DC", "WD")); 

    return opcodeTable.at(opcode);                                  //Returns a string of what the opcode instruction is
}

//Format 1 creator IN PROGRESS
string format1(string opcode){
    return opTable(opcode);
}

int main(){
    vector<string> formatInstruction;
    string test ="10";   
    formatInstruction.push_back(format1(test));     //This will push the string of the opcode instruction
    cout<< formatInstruction[0] << endl;            //Eventually this will be the array for the instructions
}