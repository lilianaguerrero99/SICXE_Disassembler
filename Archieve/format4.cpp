//Format 4 method 

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
}