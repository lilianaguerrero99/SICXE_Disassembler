//
// Created by lilia on 3/26/2020.
//

#ifndef PROGRAM2_OPENFILES_H
#define PROGRAM2_OPENFILES_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<vector<string> > getLiteralVector(vector<string> litTable);

vector<string> getLiterals(vector<string> litTable);

vector<string> getFormatArray(vector<string> vectorToSort, vector<string> literals);

vector<string> getBinaryValues(vector<string> vectorToBinary);

vector<string> getTRecords(string filePath);

string getHRecord(string filePath);

string getERecord(string filePath);

vector<string> getTRecordsSubstr(vector<string> tRecords);

vector<string> getSymTable(string filePath);

vector<string> getLitTable(string filePath);

vector<string> calculateAddresses(string header, vector<string> sorted, vector<string> symTable);

vector<string> getAllAddresses(vector<string> addresses, vector<string> symTable, string hRecord);

string getLabel(vector<string> symTable, string address);

vector<string> getAllLabels(vector<string> allAddresses, vector<string> symTable);

#endif //PROGRAM2_OPENFILES_H
