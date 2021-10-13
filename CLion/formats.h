#ifndef PROGRAM2_FORMATS_H
#define PROGRAM2_FORMATS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include "opcodeTableBinary.h"
#include "openFiles.h"

using namespace std;
extern bool lTorg;
vector<string> format1(string address, string sortedAndBinarySTR, string label, string objectCode);

string registers(string key);

vector<string> format2(string address, string sortedAndBinarySTR, string label, string objectCode);

void findBase (string hex, string binary);

string calcAddr (string one, string two, int index);

vector<string> format3(string address, string binary, string label, string hexVal, vector<string> symTable,  vector<string> allAddresses, vector<string> literals, vector<string> litTable);

vector<string> format4(string address, string binary, string label, string hex, vector<string> symTable);

vector<vector<string> > masterFormat(vector<vector<string> > total, vector<string> address, vector<string> sortedByFormatSTR, vector<string> sortedAndBinarySTR, vector<string> labels, vector<string> symTable,  vector<string> allAddresses, vector<string> literals, vector<string> litTable);
vector<vector<string> > appendLiteral(vector<vector<string> > total, vector<string> litTable, vector<string> symTable, vector<string> literals);
#endif //PROGRAM2_FORMATS_H
