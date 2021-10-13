#include "printFiles.h"

vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable,  vector<string> addresses1, vector<string> addresses2, vector<string> litTable) {
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
                int size;
                if ((next - curr) % 3 == 0) {
                     size = (next - curr) / 3;
                    toAdd.push_back("RESW");
                } else {
                    size = next - curr;
                    toAdd.push_back("RESB");
                }


                toAdd.push_back(to_string(size));
                toAdd.push_back("");
                total.push_back(toAdd);

            }
        }
    }
    return total;
}

vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable) {
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

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses) {
    vector<string> toAdd;
    string address = symTable.at(1).substr(10, 4);
    toAdd.push_back("");
    toAdd.push_back("END");
    toAdd.push_back(getLabel(symTable, address));
    toAdd.push_back("");
    toAdd.push_back("");
    total.push_back(toAdd);
    return total;

}

vector<vector<string> > appendLTORG(vector<vector<string> > total) {
    vector<string> toAdd;
    if(lTorg) {
        toAdd.push_back("");
        toAdd.push_back("");
        toAdd.push_back("LTORG");
        toAdd.push_back("");
        toAdd.push_back("");
        total.push_back(toAdd);
    }

    return total;
}

void printLis(vector<vector<string> > total, string fileName) {
    string file;
    file.append(fileName);
    file.append(".lis");
    ofstream Print(file);
    if (total.size() != 0) {
        Print << "ADDRESS" << setw(9) << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17) << "OBJECT CODE" << endl;
        for (vector<string> line : total) {
            Print << line.at(0);
            Print << setw(12) << line.at(1);  // Print Label
            Print << setw(12) << line.at(2);  // Print Opcode
            Print << setw(15) << line.at(3); // Print Operand
            Print << setw(15) << line.at(4); // Print Object Code
            Print << endl;

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
        Print << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17) << endl;
        //for (vector<string> line : total) {
        for (int i = 0; i < total.size(); i++) {
            int firstLine = total.at(i).at(1).length();
            if(total.at(i).at(1).compare("")==0){
                Print << setw(15);
            }else {
                Print << total.at(i).at(1) <<  setw(15-firstLine) ;
            }


            Print << endl;
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
        int addressSpaceConts = 13;
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

    // Separate symbol table into symTable and litTable
    vector<string> symTable = getSymTable(symFilePath);
    vector<string> litTable = getLitTable(symFilePath);

    vector<string> sorted; // Separate tRecord by Object Code/Format
    vector<string> binarySorted; // Convert Object Code to binary

    vector<string> literals = getLiterals(litTable); // ["Literal", "Literal", "Literal]
    vector<string> literalsOBj  = getLiteralsObj(getTRecordsSubstr(tRecords), literals ,getLiteralHex(literals));


    if (tRecords.size() != 0) {
        sorted = getFormatArray(getTRecordsSubstr(tRecords), literals);  // Store return value into sorted;
        binarySorted = getBinaryValues(sorted);  // Store binary value into binarySorted;
    }
    vector<string> allAddresses;
    vector<string> stringAddresses;
    if (hRecord.size() != 0) {
        stringAddresses = calculateAddresses(hRecord, sorted, symTable);  // Addresses exculding RESW/RESB in  in string format
        allAddresses = getAllAddresses(stringAddresses, symTable, hRecord);  // All Addresses including RESW/RESB in string format
    }



    vector<string> allLabels = getAllLabels(allAddresses, symTable);
    vector<vector<string> > total;

    total = appendStart(total, symTable); // Prints First Line

    total = masterFormat(total, allAddresses, sorted, binarySorted, allLabels, symTable,  allAddresses, literalsOBj, litTable); // Prints Object Code Area
    total = appendLiteral(total, litTable, symTable, literalsOBj);

    total = appendLTORG(total);
    total = appendSymbol(total, symTable, stringAddresses, allAddresses, litTable); // Prints Symbol Table Area
    total = appendEnd(total, symTable, litTable, allAddresses);  // Prints Last Line

//    printLis(total, filePath);
//    printSic(total, filePath);
    total = insertBase(total, symTable);
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
