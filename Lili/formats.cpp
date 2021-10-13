/**
 * Students involve: (Name, account, Red ID)
     * Kotaro Ueoka, cssc1947, (RedID 821442616)
     * Liliana Guerrero, cssc1948, (RedID 821798582)
     * Marie Duffy, cssc1949, (RedID 821505237)
     * Kyle McLain Kane, cssc1950, (RedID 820003555)
 * Class: CS 530, Spring 2020
 * Assignment information: Assignment #2, XE Disassembler
 * Filename: formats.cpp
 */

#include "formats.h"


string indr = "10";
string immd = "01";
bool lTorg = false;

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

    string getValue(string regVal) {
        if (regVal.compare("A") == 0) {
            return regA;
        }
        if (regVal.compare("X") == 0) {
            return regX;
        }
        if (regVal.compare("L") == 0) {
            return regL;
        }
        if (regVal.compare("B") == 0) {
            return regB;
        }
        if (regVal.compare("S") == 0) {
            return regS;
        }
        if (regVal.compare("T") == 0) {
            return regT;
        }
        if (regVal.compare("F") == 0) {
            return regF;
        }
        if (regVal.compare("PC") == 0) {
            return regPC;
        }
        if (regVal.compare("SW") == 0) {
            return regSW;
        }
        return "";
    }

    void setValue(string reg, string newVal) {
        if (reg.compare("A") == 0) {
            regA = newVal;
        }
        if (reg.compare("X") == 0) {
            regX = newVal;
        }
        if (reg.compare("L") == 0) {
            regL = newVal;
        }
        if (reg.compare("B") == 0) {
            regB = newVal;
        }
        if (reg.compare("S") == 0) {
            regS = newVal;
        }
        if (reg.compare("T") == 0) {
            regT = newVal;
        }
        if (reg.compare("F") == 0) {
            regF = newVal;
        }
        if (reg.compare("PC") == 0) {
            regPC = newVal;
        }
        if (reg.compare("SW") == 0) {
            regSW = newVal;
        }
    }

    registersFormat() {
        regA = "0000";
        regX = "0000";
        regL = "0000";
        regB = "0000";
        regS = "0000";
        regT = "0000";
        regF = "0000";
        regPC = "0000";
        regSW = "0000";
    }
};

registersFormat reg;


string GetBinaryStringFromHexString(string sHex) {
    string hexToBinary = "";
    for (size_t i = 0; i < sHex.length(); ++i) {
        stringstream toBinary;
        toBinary << hex << sHex[i];
        unsigned n;
        toBinary >> n;
        bitset<4> b(n);
        hexToBinary.append(b.to_string());


        if(i == sHex.length() -1){
            break;
        }
    }
    return hexToBinary;

}

string GetHexStringFromBinaryString(string sBin) {
    int n = stoi(sBin, 0, 2);
    stringstream ss;
    ss << hex << n;
    string hex = ss.str();
    return hex;
}

int hexToDec (string hexStr){
    stringstream str;
    str << hexStr;
    int intVal;
    str >> hex >> intVal;
    return  intVal;
}

//These formats will need <ADDRESS, LABEL, INSTRUCTION/BLANK, OPERAND>
vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode) {
    //opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary to call on the opcode table
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line
    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(opcodeTable(sortedAndBinarySTR.substr(0, 6)));                                    //Pushes the opcodeTableBinary
    buffer.push_back("");                                                                                               //Pushes empty space for no operand
    buffer.push_back(objectCode);                                                                                       //Pushes the object code to the end
    return buffer;
}

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

//Calculates the hex value into its respective string of 4 bits
string setFill (int value) {
    stringstream ss;
    ss << setfill('0') << setw(4) << hex << value;
    string result = ss.str();
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
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
        int regis2 = hexToDec(reg.getValue(registers(register2)));

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

    int reg1 = hexToDec(contentsOfReg1);
    int reg2 = hexToDec(contentsOfReg2);

    // ADDR r1,r2     r2 = (r2) + (r2)
    if(instruction.compare("ADDR") == 0){
        reg2 = reg2 + reg1;
        reg.setValue(registers(register2), setFill(reg2));
    }

    //CLEAR r1     r1 <-- 0
    if(instruction.compare("CLEAR") == 0){
        reg1 = 0;
        reg.setValue(registers(register1), setFill(reg1));
    }

    //COMPR r1,r2   (r1) : (r2)

    //DIVR r1,r2    (r2) <-- (r2)/(r1)
    if(instruction.compare("DIVR") == 0){
        reg2 = reg2 / reg1;
        reg.setValue(registers(register2), setFill(reg2));
    }

    //MULR r1,r2    r2 <-- (r2) * (r1)
    if(instruction.compare("MULR") == 0){
        reg2 = reg2 * reg1;
        reg.setValue(registers(register2), setFill(reg2));
    }

    //RMO r1,r2     r2 <-- (r1)
    if(instruction.compare("RMO") == 0){
        reg2 = reg1;
        reg.setValue(registers(register2), setFill(reg2));
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
        string result = setFill(reg2);

        //This gets rid of the extra FFFF in the front
        if(reg2 < 0) {
            result = result.substr(4,8);
        }
        reg.setValue(registers(register2), result);
    }

    //SVC n         Generate SVC interupt

    //TIXR r1       X <-- (X) + 1; (X) : (r1)
    if(instruction.compare("TIXR") == 0){
        int regXI = hexToDec(reg.getValue("X"));

        regXI = regXI + 1;
        reg.setValue("X", setFill(regXI));
    }

    buffer.push_back(objectCode);
    return buffer;
}

