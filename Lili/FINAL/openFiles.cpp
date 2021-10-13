/**
 *Students involve: (Name, account, Red ID)
     *Kotaro Ueoka, cssc1947, (RedID 821442616)
     *Liliana Guerrero, cssc1948, (RedID 821798582)
     *Marie Duffy, cssc1949, (RedID 821505237)
     *Kyle McLain Kane, cssc1950, (RedID 820003555)
 *Class: CS 530, Spring 2020
 *Assignment information: Assignment #2, XE Disassembler
 *Filename: openFiles.cpp
 */

#include "openFiles.h"

//Assuming no SIC format 1 commands
//Format 1 (First char should be c or f )
//Format 2 (First char should be 9,a, or b)
//Format 4 (3rd char should be a 1 or 9 for extended bit)
//Format 3 (Default if all cases fall through)

vector<string> DECLARATIONS;

// Find literals in lit table and returns the literal as vector
vector<string> getLiterals(vector<string> litTable) {
    vector<string> literals;
    vector<int> literalSize;
    if(litTable.size()!=0) {

        for (size_t i = 0; i < litTable.size(); i++) {  // Calculate Size of each literal
            char size = litTable.at(i).at(19) - '0';
            literalSize.push_back((int) size);
        }

        for (size_t k = 0; k < litTable.size(); k++) {

            literals.push_back(litTable.at(k).substr(11, literalSize.at(k)));
        }

    }
    return literals;
}

// Convert literals to hex equivalent EOF -> 454F46
vector<string> getLiteralHex(vector<string> literals) {
    vector<string> hexLiterals;
    for(string literal : literals){
        string dat = literal;
        ostringstream os;
        for (size_t j=0; j<dat.length() ; j++){
            os << hex << uppercase << (int) dat[j];
        }
        string hexdat = os.str();
        hexLiterals.push_back(hexdat);
    }
    return hexLiterals;
}

// Finds literals in object file and returns as vector of string
vector<string> getLiteralsObj(vector<string> vectorToSort, vector<string> literals, vector<string> literalsHex) {
    string variable = "";                                                               //Initializing the string that we will be chopping up

    for (size_t i = 0; i < vectorToSort.size(); i++) {                                //For loop to append multiple elements to a single string
        for(size_t j=0; j<vectorToSort.at(i).size(); j++){
            char c = vectorToSort.at(i).at(j);
            if(c != 0x0D){
                variable += c;
            }
        }
    }


    int stringLength = (int) variable.length();                                               //Gets the length of the string we will be chopping up
    vector<string> v;//This is the vector declaration to return our sorted vector

    int i = 0;

    while (i < stringLength) {

        for (size_t k = 0; k < literals.size(); k++) {
            // Convert LITERAL -> HEX
            if (variable.substr(i, literals.at(k).length()).compare(literals.at(k)) == 0 ) {
                v.push_back(variable.substr(i, literals.at(k).length()));

                i += literals.at(k).length();
            }else if(variable.substr(i, literals.at(k).length() * 2).compare(literalsHex.at(k))==0){
                v.push_back(variable.substr(i, literals.at(k).length() * 2));
                i += literals.at(k).length() * 2;
            }
        }
        if(i < stringLength){
            //Format 1 check case (1 byte)
            if(variable.substr(i,4).compare("0000")==0){  // OBJECT WORD
                i += 6;
            }

            else if (variable.at(i) == 'C' || variable.at(i) == 'F') {
                i += 2;
            }
                //Format 2 check case (2 bytes)
            else if (variable.at(i) == '9' || variable.at(i) == 'A' || variable.at(i) == 'B') {
                i += 4;
            }
                //Format 4 check case   (4 bytes)
            else if (variable.at(i + 2) == '1' || variable.at(i + 2) == '9') {
                i += 8;
            }
                //Format 3 default  (3 bytes)
            else {
                i += 6;
            }
        }
    }

    return v;
}

