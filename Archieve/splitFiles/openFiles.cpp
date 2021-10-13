#include "openFiles.h"

//Assuming no SIC format 1 commands
//Format 1 (First char should be c or f )
//Format 2 (First char should be 9,a, or b)
//Format 4 (3rd char should be a 1 or 9 for extended bit)
//Format 3 (Default if all cases fall through)
vector<vector<string> > getLiteralVector(vector<string> litTable) {
    vector<vector<string> > total; // [["Literal", "Address"], ["Literal", "Address"]]
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

vector<string> getLiterals(vector<string> litTable) {
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

    for (int i = 0; i < lengthOfVectorInElements; i++) {                                //For loop to append multiple elements to a single string
        variable.append(vectorToSort[i]);
    }
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
    vector <string> buff;                                                               //Creating a vector to store converted values
    for(int i = 0; i < vectorToBinary.size(); i++){                                     //Looping through the vectors elements
        string store = "";                                                              //Reseting the store string/initializing the store string
        for(int j = 0; j <vectorToBinary[i].length(); j++){
            stringstream tobin;
            tobin << hex << vectorToBinary[i].at(j);
            unsigned n;
            tobin >> n;
            bitset<4> b(n);
            store.append(b.to_string());
            if(j == vectorToBinary[i].length() - 1){
                buff.push_back(store);
            }
        }
    }
    return buff;
}

vector<string> getTRecords(string filePath) { // Stores each line of Text Record as a vector element and returns the vector
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
        tRecordsSubstr.push_back(tRecords.at(i).substr(9, tRecords.at(i).length()));  // Cut out first 9 characters from tRecord and add to tRecordSubstr
    }
    return tRecordsSubstr;
}

vector<string> getSymTable(string filePath) {  // Returns everything under "Symbol  Value   Flags:" up to blank line or "Name    Literal  Length Address:"
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

vector<string> calculateAddresses(string header, vector<string> sorted, vector<string> symTable) {  // Return Vector of addresses exculding RESW/RESB int format
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

vector<string> getAllAddresses(vector<string> addresses, vector<string> symTable, string hRecord) {  // Return vector of all addresses in string format including RESW and RESB
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

vector<string> getAllLabels(vector<string> allAddresses, vector<string> symTable) {  // Creates an array of Labels that is parallel with allAddresses
    vector<string> allLabels;
    for (int i = 0; i < allAddresses.size(); i++) {
        allLabels.push_back(getLabel(symTable, allAddresses.at(i)));
    }
    return allLabels;
}