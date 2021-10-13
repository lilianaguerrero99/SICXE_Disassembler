#include "formats.h"
#include "openFiles.h"

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

void findBase (string hex, string binary) {
    int size = hex.length() / 2;
    string find = opcodeTable(binary.substr(0, 6));
    cout<< "this is what is found: " + find << endl;
    if(find.compare("LDB")==0){
        //if immd
        base = hex.substr(4,size);
        cout<< "the base is " + base<< endl;
    }
}

//needs working on
//void findIndex (string hex, string binary){ //for indexing ,X
//    opcodeTableBinary op;
//    //int size = hex.length() / 2;
//    string find = op.opTable(binary.substr(0, 6));
//    cout<< "index is found: " + find << endl;
//    if(find.compare("LDX")==0){
//        //figure out what LDX is set to
//        index =
//        cout<< "the result is " + index<< endl;
//    }
//}

//string calcBase (string disp, string index){
string calcTA (string disp, int index, int format) {
    //format 4: add + (x)
    //format 3:
            // disp + (base) --> immd and indr
            // disp + (base) + (x) --> simple

    //if(index != 0)
        //add (x)+ result
    //int size = disp.length() / 2;
//    stringstream str2;
//    string s2 = index;
//    str2 << s2;
//    cout<< str2.str()<< endl;
//    int value2;
//    str2 >> hex >> value2;
//    cout<< value2 << endl;

//if(index == 1 && format == 3) {
//    stringstream str;
//    string s1 = disp;
//    str << s1;
//    cout << str.str() << endl;
//    int value;
//    str >> hex >> value;
//    cout << value << endl;
//
//    stringstream str1;
//    string s2 = base;
//    str1 << s2;
//
//    int value1;
//    str1 >> hex >> value1;
//    cout << value1 << endl;
//
//    stringstream str3;
//    string s3 = insideX;
//    str3 << s3;
//
//    int value3;
//    str3 >> hex >> value3;
//    cout << value3 << endl;
//
//    int addr = value + value1 + value3;
//
//    cout << uppercase << hex << addr << endl;
//    stringstream stream;
//    stream << setfill('0') << setw(4) << hex << addr;
//    string result = stream.str();
////    string result("00" + stream.str());
//    transform(result.begin(), result.end(), result.begin(), ::toupper);
////    cout<< result<<endl;
//
//    return result;
//
//}
//else if (format == 4 ){
//    stringstream str;
//    string s1 = disp;
//    str << s1;
//    cout << str.str() << endl;
//    int value;
//    str >> hex >> value;
//    cout << value << endl;
//
//    stringstream str1;
//    string s2 = insideX;
//    str1 << s2;
//
//    int value1;
//    str1 >> hex >> value1;
//    cout << value1 << endl;
//
//
//
//    int addr = value + value1 ;
//
//    cout << uppercase << hex << addr << endl;
//    stringstream stream;
//    stream << setfill('0') << setw(4) << hex << addr;
//    string result = stream.str();
////    string result("00" + stream.str());
//    transform(result.begin(), result.end(), result.begin(), ::toupper);
////    cout<< result<<endl;
//
//    return result;
//}
//else{
    stringstream str;
    string s1 = disp;
    str << s1;
    cout << str.str() << endl;
    int value;
    str >> hex >> value;
    cout << value << endl;

    stringstream str1;
    string s2 = base;
    str1 << s2;

    int value1;
    str1 >> hex >> value1;
    cout << value1 << endl;

    int addr = value + value1;

    cout << uppercase << hex << addr << endl;
    stringstream stream;
    stream << setfill('0') << setw(4) << hex << addr;
    string result = stream.str();
//    string result("00" + stream.str());
    transform(result.begin(), result.end(), result.begin(), ::toupper);
//    cout<< result<<endl;

    return result;
//}
}

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string> > literalsVector) {

    vector<string> line;
    line.push_back(address);
    line.push_back(label);
    line.push_back(opcodeTable(binary.substr(0, 6)));

    string indr = "10";
    string immd = "01";
    string simp = "11";
    char b = '1';
    char p = '1';
    char x = '1';

    string operand;
    // TODO: INDIRECT
    if(binary.substr(6,2).compare(indr)==0){
        operand.append(" @");
        //TODO: INDIRECT & BASE
        if (binary.at(9) == b) {
            operand.append("IMM,BASE");
        }
            // TODO: INDIRECT & PC
        else if (binary.at(10) == p) {
            operand.append(" IMM,PC");
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


            // 2's complement calculation of TA
            if (hexVal.at(3) == 'F') {
                string newString;
                for (int i = 3; i < 6; i++) {
                    if (hexVal.at(i) == '0') {
                        newString.append("F");
                    }
                    if (hexVal.at(i) == '1') {
                        newString.append("E");
                    }
                    if (hexVal.at(i) == '2') {
                        newString.append("D");
                    }
                    if (hexVal.at(i) == '3') {
                        newString.append("C");
                    }
                    if (hexVal.at(i) == '4') {
                        newString.append("B");
                    }
                    if (hexVal.at(i) == '5') {
                        newString.append("A");
                    }
                    if (hexVal.at(i) == '6') {
                        newString.append("9");
                    }
                    if (hexVal.at(i) == '7') {
                        newString.append("8");
                    }
                    if (hexVal.at(i) == '8') {
                        newString.append("7");
                    }
                    if (hexVal.at(i) == '9') {
                        newString.append("6");
                    }
                    if (hexVal.at(i) == 'A') {
                        newString.append("5");
                    }
                    if (hexVal.at(i) == 'B') {
                        newString.append("4");
                    }
                    if (hexVal.at(i) == 'C') {
                        newString.append("3");
                    }
                    if (hexVal.at(i) == 'D') {
                        newString.append("2");
                    }
                    if (hexVal.at(i) == 'E') {
                        newString.append("1");
                    }
                    if (hexVal.at(i) == 'F') {
                        newString.append("0");
                    }

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
            operand.append(getLabel(symTable, calcTA(hexVal.substr(3,3), 0, 3)));
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
    findBase(hexVal, binary);
    opCode.append(opcodeTable(binary.substr(0, 6)));
    line.push_back(opCode);

    //put in operand and any necessary addressing identifiers
    if (binary.at(6) == '0' && binary.at(7) == '1') { // IMMEDIATE ADDRESSING MODE
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
    else if (binary.at(6) == '1' && binary.at(7) == '0') { // INDIRECT ADDRESSING MODE
        string curr2 = "@";
        curr2.append(getLabel(symTable, hexVal.substr(4, 4)));
        line.push_back(curr2);
    }
    else { // SIMPLE ADDRESSING MODE
        if(binary.at(8) == '1') { // INDEXED
            string curr3 = getLabel(symTable, hexVal.substr(4,4));
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
