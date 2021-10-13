//  main.cpp
//  SIC/XE Disassember


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <map>
#include "opcodeTableBinary.h"

using namespace std;
string base;
int insideX;
opcodeTableBinary op;

//Assuming no SIC format 1 commands
//Format 1 (First char should be c or f )
//Format 2 (First char should be 9,a, or b)
//Format 4 (3rd char should be a 1 or 9 for extended bit)
//Format 3 (Default if all cases fall through)
vector<vector<string>> getLiteralVector(vector<string> litTable) {
    vector<vector<string>> total; // [["Literal", "Address"], ["Literal", "Address"]]
    vector<int> literalSize;
    for (int i = 0; i < litTable.size(); i++) {  // Calculate Size of each literal
        char size = litTable.at(i).at(19) - '0';
        literalSize.push_back((int) size);
    }

    for (int k = 0; k < litTable.size(); k++) {
        vector<string> literal;
        literal.push_back(litTable.at(k).substr(8, literalSize.at(k)+4));
        literal.push_back(litTable.at(k).substr(26, 4));

        total.push_back(literal);
    }
    return total;
}

vector<string> getLiterals(vector<string> litTable){
    vector<string> literals;
    vector<int> literalSize;
    for (int i = 0; i < litTable.size(); i++) {  // Calculate Size of each literal
        char size = litTable.at(i).at(19) - '0';
        literalSize.push_back((int) size);
    }

    for (int k = 0; k < litTable.size(); k++) {
        literals.push_back(litTable.at(k).substr(11, literalSize.at(k)));
    }
    return literals;
}

vector<string> getFormatArray(vector<string> vectorToSort, vector<string> literals) {
    int lengthOfVectorInElements = (int) vectorToSort.size();                                 //Gets the length of the vector
    string variable = "";                                                               //Initializing the string that we will be chopping up

    for (int i = 0; i <
                    lengthOfVectorInElements; i++)                                   //For loop to append multiple elements to a single string
        variable.append(vectorToSort[i]);

    int stringLength = (int) variable.length();                                               //Gets the length of the string we will be chopping up
    vector<string> v;                                                                   //This is the vector declaration to return our sorted vector
    int i = 0;

    while (i < stringLength) {
        //Format 1 check case (1 byte)
        for (int k = 0; k < literals.size(); k++) {
            if (variable.substr(i, literals.at(k).length()).compare(literals.at(k)) == 0) {
                v.push_back(variable.substr(i, literals.at(k).length()));
                i += literals.at(k).length();
            }
        }
        if (variable.at(i) == 'C' || variable.at(i) == 'F') {
            v.push_back(variable.substr(i, 2));
            i += 2;
        }

            //Format 2 check case (2 bytes)
        else if (variable.at(i) == '9' || variable.at(i) == 'A' || variable.at(i) == 'B') {
            v.push_back(variable.substr(i, 4));
            i += 4;
        }

            //Format 4 check case   (4 bytes)
        else if (variable.at(i + 2) == '1' || variable.at(i + 2) == '9') {
            v.push_back(variable.substr(i, 8));
            i += 8;
        }

            //Format 3 default  (3 bytes)
        else {
            v.push_back(variable.substr(i, 6));
            i += 6;
        }
    }

    return v;
}

