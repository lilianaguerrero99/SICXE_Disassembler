//
// Created by lilia on 3/26/2020.
//

#ifndef PROGRAM2_PRINTFILES_H
#define PROGRAM2_PRINTFILES_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "openFiles.cpp"
#include "formats.cpp"

using namespace std;

vector<vector<string>> appendSymbol(vector<vector<string>> total, vector<string> symTable, vector<string> addresses1, vector<string> addresses2);

vector<vector<string>> appendStart(vector<vector<string>> total, vector<string> symTable);

vector<vector<string>> appendEnd(vector<vector<string>> total, vector<string> symTable, vector<string> allAddresses);

vector<vector<string>> appendLTORG(vector<vector<string>> total, vector<vector<string>> literalVector);

void printLis(vector<vector<string>> total);

void printSic(vector<vector<string>> total);

void printTest(vector<vector<string>> total);

void testFormats();

int main();

#endif //PROGRAM2_PRINTFILES_H