string twoComplement(char input) {
    // empty map container
    map<char, string> opcodeTable;
    opcodeTable.insert(pair<char, string>('0', "F"));
    opcodeTable.insert(pair<char, string>('1', "E"));
    opcodeTable.insert(pair<char, string>('2', "D"));
    opcodeTable.insert(pair<char, string>('3', "C"));
    opcodeTable.insert(pair<char, string>('4', "B"));
    opcodeTable.insert(pair<char, string>('5', "A"));
    opcodeTable.insert(pair<char, string>('6', "9"));
    opcodeTable.insert(pair<char, string>('7', "8"));
    opcodeTable.insert(pair<char, string>('8', "7"));
    opcodeTable.insert(pair<char, string>('9', "6"));
    opcodeTable.insert(pair<char, string>('A', "5"));
    opcodeTable.insert(pair<char, string>('B', "4"));
    opcodeTable.insert(pair<char, string>('C', "3"));
    opcodeTable.insert(pair<char, string>('D', "2"));
    opcodeTable.insert(pair<char, string>('E', "1"));
    opcodeTable.insert(pair<char, string>('F', "0"));

    return opcodeTable.at(input);
}

string calcAddr (string one, string two, int index) {
    int value1 = hexToDec(one);
    int value2 = hexToDec(two);
    int total;

    string twosComp = GetBinaryStringFromHexString(one);
    char c = twosComp.at(0);
    if(c == '1'){
        // 2's complement calculation of TA
        if (one.at(0) == 'F' || one.at(0) == 'E' || one.at(0) == 'D' || one.at(0) == 'C' ||
            one.at(0) == 'B' || one.at(0) == 'A' || one.at(0) == '9' || one.at(0) == '8') {
            string newString;
            for (size_t i = 0; i < one.length(); i++) {
                newString.append(twoComplement(one.at(i)));
            }
            value1 = hexToDec(newString) + 1;
            total = value2 - value1;
        }
    } else {
        total = value1 + value2;
    }

    if(index == 1){
        int value = hexToDec(reg.getValue("X"));
        int newTotal = total + value;
        return setFill(newTotal);
    }
    else {
        return setFill(total);
    }

}