vector<string> getBinaryValues(vector<string> vectorToBinary) {
    vector<string> buff;                                                               //Creating a vector to store converted values
    for (int i = 0;
         i < vectorToBinary.size(); i++) {                                     //Looping through the vectors elements
        string store = "";                                                              //Reseting the store string/initializing the store string
        for (int j = 0; j <
                        vectorToBinary[i].length(); j++) {                            //Looping through each character in that element
            if (vectorToBinary[i].at(j) ==
                '0')                                          //These if statements act as cases and they append the result to store that will go into its prospective element
                store.append("0000");
            if (vectorToBinary[i].at(j) == '1')
                store.append("0001");
            if (vectorToBinary[i].at(j) == '2')
                store.append("0010");
            if (vectorToBinary[i].at(j) == '3')
                store.append("0011");
            if (vectorToBinary[i].at(j) == '4')
                store.append("0100");
            if (vectorToBinary[i].at(j) == '5')
                store.append("0101");
            if (vectorToBinary[i].at(j) == '6')
                store.append("0110");
            if (vectorToBinary[i].at(j) == '7')
                store.append("0111");
            if (vectorToBinary[i].at(j) == '8')
                store.append("1000");
            if (vectorToBinary[i].at(j) == '9')
                store.append("1001");
            if (vectorToBinary[i].at(j) == 'A')
                store.append("1010");
            if (vectorToBinary[i].at(j) == 'B')
                store.append("1011");
            if (vectorToBinary[i].at(j) == 'C')
                store.append("1100");
            if (vectorToBinary[i].at(j) == 'D')
                store.append("1101");
            if (vectorToBinary[i].at(j) == 'E')
                store.append("1110");
            if (vectorToBinary[i].at(j) == 'F')
                store.append("1111");

            if (j == vectorToBinary[i].length() -
                     1)                                     //Stores the converted values into buffer once the element is
                buff.push_back(store);
        }
    }
    return buff;
}

vector<string>
getTRecords(string filePath) { // Stores each line of Text Record as a vector element and returns the vector
    vector<string> tRecords;
    ifstream file(filePath);
    //Checking to see if the file is there
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    while (getline(file, line)) {
        if (line.at(0) == 'T') {
            tRecords.push_back(line);
        }
    }
    file.close();
    return tRecords;
}

string getHRecord(string filePath) { // Return Header Record as a string
    ifstream file(filePath);
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    while (getline(file, line)) {
        if (line.at(0) == 'H') {
            return line;
        }
    }

    file.close();
    return "";
}

string getERecord(string filePath) { // Return End Record as a string
    ifstream file(filePath);
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    while (getline(file, line)) {
        if (line.at(0) == 'E') {
            return line;
        }
    }
    file.close();
    return "";
}

vector<string> getTRecordsSubstr(vector<string> tRecords) {  // Cut out first 9 characters from tRecord and return

    vector<string> tRecordsSubstr;
    for (int i = 0; i < tRecords.size(); i++) {  //
        tRecordsSubstr.push_back(tRecords.at(i).substr(9, tRecords.at(
                i).length()));  // Cut out first 9 characters from tRecord and add to tRecordSubstr
    }
    return tRecordsSubstr;
}

vector<string> getSymTable(
        string filePath) {  // Returns everything under "Symbol  Value   Flags:" up to blank line or "Name    Literal  Length Address:"
    vector<string> symTable;
    ifstream file(filePath);
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    while (getline(file, line)) {
        if (line.compare("Symbol  Value   Flags:") == 0) {
            while (getline(file, line)) {  // Loop and store all symbols in symTable vector
                if (line.compare("-----------------------") == 0) {
                    continue;
                }
                if (line.compare("") != 0) {
                    symTable.push_back(line);
                } else if (line.compare("Name    Literal  Length Address:") ==
                           0) {  // Break if it finds "Name    Literal  Length Address:"
                    break;
                } else { // break if blank line
                    break;
                }
            }
        }
    }
    file.close();
    return symTable;
}

vector<string> getLitTable(string filePath) {
    vector<string> litTable;
    ifstream file(filePath);
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    while (getline(file, line)) {
        if (line.compare("Name    Literal  Length Address:") == 0) {
            while (getline(file, line)) {
                if (line.compare("------------------------------") == 0) {
                    continue;
                }
                if (line.compare("") != 0) {
                    litTable.push_back(line);
                } else {
                    break;
                }
            }
        }
    }
    file.close();
    return litTable;
}

