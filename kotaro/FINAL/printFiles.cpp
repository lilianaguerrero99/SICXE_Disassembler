
/**
 *Students involve: (Name, account, Red ID)
 *Kotaro Ueoka, cssc1947, (RedID 821442616)
 *Liliana Guerrero, cssc1948, (RedID 821798582)
 *Marie Duffy, cssc1949, (RedID 821505237)
 *Kyle McLain Kane, cssc1950, (RedID 820003555)
 *Class: CS 530, Spring 2020
 *Assignment information: Assignment #2, XE Disassembler
 *Filename: printFiles.cpp
 */

#include "printFiles.h"
int lastAddress;

// Appends RESW/RESB that were not previously added while dissasembling.  REWS/RESB declarations that happen at the end of the file.
vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable,  vector<string> allAddresseses, string hRecord) {

    stringstream ss1;
    ss1 << hex << total.at(total.size()-1).at(0);
    ss1 >> lastAddress;
    for (size_t i=0; i<symTable.size();i++){          // Loop through every line in symbol file and compare address to the last known address
        string toCompare = symTable.at(i).substr(10,4);  // address of symbol/label
        int address;
        stringstream ss;
        ss << hex << toCompare;
        ss >> address;
        if(address > lastAddress){  // Append line to total if address is bigger than last address given
            vector<string> temp;  // Create temp vector to push back to total
            temp.push_back(symTable.at(i).substr(10,4));
            getLabel(symTable, symTable.at(i).substr(10,4));
            if(i < symTable.size()-1){  // Make sure not to compare to null string
                stringstream ss2;
                int nextAddress;
                ss2 << hex << symTable.at(i+1).substr(10,4);
                ss2 >> nextAddress;
                int size = nextAddress - address;
                stringstream ss3;
                ss3 << hex << size;
                string sizeString = ss3.str();
                transform(sizeString.begin(), sizeString.end(), sizeString.begin(), ::toupper);
                if(size % 3 == 0){
                    temp.push_back("RESW");
                    size = size / 3;
                    temp.push_back(to_string(size));
                } else {
                    temp.push_back("RESB");
                    temp.push_back(to_string(size));
                }


            } else {  // If the next is null compare to the size of the hRecord size
                stringstream ss2;
                int nextAddress;
                ss2 << hex << hRecord.substr(15,4);
                ss2 >> nextAddress;
                int size = nextAddress - address;
                stringstream ss3;
                ss3 << hex << size;
                string sizeString = ss3.str();
                transform(sizeString.begin(), sizeString.end(), sizeString.begin(), ::toupper);
                if(size % 3 == 0){
                    temp.push_back("RESW");
                    size = size / 3;
                    temp.push_back(to_string(size));
                } else {
                    temp.push_back("RESB");
                    temp.push_back(to_string(size));
                }
            }
            temp.push_back("");
            temp.push_back("");
            total.push_back(temp);
        }
    }
    return total;
}

// Appends the first line of the program in format (STARTING ADDRESS, NAME OF PROGRAM, START, STARTING ADDRESS, )
vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable, string hRecord) {
    vector<vector<string>> temp;  // TEMP vector to push back to total
    vector<string> toAdd;
    string label;
    label.append(symTable.at(0).substr(0, 6));
    label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
    toAdd.push_back(symTable.at(0).substr(10, 4));
    toAdd.push_back(label);
    toAdd.push_back("START");

    stringstream ss;
    stringstream ss1;
    int address;
    ss << hex << hRecord.substr(9,4);
    ss >> address;
    ss1 << hex << address;


    toAdd.push_back(ss1.str());  // TODO: NEEDS TO BE STARTING ADDRESS
    toAdd.push_back("");
    temp.push_back(toAdd);

    for(vector<string> line : total){
        temp.push_back(line);
    }
    return temp;
}

// Appends last line of the program in format ( , , END, FIRST LABEL, )
vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses) {
    vector<string> toAdd;  // Vector to push back to total
    string address = symTable.at(1).substr(10, 4);
    toAdd.push_back("");
    toAdd.push_back("");
    toAdd.push_back("END");
    toAdd.push_back(getLabel(symTable, address));
    toAdd.push_back("");
    total.push_back(toAdd);
    return total;

}

