#ifndef PROGRAM2_PRINTFILES_H
#define PROGRAM2_PRINTFILES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "openFiles.h"
#include "formats.h"

using namespace std;

vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable, vector<string> allAddresses,  string hRecord);

vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable, string hRecord);

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses);

vector<vector<string> > appendLTORG(vector<vector<string> > total);



void printLis(vector<vector<string> > total);

void printSic(vector<vector<string> > total);

void printTest(vector<vector<string> > total);

void testFormats();


#endif //PROGRAM2_PRINTFILES_H