vector<string> calculateAddresses(string header, vector<string> sorted,
                                  vector<string> symTable) {  // Return Vector of addresses exculding RESW/RESB int format
    vector<int> addresses;

    string startAddress = header.substr(9, 4);

    stringstream str;
    str << startAddress;
    int currAddress;

    str >> hex >> currAddress;
    addresses.push_back(currAddress);
    for (int i = 0; i < sorted.size(); i++) { // store address in int format
        int size = (int) sorted.at(i).size() / 2;
        currAddress = currAddress + size;
        addresses.push_back(currAddress);
    }
    vector<string> stringAddresses;
    for (int i = 0; i < addresses.size(); i++) {  // Convert addresses to string and uppercase
        stringstream stream;
        stream << setfill('0') << setw(4) << hex << addresses.at(i);
        string currentAddressString = stream.str();
        transform(currentAddressString.begin(), currentAddressString.end(), currentAddressString.begin(), ::toupper);
        stringAddresses.push_back(currentAddressString);
    }

    return stringAddresses;


}

vector<string> getAllAddresses(vector<string> addresses,
                               vector<string> symTable,
                               string hRecord) {  // Return vector of all addresses in string format including RESW and RESB
    vector<string> allAddress;
    allAddress = addresses;

    for (int i = 0; i < symTable.size(); i++) {
        string symTableSub = symTable.at(i).substr(10, 4);
        bool found = false;
        for (int j = 0; j < addresses.size(); j++) {
            if (symTableSub.compare(addresses.at(j)) == 0) {
                found = true;
            }
        }
        if (!found) {
            allAddress.push_back(symTableSub);
        }
    }
    allAddress.push_back(hRecord.substr(15, 4));


    return allAddress;

}

string getLabel(vector<string> symTable, string address) {  // Return label in symbol table of given address
    for (int i = 1; i < symTable.size(); i++) {
        if (address.compare(symTable.at(i).substr(10, 4)) == 0) {
            string label = symTable.at(i).substr(0, 6);
            label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
            return label;
        }
    }
    return "";
}

vector<string> getAllLabels(vector<string> allAddresses,
                            vector<string> symTable) {  // Creates an array of Labels that is parallel with allAddresses
    vector<string> allLabels;
    for (int i = 0; i < allAddresses.size(); i++) {
        allLabels.push_back(getLabel(symTable, allAddresses.at(i)));
    }
    return allLabels;
}


//These formats will need <ADDRESS, LABEL, INSTRUCTION/BLANK, OPERAND>
vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode) {
    //opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary to call on the opcode table
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line

    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(op.opTable(sortedAndBinarySTR.substr(0, 6)));                                    //Pushes the opcodeTableBinary
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

    return registerMNEMONIC.at(
            key);                                                                                    //Returning the value at the wanted key
}

