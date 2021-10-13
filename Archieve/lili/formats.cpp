#include "formats.h"

string base;
string indr = "10";
string immd = "01";
string simp = "11";
int b,x,p = 1;

class registersFormat {
public:
    string regA;
    string regX;
    string regL;
    string regB;
    string regS;
    string regT;
    string regF;
    string regPC;
    string regSW;

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
    registersFormat()= default;
};

registersFormat reg;
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
    temp.append(registers(
            register2));                                                                                  //Pushes on the value of what MNEMONIC R2 is

    buffer.push_back(
            temp);                                                                                             //Pushes the operand onto our buffer
    buffer.push_back(
            objectCode);                                                                                       //Pushes the object code to the end
    return buffer;
}

//string calcBase (string disp, string index){
string calcTA (string one, string two, int index) {

    //example for f4: calcTA(addr, "0", 1);

    //para: two strings (string a, string b)
    //two case:
        //this one is always runs
            //a+b
        //if(index == 1)
            //make stringstream for reg x
            //a+b+x

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
    

    int total = value1 + value2;
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

string twoComplement(char input){
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

void findReg(string opcode, string hex){
    //length of object code in hex
    int size = hex.length()/2;
    string find = opcode;

    if(find.compare("LDB")==0){
        base = hex.substr(4,size);
        reg.setValue("B", base);
    }
}

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string> > literalsVector) {

    vector<string> line;
    line.push_back(address);
    line.push_back(label);
    line.push_back(opcodeTable(binary.substr(0, 6)));

    string operand;
    // TODO: INDIRECT
    if(binary.substr(6,2).compare(indr)==0){
        operand.append(" @");
        //TODO: INDIRECT & BASE
        if (binary.at(9) == b) {
            operand.append(getLabel(symTable, calcTA(hexVal.substr(3,3), 0, 3)));
        }
            // TODO: INDIRECT & PC
        else if (binary.at(10) == p) {

//            operand.append(" IMM,PC");
        }
    }
        //IMMEDIATE
    else if(binary.substr(6,2).compare(immd)==0){
        operand.append(" #");
        // TODO: IMMEDIATE & BASE
        if (binary.at(9) == b) {
            operand.append("IMM,BASE");
        }
            // TODO: IMMEDIATE & PC
        else if (binary.at(10) == p) {
            operand.append(" IMM,PC");
        }
            // COMPLETED: IMMEDIATE & DIRECT
        else {
            stringstream str;
            int intVal;
            string hexString = hexVal.substr(3, 3);
            str << hexString;
            str >> hex >> intVal;
            operand.append(to_string(intVal));
        }
    }
    else if (binary.substr(6,2).compare(simp)==0){ //SIMPLE
        // COMPLETED: Simple & PC Relative
        if (binary.at(10) == p) {
            stringstream str;
            stringstream str2;
            stringstream str3;
            stringstream stream1;
            stringstream stream2;
            string val;
            int pc;
            int disp;

            str << address;
            str >> hex >> pc;
            pc = pc + 3;
            string newString;
            
            // MAP
           
           // 2's complement calculation of TA
           if (hexVal.at(3) == 'F'|| hexVal.at(3) == 'E'||hexVal.at(3) == 'D'||hexVal.at(3) == 'C'|| hexVal.at(3) == 'B'||hexVal.at(3) == 'A'||hexVal.at(3) == '9'||hexVal.at(3) == '8') {
               string newString;
               for (int i = 3; i < hexVal.length(); i++) {
                   newString.append(twoComplement(hexVal.at(i)));
               }
                str3 << newString;
                str2 << newString;
                str2 >> hex >> disp;
                disp++;
                pc = pc - disp;

            } else {
                str2 << hexVal.substr(3, 3);
                str2 >> hex >> disp;
                pc = pc + disp;
            }

            stream1 << setfill('0') << setw(4) << hex << pc;
            string currentString = stream1.str();
            transform(currentString.begin(), currentString.end(), currentString.begin(), ::toupper);

            operand.append(getLabel(symTable, currentString));

            if (binary.at(8) == x) {
                operand.append(",X");
            }
        }
            // TODO: SIMPLE & BASE
        else if(binary.at(9) == b) {
            //calculate before getting the label
            //convert string to int to do the calculations
            //disp + base
            //convert back into string and get label
            operand.append(getLabel(symTable, calcTA(hexVal.substr(3,3), reg.getValue("B"), 0)));
        }
    }

    // TODO: LITERALS
    // Check if literal address == current address
    // If match found append literal to operand
    for(int i=0; i<literalsVector.size(); i++){
        if(literalsVector.at(i).at(1).compare(address)==0){
            operand.append(literalsVector.at(i).at(0));
        }
    }
    line.push_back(operand);
    line.push_back(hexVal);
    return line;
}

vector<string> format4(string address, string binary, string label, string hexVal, vector<string> symTable) {
    vector<string> line;
    line.push_back(address);
    line.push_back(label);
    string opCode = "+";

    //check opcode table for the correct instruction
    findReg(opcodeTable(binary.substr(0,6)), hexVal);
    opCode.append(opcodeTable(binary.substr(0, 6)));
    line.push_back(opCode);

    //put in operand and any necessary addressing identifiers
    if (binary.substr(6,2).compare(immd) == 0) { // IMMEDIATE ADDRESSING MODE
        string curr = "#";
        string label = getLabel(symTable, hexVal.substr(4, 4));
        if(label.compare("") != 0) { //indicates that there is a symbol for this line
            curr.append(label);
        }
        else { //no symbol for this line, so it immediately addresses an int value
            // use stringstream to convert the hex value to decimal value
            stringstream str;
            int intVal;
            string hexString = hexVal.substr(3, 5);
            str << hexString;
            str >> hex >> intVal;
            curr.append(to_string(intVal));
        }

        line.push_back(curr);
    }
    else if (binary.substr(6,2).compare(indr) == 0) { // INDIRECT ADDRESSING MODE
        string curr2 = "@";
        curr2.append(getLabel(symTable, hexVal.substr(4, 4)));
        line.push_back(curr2);
    }
    else { // SIMPLE ADDRESSING MODE
        if(binary.at(8) == '1') { // INDEXED
            string curr3 = getLabel(symTable,calcTA(hexVal.substr(4,4), "0", 1));
            //string curr3 = getLabel(symTable, hexVal.substr(4,4));
            curr3.append(",X");
            line.push_back(curr3);
        }
        else {
            line.push_back(getLabel(symTable, hexVal.substr(4, 4)));
        }

    }

    // push the object code onto the vector
    line.push_back(hexVal);

    return line;
}

vector<vector<string> > masterFormat(vector<vector<string> > total, vector<string> address, vector<string> sortedByFormatSTR, vector<string> sortedAndBinarySTR, vector<string> labels, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string> > literalsVector) {

    //This will loop through the format sorted vector and then convert by calling each necessary function
    //Passes the string at that line-


    for (int i = 0; i < sortedByFormatSTR.size(); i++) {
        bool isFormat = true;
        for (int k = 0; k < literals.size(); k++) {
            if (sortedByFormatSTR.at(i).compare(literals.at(k)) == 0) {
                isFormat = false;
            }
        }
        if (isFormat == true) {
            if (sortedByFormatSTR[i].length() ==
                2) {                                                                         //Checks for format 1
                total.push_back(format1(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i]));
            } else if (sortedByFormatSTR[i].length() ==
                       4) {                                                                         //Checks for format 2
                total.push_back(format2(address[i], sortedAndBinarySTR[i], labels[i],
                                        sortedByFormatSTR[i]));        //This pushes the format 2 element vector
            } else if (sortedByFormatSTR[i].length() == 6) {
                total.push_back(format3(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i], symTable,
                                        allAddresses, literals, literalsVector));
            } else if (sortedByFormatSTR[i].length() == 8) {                                                                         //Checks for format 2
                //  total.push_back(format4(address[i], sortedAndBinarySTR[i], labels[i]), sortedByFormatSTR[i], symTable));
                total.push_back(format4(address[i], sortedAndBinarySTR[i], labels[i], sortedByFormatSTR[i], symTable));
                //This pushes the format 4 element vector
            } else {
                cout << "ERROR: Format not found" << endl;
            }
        }

    }
    return total;
}
