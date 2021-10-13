#include "printFiles.h"

vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable, vector<string> addresses1, vector<string> addresses2) {
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

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> allAddresses) {
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

vector<vector<string> > appendLTORG(vector<vector<string> > total, vector<vector<string> > literalVector) {
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

void printLis(vector<vector<string> > total) {
    ofstream Print("simple.lis");
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
void printSic(vector<vector<string> > total) {
    ofstream Print("simple.sic");
    if (total.size() != 0) {
        Print << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17) << endl;
        //for (vector<string> line : total) {
        for (int i = 0; i < total.size(); i++) {
            Print << total.at(i).at(1) <<  setw(15) ;
            Print << total.at(i).at(2);
            Print  << total.at(i).at(3);
            Print << endl;
        }
    }
    else {
        Print << "Nothing to Print" << endl;
    }
}

void printTest(vector<vector<string> > total) {
    if (total.size() != 0) {
        cout << "ADDRESS" << setw(9) << "LABEL" << setw(12) << "OPCODE" << setw(15) << "OPERAND" << setw(17) << "OBJECT CODE" << endl;
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
    vector<vector<string> > literalsVector = getLiteralVector(litTable);  // ["Literal", "Address"], ["Literal", "Address"]

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