vector<string> format2(string address, string sortedAndBinarySTR, string label, string objectCode) {
    vector<string> buffer;                                                                                              //Creating the individual buffer to store the one line
    string temp;                                                                                                        //Stores the parameters for the R1, R2 part
    //opcodeTableBinary op;                                                                                               //Creating an object of type opcodeTableBinary so we can utilize the opcode table

    buffer.push_back(address);                                                                                          //Pushes back the stored address
    buffer.push_back(label);                                                                                            //Pushes back the stored label
    buffer.push_back(op.opTable(sortedAndBinarySTR.substr(0, 6)));                                    //Pushes the opcodeTableBinary
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

void findBase (string hex, string binary){
    int size = hex.length() / 2;
    string find = op.opTable(binary.substr(0, 6));
    cout<< "this is what is found: " + find << endl;
    if(find.compare("LDB")==0){
        //if immd
        base = hex.substr(4,size);
        cout<< "the base is " + base<< endl;
    }
}

//needs working on
//void findIndex (string hex, string binary){
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
string calcTA (string disp, int index, int format){
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

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable,
                       vector<string> allAddresses, vector<string> literals, vector<vector<string>> literalsVector) {


    vector<string> line;
    opcodeTableBinary op;
    line.push_back(address);
    line.push_back(label);
    line.push_back(op.opTable(binary.substr(0, 6)));

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


vector<string> format4(string address, string binary, string label, string hex, vector<string> symTable) {
    vector<string> line;
    opcodeTableBinary op;


    line.push_back(address);
    line.push_back(label);

    //check opcode table for the correct mneumonic
    string opCode = "+";
    opCode.append(op.opTable(binary.substr(0, 6)));
    line.push_back(opCode);

    //put in operand and any necessary addressing identifiers
    if (binary.at(6) == '0' && binary.at(7) == '1') {
        //this indicates immediate addressing mode
        string curr = "#";
        curr.append(getLabel(symTable, hex.substr(4, 4)));
        line.push_back(curr);
    }
    else if (binary.at(6) == '1' && binary.at(7) == '0') {
        //this indicates indirect addressing mode
        string curr2 = "@";
        curr2.append(getLabel(symTable, hex.substr(4, 4)));
        line.push_back(curr2);
    }
    else { //simple addressing mode
        if(binary.at(8) == '1') { //indicated indexed format
            string curr3 = getLabel(symTable, hex.substr(4,4));
            curr3.append(",X");
            line.push_back(curr3);
        }
        else {
            line.push_back(getLabel(symTable, hex.substr(4, 4)));
        }

    }

    line.push_back(hex);

    return line;
}//Will return a vector of vectors containing each contents
vector<vector<string>> masterFormat(vector<vector<string>> total, vector<string> address, vector<string> sortedByFormatSTR, vector<string> sortedAndBinarySTR,
             vector<string> labels, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string>> literalsVector) {

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
            } else if (sortedByFormatSTR[i].length() ==
                       8) {                                                                         //Checks for format 2
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

vector<vector<string>> appendSymbol(vector<vector<string>> total, vector<string> symTable, vector<string> addresses1,
                                    vector<string> addresses2) {

    int start;
    for (int i = 0; i < addresses2.size(); i++) {
        if (addresses2.at(i).compare(addresses1.at(addresses1.size() - 1)) == 0) {
            start = i;
        }
    }

    for (int i = start; i < addresses2.size(); i++) {

        for (int j = 0; j < symTable.size(); j++) {
            if (addresses2.at(i).compare(symTable.at(j).substr(10, 4)) == 0) {
                vector<string> toAdd;
                string currAdd = symTable.at(j).substr(10, 4);

                toAdd.push_back(currAdd);
                toAdd.push_back(getLabel(symTable, currAdd));


                stringstream str1;
                stringstream str2;
                int curr;
                int next;
                str1 << addresses2.at(i);
                str2 << addresses2.at(i + 1);
                str1 >> hex >> curr;
                str2 >> hex >> next;
                int size = (next - curr) / 3;

                toAdd.push_back("RESW");
                toAdd.push_back(to_string(size));
                toAdd.push_back("");
                total.push_back(toAdd);

            }
        }
    }


    return total;
}

vector<vector<string>> appendStart(vector<vector<string>> total, vector<string> symTable) {
    vector<string> toAdd;
    string label;
    label.append(symTable.at(0).substr(0, 6));
    label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
    toAdd.push_back(symTable.at(0).substr(10, 4));
    toAdd.push_back(label);
    toAdd.push_back("START");
    toAdd.push_back("0");
    toAdd.push_back("000000");

    total.push_back(toAdd);
    return total;
}

vector<vector<string>> appendEnd(vector<vector<string>> total, vector<string> symTable, vector<string> allAddresses) {
    vector<string> toAdd;
    string label = symTable.at(1).substr(10, 4);
    toAdd.push_back(allAddresses.at(allAddresses.size() - 1));
    toAdd.push_back("END");
    toAdd.push_back(getLabel(symTable, label));
    toAdd.push_back("");
    toAdd.push_back("");
    total.push_back(toAdd);
    return total;
}

vector<vector<string>> appendLTORG(vector<vector<string>> total, vector<vector<string>> literalVector) {
    vector<string> toAdd;
    if(literalVector.size()!=0){
        toAdd.push_back("    ");
        toAdd.push_back("");
        toAdd.push_back("LTORG");
        toAdd.push_back("");
        toAdd.push_back("");
    }
    total.push_back(toAdd);
    return total;
}

void printLis(vector<vector<string>> total) {
    ofstream Print("simple.lis");
    if (total.size() != 0) {
        Print << "ADDRESS" << setw(9) << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17)
              << "OBJECT CODE" << endl;

        for (vector<string> line : total) {
            Print << line.at(0);
            Print << setw(12) << line.at(1);  // Print Label
            Print << setw(12) << line.at(2);  // Print Opcode
            Print << setw(15) << line.at(3); // Print Operand
            Print << setw(15) << line.at(4); // Print Object Code
            Print << endl;
        }

    } else {
        Print << "Nothing to Print" << endl;
    }

}

//the spacing still needs fixing
void printSic(vector<vector<string>> total) {
    ofstream Print("simple.sic");
    if (total.size() != 0) {
        Print << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17)
              << endl;
        //for (vector<string> line : total) {
        for (int i = 0; i < total.size(); i++) {
            Print << total.at(i).at(1) <<  setw(15) ;
            Print << total.at(i).at(2);
            Print  << total.at(i).at(3);
            Print << endl;
        }

    } else {
        Print << "Nothing to Print" << endl;
    }

}

void printTest(vector<vector<string>> total) {

    if (total.size() != 0) {
        cout << "ADDRESS" << setw(9) << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17)
             << "OBJECT CODE" << endl;
        cout << "------------------------------------------------------------" << endl;
        for (vector<string> line : total) {
            cout << line.at(0);
            cout << setw(12) << line.at(1);  // Print Label
            cout << setw(12) << line.at(2);  // Print Opcode
            cout << setw(15) << line.at(3); // Print Operand
            cout << setw(15) << line.at(4); // Print Object Code
            cout << endl;
        }
        cout << "-----------------------------------------------------------" << endl;
    } else {
        cout << "Nothing to Print" << endl;
    }

}

