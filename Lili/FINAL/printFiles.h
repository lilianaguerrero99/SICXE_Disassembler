/**
 *Students involve: (Name, account, Red ID)
     *Kotaro Ueoka, cssc1947, (RedID 821442616)
     *Liliana Guerrero, cssc1948, (RedID 821798582)
     *Marie Duffy, cssc1949, (RedID 821505237)
     *Kyle McLain Kane, cssc1950, (RedID 820003555)
 *Class: CS 530, Spring 2020
 *Assignment information: Assignment #2, XE Disassembler
 *Filename: printFiles.h
 */

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

int charToInt (basic_string<char> c);
int stringToInt (string str);
string intToString (int val);

vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable, vector<string> allAddresses,  string hRecord);

vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable, string hRecord);

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses);

vector<vector<string> > appendLTORG(vector<vector<string> > total);

vector<vector<string> > sortTotal(vector<vector<string>> total);

vector<vector<string> >  insertBase (vector<vector<string>> total);

void printLis(vector<vector<string> > total, string fileName);

void printSic(vector<vector<string> > total, string fileName);

void runProgram(string filePath);


#endif //PROGRAM2_PRINTFILES_H