void findReg(string opcode, string hex, int format, string operand, vector<string> symTable, string nextAddr, string binary) {

    //length of the hex object code
    int size = hex.length() / 2;
    int startSub = size;

    string find = opcode;
    string symAddr;

    //passIndex value represents the X flag (indexed)
    int passIndex = 0;
    if(binary.at(8)== '1') {
        passIndex = 1;
    }

    if (operand.compare("") == 0) {                                                                                  //means there is no symbol (i.e. LDA #5)
        format = 4;                                                                                                     //even if format = 3, it will behave the same as 4 in this case
    } else {                                                                                                            //there is a symbol, so calculate its address (i.e. TABLE = 1791)
        symAddr = calcAddr(hex.substr(startSub, size), nextAddr, passIndex);
    }

    //A register
    if (find.compare("LDA") == 0) {
        if (format == 4) {
            reg.setValue("A", hex.substr(startSub, size));
        } else {                                                                                                        //store the symbol's address into the register
            reg.setValue("A",symAddr);
        }
    }
    //B register
    if (find.compare("LDB") == 0) {
        if (format == 4) {
            reg.setValue("B", hex.substr(startSub, size));
        } else {
            reg.setValue("B",symAddr);
        }
        //base = hex.substr(startSub, size);
        //reg.setValue("B", base);
    }
    //F register
    if (find.compare("LDF") == 0) {
        if (format == 4) {
            reg.setValue("F", hex.substr(startSub, size));
        }
        else {
            reg.setValue("F",symAddr);
        }
    }
    //L register
    if (find.compare("LDL") == 0) {
        if (format == 4) {
            reg.setValue("L", hex.substr(startSub, size));
        }
        else {
            reg.setValue("L",symAddr);
        }
    }
    //X register
    if (find.compare("LDX") == 0) {
        if (format == 4) {
            reg.setValue("X", hex.substr(startSub, size));
        }
        else {
            reg.setValue("X",symAddr);
        }
    }
    //S register
    if (find.compare("LDS") == 0) {
        if (format == 4) {
            reg.setValue("S", hex.substr(startSub, size));
        }
        else {
            reg.setValue("S",symAddr);
        }

    }
    //T register
    if (find.compare("LDT") == 0) {
        if (format == 4) {
            reg.setValue("T", hex.substr(startSub, size));
        }
        else {
            reg.setValue("T",symAddr);
        }

    }
}

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<string> litTable) {
    vector<string> line;
    char b = '1';
    char p = '1';
    string pc;
    string operand;
    string copyOperand;

    line.push_back(address);
    line.push_back(label);
    line.push_back(opcodeTable(binary.substr(0, 6)));
    pc = calcAddr(address, "3", 0);

    // Completed: INDIRECT
    if (binary.substr(6, 2).compare(indr) == 0) {
        operand.append(" @");
        //Complete: INDIRECT & BASE
        if (binary.at(9) == b) {
            copyOperand = getLabel(symTable, calcAddr(hexVal.substr(3, 3), reg.getValue("B"), 0));
            operand.append(copyOperand);
        }
            // Completed: Indirect& PC
        else if (binary.at(10) == p) {
            copyOperand = getLabel(symTable, calcAddr(hexVal.substr(3, 3), pc, 0));
            operand.append(copyOperand);
        }
    }
        //IMMEDIATE
    else if (binary.substr(6, 2).compare(immd) == 0) {
        operand.append(" #");
        // Complete: IMMEDIATE & BASE
        if (binary.at(9) == b) {
            copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3, 3), reg.getValue("B"), 0)));
            operand.append(copyOperand);
        }
            // Complete: IMMEDIATE & PC
        else if (binary.at(10) == p) {
            copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3, 3), pc, 0)));
            operand.append(copyOperand);
        }
            // COMPLETED: IMMEDIATE & DIRECT
        else { //come back later
            int intVal = hexToDec(hexVal.substr(3,3));
            operand.append(to_string(intVal));
        }
    } else  { //SIMPLE
        // COMPLETED: Simple & PC Relative
        if (binary.at(10) == p) {
            if(binary.at(8) == '1'){
                copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3, 3), pc, 1)));
                operand.append(copyOperand);
                operand.append(",X");
            }else {
                copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3,3), pc, 0)));
                operand.append(copyOperand);
            }
        }
            // Completed: SIMPLE & BASE
        else if (binary.at(9) == b) {
            if(binary.at(8) == '1'){
                copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3, 3), reg.getValue("B"), 1)));
                operand.append(copyOperand);
                operand.append(",X");
            }else {
                copyOperand = (getLabel(symTable, calcAddr(hexVal.substr(3, 3), reg.getValue("B"), 0)));
                operand.append(copyOperand);
            }
        }
    }

    // TODO: LITERALS
    // Check if literal address == current address
    // If match found append literal to operand
    if(getLiteralAtAddress(litTable, address).compare("")!=0){
        for(string line : litTable){
            if(line.substr(26,4).compare(address) == 0) {
                string temp = line.substr(8,7);
                temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
                lTorg = true;
                operand.append(temp);
            }
        }
    }


    findReg(opcodeTable(binary.substr(0,6)), hexVal, 3, copyOperand, symTable, pc, binary);
    line.push_back(operand);
    line.push_back(hexVal);
    return line;
}