void testFormats() {

    string objFilePath = "sample.obj";
    string symFilePath = "sample.sym";

    // Separate object code file into different elements based on line
    string hRecord = getHRecord(objFilePath);
    vector<string> tRecords = getTRecords(objFilePath);
    string eRecord = getERecord(objFilePath);

    // Separate symbol table into symTable and litTable
    vector<string> symTable = getSymTable(symFilePath);
    vector<string> litTable = getLitTable(symFilePath);

    vector<string> sorted; // Separate tRecord by Object Code/Format
    vector<string> binarySorted; // Convert Object Code to binary

    vector<string> literals = getLiterals(litTable); // ["Literal", "Literal", "Literal]
    vector<vector<string>> literalsVector = getLiteralVector(litTable);  // ["Literal", "Address"], ["Literal", "Address"]

    if (tRecords.size() != 0) {
        sorted = getFormatArray(getTRecordsSubstr(tRecords), literals);  // Store return value into sorted;
        binarySorted = getBinaryValues(sorted);  // Store binary value into binarySorted;
    }
    vector<string> allAddresses;
    vector<string> stringAddresses;
    if (hRecord.size() != 0) {
        stringAddresses = calculateAddresses(hRecord, sorted,
                                             symTable);  // Addresses exculding RESW/RESB in  in string format
        allAddresses = getAllAddresses(stringAddresses,
                                       symTable, hRecord);  // All Addresses including RESW/RESB in string format
    }

    vector<string> allLabels = getAllLabels(allAddresses, symTable);
    vector<vector<string>> total;


    total = appendStart(total, symTable); // Prints First Line
    total = masterFormat(total, allAddresses, sorted, binarySorted, allLabels, symTable, allAddresses, literals, literalsVector); // Prints Object Code Area
    total = appendLTORG(total, literalsVector);
    total = appendSymbol(total, symTable, stringAddresses, allAddresses); // Prints Symbol Table Area
    total = appendEnd(total, symTable, allAddresses);  // Prints Last Line

    printLis(total);
    printSic(total);

    printTest(total);

}

int main() {
    testFormats();
}
