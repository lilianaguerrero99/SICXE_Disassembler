//
// Created by lilia on 3/26/2020.
//

#ifndef PROGRAM2_FORMATS_H
#define PROGRAM2_FORMATS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include "opcodeTableBinary.cpp"

using namespace std;
string base;
int insideX;

vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode);

string registers(string key);

vector<string> format2(string address, string sortedAndBinarySTR, string label, string objectCode);

void findBase (string hex, string binary);

string calcTA (string disp, int index, int format);

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string>> literalsVector);

vector<string> format4(string address, string binary, string label, string hex, vector<string> symTable);

vector<vector<string>> masterFormat(vector<vector<string>> total, vector<string> address, vector<string> sortedByFormatSTR, vector<string> sortedAndBinarySTR, vector<string> labels, vector<string> symTable, vector<string> allAddresses, vector<string> literals, vector<vector<string>> literalsVector);

#endif //PROGRAM2_FORMATS_H