// Appends LTORG right before the RESW/RESB declarations at the end of the file
vector<vector<string> > appendLTORG(vector<vector<string> > total) {
    vector<string> toAdd;
    if(lTorg) {  // Append lTorg to line if we set lTorg to true
        vector<vector<string>> tempVect; // temp vector to push back to total
        stringstream ss1;
        for (vector<string> line : total) {  // Once we add Ltorg exit loop
            stringstream ss;
            int currAdd;
            ss << hex << line.at(0);
            ss >> currAdd;
            bool done;
            if(currAdd > lastAddress && !done) {
                 toAdd.push_back("");
                 toAdd.push_back("");
                 toAdd.push_back("LTORG");
                 toAdd.push_back("");
                 toAdd.push_back("");
                 tempVect.push_back(toAdd);
                 done = true;
            }
            tempVect.push_back(line);
        }
        return tempVect;
    }

    return total;
}

// Output the fileName.lis file into working directory
void printLis(vector<vector<string> > total, string fileName) {
    string file;
    file.append(fileName);
    file.append(".lis");
    ofstream Print(file);
    if (total.size() != 0) {
        if (total.size() != 0) {

            for (vector<string> line : total) {
                Print << line.at(0);
                for(int i=line.at(0).size(); i<7; i++){  // PRINT ADDRESS
                    Print << " ";
                }
                Print << line.at(1);
                for(int i=line.at(1).size(); i<7; i++){  // PRINT LABEL
                    Print << " ";
                }

                if(line.at(2).find("+" )==0){
                    Print << line.at(2);
                    for(int i=line.at(2).size(); i<9; i++){
                        Print << " ";
                    }
                }else {
                    Print << " ";
                    Print << line.at(2);
                    for(int i=line.at(2).size(); i<8; i++){
                        Print << " ";
                    }
                }
                line.at(3).erase(std::remove_if(line.at(3).begin(), line.at(3).end(), ::isspace), line.at(3).end());
                if(line.at(3).find("=")==0 || line.at(3).find("#")==0 || line.at(3).find("@")==0){
                    Print << line.at(3);
                    for(int i=line.at(3).size(); i<11; i++){
                        Print << " ";
                    }
                }else {
                    Print << " ";
                    Print << line.at(3);
                    for(int i=line.at(3).size(); i<10; i++){
                        Print << " ";
                    }
                }

                Print<< line.at(4);
                for(int i=line.at(4).size(); i<10; i++){  // PRINT LABEL
                    Print << " ";
                }

                Print << endl;
            }

        }
    }
    else {
        Print << "Nothing to Print" << endl;
    }
}

// Output the fileName.sic file into working directory
void printSic(vector<vector<string> > total, string fileName) {
    string file;
    file.append(fileName);
    file.append(".sic");
    ofstream Print(file);
    if (total.size() != 0) {
        if (total.size() != 0) {
            for (vector<string> line : total) {

                Print << line.at(1);
                for(int i=line.at(1).size(); i<7; i++){  // PRINT LABEL
                    Print << " ";
                }

                if(line.at(2).find("+" )==0){
                    Print << line.at(2);
                    for(int i=line.at(2).size(); i<9; i++){
                        Print << " ";
                    }
                }else {
                    Print << " ";
                    Print << line.at(2);
                    for(int i=line.at(2).size(); i<8; i++){
                        Print << " ";
                    }
                }
                line.at(3).erase(std::remove_if(line.at(3).begin(), line.at(3).end(), ::isspace), line.at(3).end());
                if(line.at(3).find("=")==0 || line.at(3).find("#")==0 || line.at(3).find("@")==0){
                    Print << line.at(3);
                    for(int i=line.at(3).size(); i<11; i++){
                        Print << " ";
                    }
                }else {
                    Print << " ";
                    Print << line.at(3);
                    for(int i=line.at(3).size(); i<10; i++){
                        Print << " ";
                    }
                }
                Print << endl;
            }

        }
    }
    else {
        Print << "Nothing to Print" << endl;
    }
}

// Insert Base Declarations under lines with LDB in them
vector<vector<string> >  insertBase (vector<vector<string>> total, vector<string> symTable){
    vector<vector<string>> temp;
    for(vector<string> line : total){
        temp.push_back(line);
        if(line.at(2).compare("+LDB") ==0|| line.at(2).compare("LDB")==0){
            vector<string> tempVector;
            tempVector.push_back("");
            tempVector.push_back("");
            tempVector.push_back("BASE");
            string label = line.at(3);
            string chars = "#";


            for (char c: chars) {
                label.erase(std::remove(label.begin(), label.end(), c), label.end());
            }

            tempVector.push_back(label);
            tempVector.push_back("");
            temp.push_back(tempVector);
        }
    }
    return temp;
}

