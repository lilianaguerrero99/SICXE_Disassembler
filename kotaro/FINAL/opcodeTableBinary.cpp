/**
 *Students involve: (Name, account, Red ID)
 *Kotaro Ueoka, cssc1947, (RedID 821442616)
 *Liliana Guerrero, cssc1948, (RedID 821798582)
 *Marie Duffy, cssc1949, (RedID 821505237)
 *Kyle McLain Kane, cssc1950, (RedID 820003555)
 *Class: CS 530, Spring 2020
 *Assignment information: Assignment #2, XE Disassembler
 *Filename: opcodeTableBinary.cpp
 */

#include "opcodeTableBinary.h"

//string opcodeTableBinary::opTable(string basicString) {
string opcodeTable (string basicString){
    // empty map container
    map<string, string> opcodeTable;

    //Filling the opcodeTableBinary table with Key(opcodeTableBinary number (first 6 bits of their binary form)) and Value (opcodeTableBinary instruction)
    opcodeTable.insert(pair<string, string>("000000", "LDA"));
    opcodeTable.insert(pair<string, string>("000110", "ADD"));
    opcodeTable.insert(pair<string, string>("010110", "ADDF"));
    opcodeTable.insert(pair<string, string>("100100", "ADDR"));

    opcodeTable.insert(pair<string, string>("010000", "AND"));
    opcodeTable.insert(pair<string, string>("101101", "CLEAR"));
    opcodeTable.insert(pair<string, string>("001010", "COMP"));
    opcodeTable.insert(pair<string, string>("100010", "COMPF"));

    opcodeTable.insert(pair<string, string>("101000", "COMPR"));
    opcodeTable.insert(pair<string, string>("001001", "DIV"));
    opcodeTable.insert(pair<string, string>("011001", "DIVF"));
    opcodeTable.insert(pair<string, string>("100111", "DIVR"));

    opcodeTable.insert(pair<string, string>("110001", "FIX"));
    opcodeTable.insert(pair<string, string>("110000", "FLOAT"));
    opcodeTable.insert(pair<string, string>("111101", "HIO"));
    opcodeTable.insert(pair<string, string>("001111", "J"));

    opcodeTable.insert(pair<string, string>("001100", "JEQ"));
    opcodeTable.insert(pair<string, string>("001101", "JGT"));
    opcodeTable.insert(pair<string, string>("001110", "JLT"));
    opcodeTable.insert(pair<string, string>("010010", "JSUB"));

    opcodeTable.insert(pair<string, string>("011010", "LDB"));
    opcodeTable.insert(pair<string, string>("010100", "LDCH"));
    opcodeTable.insert(pair<string, string>("011100", "LDF"));
    opcodeTable.insert(pair<string, string>("000010", "LDL"));

    opcodeTable.insert(pair<string, string>("011011", "LDS"));
    opcodeTable.insert(pair<string, string>("011101", "LDT"));
    opcodeTable.insert(pair<string, string>("000001", "LDX"));
    opcodeTable.insert(pair<string, string>("110100", "LPS"));

    opcodeTable.insert(pair<string, string>("001000", "MUL"));
    opcodeTable.insert(pair<string, string>("011000", "MULF"));
    opcodeTable.insert(pair<string, string>("100110", "MULR"));
    opcodeTable.insert(pair<string, string>("110010", "NORM"));

    opcodeTable.insert(pair<string, string>("010001", "OR"));
    opcodeTable.insert(pair<string, string>("110110", "RD"));
    opcodeTable.insert(pair<string, string>("101011", "RMO"));
    opcodeTable.insert(pair<string, string>("010011", "RSUB"));

    opcodeTable.insert(pair<string, string>("101001", "SHIFTL"));
    opcodeTable.insert(pair<string, string>("101010", "SHIFTR"));
    opcodeTable.insert(pair<string, string>("111100", "SIO"));
    opcodeTable.insert(pair<string, string>("111011", "SSK"));

    opcodeTable.insert(pair<string, string>("000011", "STA"));
    opcodeTable.insert(pair<string, string>("011110", "STB"));
    opcodeTable.insert(pair<string, string>("010101", "STCH"));
    opcodeTable.insert(pair<string, string>("100000", "STF"));

    opcodeTable.insert(pair<string, string>("110101", "STI"));
    opcodeTable.insert(pair<string, string>("000101", "STL"));
    opcodeTable.insert(pair<string, string>("011111", "STS"));
    opcodeTable.insert(pair<string, string>("111010", "STSW"));

    opcodeTable.insert(pair<string, string>("100001", "STT"));
    opcodeTable.insert(pair<string, string>("000100", "STX"));
    opcodeTable.insert(pair<string, string>("000111", "SUB"));
    opcodeTable.insert(pair<string, string>("010111", "SUBF"));

    opcodeTable.insert(pair<string, string>("100101", "SUBR"));
    opcodeTable.insert(pair<string, string>("101100", "SVC"));
    opcodeTable.insert(pair<string, string>("111000", "TD"));
    opcodeTable.insert(pair<string, string>("111110", "TIO"));

    opcodeTable.insert(pair<string, string>("001011", "TIX"));
    opcodeTable.insert(pair<string, string>("101110", "TIXR"));
    opcodeTable.insert(pair<string, string>("110111", "WD"));

    return opcodeTable.at(basicString);                                  //Returns a string of what the opcodeTableBinary instruction is
}
