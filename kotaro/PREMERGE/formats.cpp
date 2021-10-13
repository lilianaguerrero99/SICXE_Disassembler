#include "formats.h"

string indr = "10";
string immd = "01";
string simp = "11";

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
    for (int i = 0; i < sHex.length(); ++i) {
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

//These formats will need <ADDRESS, LABEL, INSTRUCTION/BLANK, OPERAND>
vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode) {
    //opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary to call on the opcode table
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line

    buffer.push_back(
            address);                                                                                          //Pushes back the stored address
    buffer.push_back(
            label);                                                                                            //Pushes back the stored label
    buffer.push_back(opcodeTable(
            sortedAndBinarySTR.substr(0, 6)));                                    //Pushes the opcodeTableBinary
    buffer.push_back(
            "");                                                                                               //Pushes empty space for no operand
    buffer.push_back(
            objectCode);                                                                                       //Pushes the object code to the end

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



//Calculates the hex value into its respective string
string calculateRegisterNewValue(int registerValue) {
    stringstream ss3;
    ss3 << setfill('0') << setw(4) << hex << registerValue;
    string result = ss3.str();
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
    stringstream ss1;
    string s1 = one;
    ss1 << s1;
    int value1;
    ss1 >> hex >> value1;


    stringstream ss2;
    string s2 = two;
    ss2 << s2;
    int value2;
    ss2 >> hex >> value2;

    int total;
    string twosComp = GetBinaryStringFromHexString(s1);
    char c = twosComp.at(0);

    if(c == '1'){
        // 2's complement calculation of TA
        if (s1.at(0) == 'F' || s1.at(0) == 'E' || s1.at(0) == 'D' || s1.at(0) == 'C' ||
            s1.at(0) == 'B' || s1.at(0) == 'A' || s1.at(0) == '9' || s1.at(0) == '8') {
            string newString;
            for (int i = 0; i < s1.length(); i++) {
                newString.append(twoComplement(s1.at(i)));
            }
            stringstream ss1;
            ss1 << newString;
            ss1 >> hex >> value1;
            value1++;
            total = value2 - value1;
        }
    } else {
        total = value1 + value2;
    }
    stringstream str1;
    str1 << setfill('0') << setw(4) << hex << total;

    string result1 = str1.str();
    transform(result1.begin(), result1.end(), result1.begin(), ::toupper);

    if(index == 1){
        stringstream ss;
        string s = reg.getValue("X");
        ss << s;
        int value;
        ss >> hex >> value;

        int newTotal = total + value;
        stringstream str;
        str << setfill('0') << setw(4) << hex << newTotal;

        string result = str.str();
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    else {
        return result1;
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
    line.push_back(address);
    line.push_back(label);
    line.push_back(opcodeTable(binary.substr(0, 6)));

    char b = '1';
    char p = '1';
    char x = '1';

    string pc;
    pc = calcAddr(address, "3", 0);

    string operand;
    string copyOperand;
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
            stringstream str;
            int intVal;
            string hexString = hexVal.substr(3, 3);
            str << hexString;
            str >> hex >> intVal;
            operand.append(to_string(intVal));
        }
    } else if (binary.substr(6, 2).compare(simp) == 0) { //SIMPLE


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
                temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
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
            stringstream str;
            int intVal;
            string hexString = hexVal.substr(3, 5);
            str << hexString;
            str >> hex >> intVal;
            currOp.append(to_string(intVal));
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

    int j = 0; // KEEP TRACK OF SORTEDBYFORMATSTR
    for(int i=0; i<address.size();i++){
        bool isFormat = true;
        for(string declaration : DECLARATIONS){
            if(declaration.compare(address.at(i))==0){
                stringstream ss;
                stringstream ss1;
                int currAddress;
                int nextAddress;
                vector<string> temp;
                temp.push_back(address.at(i));
                temp.push_back("");

                if(i+1 < address.size()) {
                    ss << hex << address.at(i);
                    ss >> currAddress;
                    ss1 << hex << address.at(i + 1);
                    ss1 >> nextAddress;
                    int size = nextAddress - currAddress;

                    if(size%3==0){
                        stringstream ss2;
                        temp.push_back("RESW");
                        ss2 << hex <<  size / 3;
                        string add = ss2.str();
                        transform(add.begin(), add.end(), add.begin(), ::toupper);
                        temp.push_back(add);
                    } else {
                        stringstream ss2;
                        temp.push_back("RESB");
                        ss2 << size;
                        string add = ss2.str();
                        transform(add.begin(), add.end(), add.begin(), ::toupper);
                        temp.push_back(add);
                    }
                    temp.push_back("");

                }


                temp.push_back("");
                total.push_back(temp);
                isFormat = false;

            }
        }
        if(isFormat) {
            for (int k = 0; k < literals.size(); k++) {

                if (sortedByFormatSTR.at(j).compare(literals.at(k)) == 0 && isFormat) {

                    isFormat = false;
                    j++;
                }
            }
        }

        if (isFormat) {

            if(sortedByFormatSTR[j].substr(0,4).compare("0000")==0){
                vector<string> temp;
                temp.push_back(address.at(i));
                temp.push_back(getLabel(symTable, address.at(i)));
                temp.push_back("WORD");
                stringstream ss;
                stringstream ss1;
                int size;
                ss << hex << sortedByFormatSTR.at(j);
                ss >> size;
                ss1 <<size;

                temp.push_back(ss1.str());
                temp.push_back(sortedByFormatSTR[j]);
                total.push_back(temp);
                j++;
            }
            else if (sortedByFormatSTR[j].length() ==2) {                                                                         //Checks for format 1
                total.push_back(format1(address[i], sortedAndBinarySTR[j], labels[i], sortedByFormatSTR[j]));
                j++;
            } else if (sortedByFormatSTR[j].length() ==4) {                                                                         //Checks for format 2
                total.push_back(format2(address[i], sortedAndBinarySTR[j], labels[i], sortedByFormatSTR[j]));        //This pushes the format 2 element vector
                j++;
            } else if (sortedByFormatSTR[j].length() == 6) {
                total.push_back(format3(address[i], sortedAndBinarySTR[j], labels[i], sortedByFormatSTR[j], symTable, allAddresses, literals, litTable));
                j++;
            } else if (sortedByFormatSTR[j].length() == 8) {                                                                         //Checks for format 2
                //  total.push_back(format4(address[i], sortedAndBinarySTR[i], labels[i]), sortedByFormatSTR[i], symTable));
                total.push_back(format4(address[i], sortedAndBinarySTR[j], labels[i], sortedByFormatSTR[j], symTable));
                j++;
                //This pushes the format 4 element vector
            } else {
                cout << "ERROR: Format not found" << endl;
            }
        }
    }
    return total;
}

vector<vector<string> > appendLiteral(vector<vector<string> > total, vector<string> litTable, vector<string> symTable,vector<string> literals){
   bool found = false;
   vector<vector<string> > tempVector;

   for(string litTableLine : litTable){
        for(int i=0; i<total.size();i++){
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
                    operand.erase(std::remove_if(operand.begin(), operand.end(), ::isspace), operand.end());
                    temp.push_back(operand);

                    if(litTableLine.at(9) == 'C') {
                        string dat = litTableLine.substr(11, litTableLine.at(19) - '0');

                        ostringstream os;
                        for (int j = 0;
                             j < dat.length(); j++) {  // Convert current LABEL to HEX and push back as Object Code
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

