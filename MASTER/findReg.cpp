void findReg(string opcode, string hex, int format, string operand, vector<string> symTable, string nextAddr, string binary) {

    //length of the hex object code
    int size = hex.length() / 2;
    int startSub;
    if (format == 3) {
        startSub = 3;
    } else if (format == 4) {
        startSub = 4;
    }

    string find = opcode;
    string symAddr;

    //passIndex value represents the X flag (indexed)
    int passIndex = 0;
    if(binary.at(8)== '1') {
        passIndex = 1;
    }

    if (operand.compare("") == 0) {                                                                                  //means there is no symbol (i.e. LDA #5)
        format = 4;                                                                                                     //even if format = 3, it will behave the same as 4 in this case
    } else {                                                                                                            //there is a symbol, so calculate its address (i.e. TABLE = 1791)
        symAddr = calcAddr(hex.substr(startSub, size), nextAddr, passIndex);
    }

    //A register
    if (find.compare("LDA") == 0) {
        if (format == 4) {
            reg.setValue("A", hex.substr(startSub, size));
        } else {                                                                                                        //store the symbol's address into the register
            reg.setValue("A",symAddr);
        }
    }
    //B register
    if (find.compare("LDB") == 0) {
        if (format == 4) {
            reg.setValue("B", hex.substr(startSub, size));
        } else {
            reg.setValue("B",symAddr);
        }
        //base = hex.substr(startSub, size);
        //reg.setValue("B", base);
    }
    //F register
    if (find.compare("LDF") == 0) {
        if (format == 4) {
            reg.setValue("F", hex.substr(startSub, size));
        }
        else {
            reg.setValue("F",symAddr);
        }
    }
    //L register
    if (find.compare("LDL") == 0) {
        if (format == 4) {
            reg.setValue("L", hex.substr(startSub, size));
        }
        else {
            reg.setValue("L",symAddr);
        }
    }
    //X register
    if (find.compare("LDX") == 0) {
        if (format == 4) {
            reg.setValue("X", hex.substr(startSub, size));
        }
        else {
            reg.setValue("X",symAddr);
        }
    }
    //S register
    if (find.compare("LDS") == 0) {
        if (format == 4) {
            reg.setValue("S", hex.substr(startSub, size));
        }
        else {
            reg.setValue("S",symAddr);
        }

    }
    //T register
    if (find.compare("LDT") == 0) {
        if (format == 4) {
            reg.setValue("T", hex.substr(startSub, size));
        }
        else {
            reg.setValue("T",symAddr);
        }

    }
}