// Sort the total vector once all literals and object code lines are added
vector<vector<string> > sortTotal(vector<vector<string>> total){
    vector<int> numArray;
    for(size_t i=0; i< total.size(); i++){  //
        stringstream ss;
        int address;
        ss << hex << total.at(i).at(0);
        ss >> address;
        numArray.push_back(address);
    }

    sort(numArray.begin(), numArray.end());


    vector<vector<string>> newVector;

    for(int i : numArray){

        stringstream ss;
        string address;
        ss << hex << setfill('0') << setw(4) << i;
        address = ss.str();
        transform(address.begin(), address.end(), address.begin(), ::toupper);

        for(vector<string> line : total){
            if(address.compare(line.at(0))==0 ){
                vector<string> temp;
                temp.push_back(line.at(0));
                temp.push_back(line.at(1));
                temp.push_back(line.at(2));
                temp.push_back(line.at(3));
                temp.push_back(line.at(4));
                newVector.push_back(temp);
            }
        }

    }
    return newVector;
}

// Main program called from main
void runProgram(string filePath) {

    string objFilePath;  // filePath.obj
    string symFilePath; // filePath.sym

    objFilePath.append(filePath);
    symFilePath.append(filePath);
    objFilePath.append(".obj");
    symFilePath.append(".sym");

    // Separate object code file into different elements based on line
    string hRecord = getHRecord(objFilePath);  // Header record line as a string
    vector<string> tRecords = getTRecords(objFilePath);  // Text record line as a vector of strings
    string eRecord = getERecord(objFilePath);  // End record line as a string
    vector<string> tRecordsStartingAddress= getTRecordsStartAddress(tRecords);  // Starting Address in Text Records
    vector<string> tRecordsLength = getTRecordsLength(tRecords);  // 2 byte legth of Text record as vector

    // Separate symbol table into symTable and litTable
    vector<string> symTable = getSymTable(symFilePath);  // Stores each line of symbols lines in vector
    vector<string> litTable = getLitTable(symFilePath);  // Stores all literal lines in a vector

    vector<string> sorted; // Separate tRecord by Object Code/Format
    vector<string> binarySorted; // Convert Object Code to binary

    vector<string> literals = getLiterals(litTable); // ["Literal", "Literal", "Literal]
    vector<string> literalsOBj  = getLiteralsObj(getTRecordsSubstr(tRecords), literals ,getLiteralHex(literals)); // Converts literals such as EOF to hex equivalent


    if (tRecords.size() != 0) {
        sorted = getFormatArray(getTRecordsSubstr(tRecords), literalsOBj);  // Store return value into sorted;
        binarySorted = getBinaryValues(sorted);  // Store binary value into binarySorted;
    }

    vector<string> allAddresses;  // Calculate allAddresses including jumps

    if (hRecord.size() != 0) {
          allAddresses = addressCalculationWithTRecord(hRecord, tRecordsLength, tRecordsStartingAddress, getTRecordsSubstr(tRecords), sorted, symTable);
    }


    vector<string> allLabels = getAllLabels(allAddresses, symTable);  // Parallel vector of labels with addresses
    vector<vector<string> > total;  // Master vector that stores each line as its own vector of strings

    total = masterFormat(total, allAddresses, sorted, binarySorted, allLabels, symTable,  allAddresses, literalsOBj, litTable); // Adds Object Code Area into total
    total = appendLiteral(total, litTable, symTable, literalsOBj);  // adds literals to total

    total = sortTotal(total);  // sorts total by address

    total = appendSymbol(total, symTable, allAddresses, hRecord);  // append RESW/RESB to end of total
    total = appendLTORG(total);  // Appends LTorg if literals are declared in object code

    total = insertBase(total, symTable);  // Appends BASE declarations every time LDB is used

    total = appendStart(total, symTable, hRecord); // Prints First Line
    total = appendEnd(total, symTable, litTable, allAddresses);  // Prints Last Line

    printLis(total, filePath);
    printSic(total, filePath);


}

int main(int argc, char* argv[]) {
    if(argc == 1){
        cout << "Please enter filename" << endl;
        return 0;
    }
    string file = argv[1];

    runProgram(file);
}
