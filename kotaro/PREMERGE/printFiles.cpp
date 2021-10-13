
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
vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable,  vector<string> allAddresseses, string hRecord) {

    stringstream ss1;
    ss1 << hex << total.at(total.size()-1).at(0);
    ss1 >> lastAddress;
    for (int i=0; i<symTable.size();i++){
        string toCompare = symTable.at(i).substr(10,4);
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


            } else {
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

vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable, string hRecord) {
    vector<vector<string>> temp;
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

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses) {
    vector<string> toAdd;
    string address = symTable.at(1).substr(10, 4);
    toAdd.push_back("");
    toAdd.push_back("");
    toAdd.push_back("END");
    toAdd.push_back(getLabel(symTable, address));
    toAdd.push_back("");
    total.push_back(toAdd);
    return total;

}

vector<vector<string> > appendLTORG(vector<vector<string> > total) {
    vector<string> toAdd;
    if(lTorg) {
        vector<vector<string>> tempVect;
        stringstream ss1;
        for (vector<string> line : total) {
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

//the spacing still needs fixing
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

void printTest(vector<vector<string> > total) {
    if (total.size() != 0) {

        for (vector<string> line : total) {
            cout << line.at(0);
            for(int i=line.at(0).size(); i<7; i++){  // PRINT ADDRESS
                cout << " ";
            }
            cout << line.at(1);
            for(int i=line.at(1).size(); i<7; i++){  // PRINT LABEL
                cout << " ";
            }

            if(line.at(2).find("+" )==0){
                cout << line.at(2);
                for(int i=line.at(2).size(); i<9; i++){
                    cout << " ";
                }
            }else {
                cout << " ";
                cout << line.at(2);
                for(int i=line.at(2).size(); i<8; i++){
                    cout << " ";
                }
            }
            line.at(3).erase(std::remove_if(line.at(3).begin(), line.at(3).end(), ::isspace), line.at(3).end());
            if(line.at(3).find("=")==0 || line.at(3).find("#")==0 || line.at(3).find("@")==0){
                cout << line.at(3);
                for(int i=line.at(3).size(); i<11; i++){
                    cout << " ";
                }
            }else {
                cout << " ";
                cout << line.at(3);
                for(int i=line.at(3).size(); i<10; i++){
                    cout << " ";
                }
            }

            cout << line.at(4);
            for(int i=line.at(4).size(); i<10; i++){  // PRINT LABEL
                cout << " ";
            }

            cout << endl;
        }

    } else {
        cout << "Nothing to Print" << endl;
    }
}

vector<vector<string> > sortTotal(vector<vector<string>> total){
    vector<int> numArray;
    for(int i=0; i< total.size(); i++){  //
        stringstream ss;
        int address;
        ss << hex << total.at(i).at(0);
        ss >> address;
        numArray.push_back(address);
    }

    sort(numArray.begin(), numArray.end());


    vector<vector<string>> newVector;

    for(int i : numArray){
        bool found = false;
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

void testFormats(string filePath) {

    string objFilePath;
    string symFilePath;

    objFilePath.append(filePath);
    symFilePath.append(filePath);
    objFilePath.append(".obj");
    symFilePath.append(".sym");

    // Separate object code file into different elements based on line
    string hRecord = getHRecord(objFilePath);
    vector<string> tRecords = getTRecords(objFilePath);
    string eRecord = getERecord(objFilePath);
    vector<string> tRecordsStartingAddress= getTRecordsStartAddress(tRecords);  // Starting Address in Text Records
    vector<string> tRecordsLength = getTRecordsLength(tRecords);

    // Separate symbol table into symTable and litTable
    vector<string> symTable = getSymTable(symFilePath);
    vector<string> litTable = getLitTable(symFilePath);

    vector<string> sorted; // Separate tRecord by Object Code/Format
    vector<string> binarySorted; // Convert Object Code to binary

    vector<string> literals = getLiterals(litTable); // ["Literal", "Literal", "Literal]
    vector<string> literalsOBj  = getLiteralsObj(getTRecordsSubstr(tRecords), literals ,getLiteralHex(literals));


    if (tRecords.size() != 0) {
        sorted = getFormatArray(getTRecordsSubstr(tRecords), literalsOBj);  // Store return value into sorted;
        binarySorted = getBinaryValues(sorted);  // Store binary value into binarySorted;
    }
    vector<string> allAddresses;
    vector<string> stringAddresses;
    if (hRecord.size() != 0) {
//        stringAddresses = calculateAddresses(hRecord, sorted, symTable);  // Addresses exculding RESW/RESB in  in string format
//        allAddresses = getAllAddresses(stringAddresses, symTable, hRecord);  // All Addresses including RESW/RESB in string format
          allAddresses = addressCalculationWithTRecord(hRecord, tRecordsLength, tRecordsStartingAddress, getTRecordsSubstr(tRecords), sorted, symTable);
    }


    vector<string> allLabels = getAllLabels(allAddresses, symTable);
    vector<vector<string> > total;

    total = masterFormat(total, allAddresses, sorted, binarySorted, allLabels, symTable,  allAddresses, literalsOBj, litTable); // Prints Object Code Area
    total = appendLiteral(total, litTable, symTable, literalsOBj);

    total = sortTotal(total);

    total = appendSymbol(total, symTable, allAddresses, hRecord);
    total = appendLTORG(total);

    total = insertBase(total, symTable);

    total = appendStart(total, symTable, hRecord); // Prints First Line
    total = appendEnd(total, symTable, litTable, allAddresses);  // Prints Last Line

    printLis(total, filePath);
    printSic(total, filePath);
    printTest(total);

}

int main(int argc, char* argv[]) {
    if(argc == 1){
        cout << "Please enter filename" << endl;
        return 0;
    }
    string file = argv[1];

    testFormats(file);
}
