vector<string> format4(string address, string nextAddr, string binary, string label, string hexVal, vector<string> symTable) {

    vector<string> line;
    line.push_back(address);
    line.push_back(label);
    string operand; //operand without @, #, or ,X included
    string currOp; //formatted operand

    //check opcode table for the instruction
    string opCode = "+";
    opCode.append(opcodeTable(binary.substr(0, 6)));
    line.push_back(opCode);                                                                                             //put the opcode into the vector

    //put in operand and any necessary addressing identifiers
    if (binary.substr(6,2).compare("01") == 0) {                                                            // IMMEDIATE ADDRESSING MODE
        currOp.append("#");
        operand = getLabel(symTable, hexVal.substr(4, 4));
        if(operand.compare("") != 0) {                                                                               //indicates that there is an operand for this line
            currOp.append(operand);
        }
        else {                                                                                                          //no symbol for this line, so it immediately addresses an int value
            // use stringstream to convert the hex value to decimal value
            stringstream str;
            int intVal;
            string hexString = hexVal.substr(3, 5);
            str << hexString;
            str >> hex >> intVal;
            currOp.append(to_string(intVal));
        }

    }
    else if (binary.substr(6,2).compare("10") == 0) {                                                           // INDIRECT ADDRESSING MODE
        currOp.append("@");
        operand = getLabel(symTable, hexVal.substr(4, 4));
        currOp.append(operand);
    }
    else {                                                                                                              // SIMPLE ADDRESSING MODE
        if(binary.at(8) == '1') {                                                                                    // INDEXED
            operand = getLabel(symTable,calcAddr(hexVal.substr(4,4), "0", 1));
            currOp.append(operand);
            currOp.append(",X");
        }
        else {
            operand = getLabel(symTable, hexVal.substr(4, 4));
            currOp.append(operand);
        }

    }

    findReg(opCode, hexVal, 4, operand, symTable, nextAddr, binary);

    line.push_back(currOp); //push the operand onto the vector
    line.push_back(hexVal);  //push the object code onto the vector

    return line;
}