// Splits the formats based on nixbpe
vector<string> getFormatArray(vector<string> vectorToSort, vector<string> literals) {
    string variable = "";                                                               //Initializing the string that we will be chopping up
    for (size_t i = 0; i < vectorToSort.size(); i++) {                                //For loop to append multiple elements to a single string
        for(size_t j=0; j<vectorToSort.at(i).size(); j++){
            char c = vectorToSort.at(i).at(j);
            if(c != 0x0D){
                variable += c;
            }
        }
    }
    int stringLength =  variable.length();                                               //Gets the length of the string we will be chopping up
    vector<string> v;                                                                   //This is the vector declaration to return our sorted vector
    int i = 0;

    while (i < stringLength) {
        // Literal check
        bool isLit = false;
        for (size_t k = 0; k < literals.size(); k++) {

            string lit = literals.at(k);
            if(lit.compare(variable.substr(i,lit.size()))==0){
                v.push_back(lit);

                i += lit.size();
                isLit = true;

            }

        }

        if(!isLit) {
            if(variable.substr(i,4).compare("0000")==0){  // CHECK IF OBJECT WORD
                v.push_back(variable.substr(i,6));
                i += 6;
            }
            else if (variable.at(i) == 'C' || variable.at(i) == 'F') {

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
    }

    return v;
}

// Converts vector from getFormatArray to binary equivalent and returns as vector of strings
vector<string> getBinaryValues(vector<string> vectorToBinary) {
    vector <string> buff;                                                               //Creating a vector to store converted values
    for(size_t i = 0; i < vectorToBinary.size(); i++){                                     //Looping through the vectors elements
        string store = "";                                                              //Reseting the store string/initializing the store string
        for(size_t j = 0; j <vectorToBinary[i].length(); j++){
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

// Get each line that starts with T
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

// Get line that starts with H and returns as string
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

// Returns string that starts with E
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

// Cuts off size and starting address from tRecords
vector<string> getTRecordsSubstr(vector<string> tRecords) {  // Cut out first 9 characters from tRecord and return
    vector<string> tRecordsSubstr;
    for (size_t i = 0; i < tRecords.size(); i++) {  //
        tRecordsSubstr.push_back(tRecords.at(i).substr(9, tRecords.at(i).length()));  // Cut out first 9 characters from tRecord and add to tRecordSubstr
    }
    return tRecordsSubstr;
}

// Returns starting address of TRecord as vector
vector<string> getTRecordsStartAddress(vector<string> tRecords){
    vector<string> startingAddresses;
    for(string line : tRecords){
        startingAddresses.push_back(line.substr(3,4));
    }
    return startingAddresses;
}

// Returns length of each TRecord line
vector<string> getTRecordsLength(vector<string> tRecords){
    vector<string> lengths;
    for(string line : tRecords){
        lengths.push_back(line.substr(7,2));
    }
    return lengths;
}

// Returns all labels in the symbol table that aren't literals
vector<string> getSymTable(string filePath) {  // Returns everything under "Symbol  Value   Flags:" up to blank line or "Name    Literal  Length Address:"
    vector<string> symTable;
    ifstream file(filePath);

    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;
    int currLine = 0;
    bool blank = false;
    while (getline(file,line)) {
        string newLine;
        for(size_t i=0; i< line.length(); i++){  // Create new string without and 0xOD which is "ENTER"
            if(line.at(i) != 0x0D){
                newLine += line.at(i);
            }
        }
        if(newLine.compare("")==0){

            blank = true;
        }
        if(currLine!=0 && currLine!=1 && !blank){  // Push back all symbols
            symTable.push_back(line);
        }
        currLine++;
    }

    file.close();
    return symTable;
}

// Returns all literals in the .sym file
vector<string> getLitTable(string filePath) {
    vector<string> litTable;
    ifstream file(filePath);
    if (!file) {
        cout << "Error opening the file. \n";
    }
    string line;

    int dashCounter = 0;

    while (getline(file, line)) {
        string newLine;
        for(size_t i=0; i< line.length(); i++){  // Create new string without and 0xOD which is "ENTER"
            if(line.at(i) != 0x0D){
                newLine += line.at(i);
            }
        }

        if(dashCounter==2){
            litTable.push_back(newLine);
        }

        if(newLine.compare("")!=0){
            if(newLine.at(0) == '-'){
                dashCounter++;
            }
        }
    }
    file.close();
    return litTable;
}

// Calculate all the addresses in the program based on starting address/ starting address in tRecord/ length of tRecord/ addresses in symbol file
vector<string> addressCalculationWithTRecord(string hRecord, vector<string> tRecordSize, vector<string> tRecordsStartPosition, vector<string> tRecord, vector<string> formats, vector<string> symTable){
    string startingAddress = hRecord.substr(9,4);

    bool running = true;
    vector<string> allAddresses;  // Vector of all address positions
    allAddresses.push_back(startingAddress);
    int currentAddress;
    stringstream ss;
    ss << hex << startingAddress;
    ss >> currentAddress;
    string currAddressString;
    int formatTracker = 0;
    while (running){ // Overall tRecord vector
        for(size_t i=0; i<tRecord.size();i++){

            string line = tRecord.at(i);
            string newLine = "";
            //For loop to append multiple elements to a single string
                for(size_t j=0; j<line.size(); j++){
                    char c = line.at(j);
                    if(c != 0x0D){
                        newLine += c;
                    }
                }


            int lineSize  = line.size() / 2;
            int addressCount = 0;
            while(addressCount < lineSize){  // Within each tRecord line
                stringstream ss1;
                int formatSize = formats.at(formatTracker).size() / 2;
                currentAddress += formatSize;
                addressCount += formatSize;
                ss1 << setfill('0') << setw(4)<< hex <<currentAddress;
                currAddressString = ss1.str();
                transform(currAddressString.begin(), currAddressString.end(), currAddressString.begin(), ::toupper);
                allAddresses.push_back(currAddressString);
                formatTracker++;
            }

            int next;
            string nextAddress;
            if(i+1 < tRecordSize.size()){
                nextAddress = tRecordsStartPosition.at(i+1);
                stringstream ss1;
                ss1 << setfill('0') << setw(4) << hex << nextAddress;
                ss1 >> next;

            }else {
                running = false;
            }

            bool foundInSymbolTable = false;
            for(string line : symTable){
                string symTableAddress = line.substr(10,4);
                int symTableInt;
                stringstream ss2;
                ss2 << hex << symTableAddress;
                ss2 >> symTableInt;
                if(currAddressString.compare(line.substr(10,4))==0){
                    stringstream ss1;
                    currAddressString = line.substr(10,4);
                    ss1 << setfill('0') << setw(4) <<  hex << currAddressString;
                    transform(currAddressString.begin(), currAddressString.end(), currAddressString.begin(), ::toupper);
                    allAddresses.push_back(currAddressString);
                    ss1 >> currentAddress;
                    foundInSymbolTable = true;
                    DECLARATIONS.push_back(currAddressString);

                } else if (symTableInt < next && foundInSymbolTable){
                    stringstream ss1;
                    currAddressString = line.substr(10,4);
                    ss1 << setfill('0') << setw(4) <<  hex << currAddressString;
                    transform(currAddressString.begin(), currAddressString.end(), currAddressString.begin(), ::toupper);
                    allAddresses.push_back(currAddressString);
                    ss1 >> currentAddress;
                    DECLARATIONS.push_back(currAddressString);

                }

            }
            currentAddress = next;
            stringstream ss3;
            ss3 << setfill('0') << setw(4)<< hex << currentAddress;
            currAddressString = ss3.str();
            transform(currAddressString.begin(), currAddressString.end(), currAddressString.begin(), ::toupper);


            allAddresses.push_back(currAddressString);
        }

        running = false;
    }


    for (size_t lpo = 0; lpo < allAddresses.size(); lpo++)
    {
        for (size_t lp = lpo + 1; lp < allAddresses.size(); lp++)  //  lp needs to stay 1 ahead of lpo.
        {
            if (allAddresses[lpo] == allAddresses[lp])
            {
                allAddresses.erase(allAddresses.begin() + lp);  //  Also resizes the vector.
            }
        }
    }

    allAddresses.pop_back();


    return allAddresses;
}

// Returns label from symbol table based on passed in address
string getLabel(vector<string> symTable, string address) {  // Return label in symbol table of given address
    for (size_t i = 1; i < symTable.size(); i++) {
        if (address.compare(symTable.at(i).substr(10, 4)) == 0) {
            string label = symTable.at(i).substr(0, 6);
            label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
            return label;
        }
    }
    return "";
}

// Returns literal based on the address that is passed in
string getLiteralAtAddress(vector<string> litTable, string address){
    for(size_t i=0; i< litTable.size();i++){
        if(address.compare(litTable.at(i).substr(26,4))==0){

            string label = litTable.at(i).substr(11, litTable.at(i).at(19)-'0');
            label.erase(std::remove_if(label.begin(), label.end(), ::isspace), label.end());
            return label;
        }
    }
    return "";
}

// Create parallel vector based on the addresses passed in
vector<string> getAllLabels(vector<string> allAddresses, vector<string> symTable) {  // Creates an array of Labels that is parallel with allAddresses
    vector<string> allLabels;
    for (size_t i = 0; i < allAddresses.size(); i++) {
        allLabels.push_back(getLabel(symTable, allAddresses.at(i)));
    }
    return allLabels;
}