vector<string> format4(string address, string binary, string label, string hexVal, vector<string> symTable) {

    vector<string> line;
    line.push_back(address);
    line.push_back(label);
    string operand; //operand without @, #, or ,X included
    string currOp; //formatted operand

    //check opcode table for the instruction
    string opCode = "+";
    opCode.append(opcodeTable(binary.substr(0, 6)));
    line.push_back(opCode);                                                                                             //put the opcode into the vector

    string pc;
    pc = calcAddr(address, "4", 0);
    //put in operand and any necessary addressing identifiers
    if (binary.substr(6,2).compare(immd) == 0) {                                                            // IMMEDIATE ADDRESSING MODE
        currOp.append("#");
        operand = getLabel(symTable, hexVal.substr(4, 4));
        if(operand.compare("") != 0) {                                                                               //indicates that there is an operand for this line
            currOp.append(operand);
        }
        else {                                                                                                          //no symbol for this line, so it immediately addresses an int value
            // use stringstream to convert the hex value to decimal value
            currOp.append(to_string(hexToDec(hexVal.substr(3,5))));
        }

    }
    else if (binary.substr(6,2).compare(indr) == 0) {                                                           // INDIRECT ADDRESSING MODE
        currOp.append("@");
        operand = getLabel(symTable, hexVal.substr(4, 4));
        currOp.append(operand);
    }
    else {                                                                                                              // SIMPLE ADDRESSING MODE
        if(binary.at(8) == '1') {                                                                                    // INDEXED
            operand = getLabel(symTable,calcAddr(hexVal.substr(4,4), "0", 1));
            currOp.append(operand);
            currOp.append(",X");
        }
        else {
            operand = getLabel(symTable, hexVal.substr(4, 4));
            currOp.append(operand);
        }

    }

    findReg(opcodeTable(binary.substr(0, 6)), hexVal, 4, operand, symTable, pc, binary);
    line.push_back(currOp); //push the operand onto the vector
    line.push_back(hexVal);  //push the object code onto the vector
    return line;
}

vector<vector<string> > masterFormat(vector<vector<string> > total, vector<string> address, vector<string> sortedByFormatSTR,vector<string> sortedAndBinarySTR, vector<string> labels, vector<string> symTable,vector<string> allAddresses, vector<string> literals, vector<string> litTable) {

    //This will loop through the format sorted vector and then convert by calling each necessary function
    //Passes the string at that line-
    for (size_t i = 0; i < sortedByFormatSTR.size(); i++) {

        bool isFormat = true;

        for (size_t k = 0; k < literals.size(); k++) {
            if (sortedByFormatSTR.at(i).compare(literals.at(k)) == 0) {
                isFormat = false;
            }
        }

        if (isFormat == true) {

            if (sortedByFormatSTR[i].length() ==2) {                                                                         //Checks for format 1
                total.push_back(format1(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i]));

            } else if (sortedByFormatSTR[i].length() ==4) {                                                                         //Checks for format 2
                total.push_back(format2(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i]));        //This pushes the format 2 element vector

            } else if (sortedByFormatSTR[i].length() == 6) {
                total.push_back(format3(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i], symTable, allAddresses, literals, litTable));

            } else if (sortedByFormatSTR[i].length() == 8) {                                                                         //Checks for format 2
                //  total.push_back(format4(address[i], sortedAndBinarySTR[i], labels[i]), sortedByFormatSTR[i], symTable));
                total.push_back(format4(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i], symTable));

                //This pushes the format 4 element vector
            } else {
                cout << "ERROR: Format not found" << endl;
            }
        }



//        for(string lit : litTable){
//            if(lit.substr(26,4).compare(address.at(i))==0){
//
//            }
//        }



    }


    return total;
}

vector<vector<string> > appendLiteral(vector<vector<string> > total, vector<string> litTable, vector<string> symTable,vector<string> literals){
    bool found = false;
    vector<vector<string> > tempVector;

    for(string litTableLine : litTable){
        for(size_t i=0; i<total.size();i++){
            if(litTableLine.substr(26,4).compare(total.at(i).at(0))==0){
                found = true;
            }
        }
        if(!found) {
            found = false;
            vector<string> temp;
            for(vector<string> line : total){
                stringstream ss;
                int size = line.at(4).size()/2;
                ss << hex << size;
                string pc = calcAddr(line.at(0), ss.str(), 0);
                if(pc.compare(litTableLine.substr(26,4))==0){
                    temp.push_back(litTableLine.substr(26,4));
                    temp.push_back(getLabel(symTable, litTableLine.substr(26,4)));
                    temp.push_back("BYTE");
                    string operand;
                    operand = litTableLine.substr(7,8);
                    operand.erase(remove_if(operand.begin(), operand.end(), ::isspace), operand.end());
                    temp.push_back(operand);

                    if(litTableLine.at(9) == 'C') {
                        string dat = litTableLine.substr(11, litTableLine.at(19) - '0');

                        ostringstream os;
                        for (size_t j = 0; j < dat.length(); j++) {  // Convert current LABEL to HEX and push back as Object Code
                            os << hex << uppercase << (int) dat[j];
                        }
                        string hexdat = os.str();
                        temp.push_back(hexdat);
                    } else {
                        temp.push_back(litTableLine.substr(11, litTableLine.at(19)-'0'));
                    }
                }
            }
            total.push_back(temp);
        }
    }


    return total;
}