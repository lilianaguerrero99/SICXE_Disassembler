/**
 * Students involve: (Name, account, Red ID)
     * Kotaro Ueoka, cssc1947, (RedID 821442616)
     * Liliana Guerrero, cssc1948, (RedID 821798582)
     * Marie Duffy, cssc1949, (RedID 821505237)
     * Kyle McLain Kane, cssc1950, (RedID 820003555)
 * Class: CS 530, Spring 2020
 * Assignment information: Assignment #2, XE Disassembler
 * Filename: printFiles.h
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

vector<vector<string> > appendSymbol(vector<vector<string> > total, vector<string> symTable, vector<string> addresses1, vector<string> addresses2, vector<string> litTable);

vector<vector<string> > appendStart(vector<vector<string> > total, vector<string> symTable);

vector<vector<string> > appendEnd(vector<vector<string> > total, vector<string> symTable, vector<string> litTable, vector<string> allAddresses);

vector<vector<string> > appendLTORG(vector<vector<string> > total);



void printLis(vector<vector<string> > total);

void printSic(vector<vector<string> > total);

void printTest(vector<vector<string> > total);

void testFormats();


#endif //PROGRAM2_PRINTFILES_H
