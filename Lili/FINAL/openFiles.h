/**
 *Students involve: (Name, account, Red ID)
     *Kotaro Ueoka, cssc1947, (RedID 821442616)
     *Liliana Guerrero, cssc1948, (RedID 821798582)
     *Marie Duffy, cssc1949, (RedID 821505237)
     *Kyle McLain Kane, cssc1950, (RedID 820003555)
 *Class: CS 530, Spring 2020
 *Assignment information: Assignment #2, XE Disassembler
 *Filename: openFiles.h
 */
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

extern vector<string> DECLARATIONS;

vector<string> getLiterals(vector<string> litTable);
vector<string> getLiteralHex(vector<string> literals);
vector<string> getLiteralsObj(vector<string> vectorToSort, vector<string> literals, vector<string> literalsHex);

vector<string> getFormatArray(vector<string> vectorToSort, vector<string> literals);
vector<string> getBinaryValues(vector<string> vectorToBinary);

vector<string> getTRecords(string filePath);
string getHRecord(string filePath);
string getERecord(string filePath);

vector<string> getTRecordsLength(vector<string> tRecords);
vector<string> getTRecordsSubstr(vector<string> tRecords);
vector<string> getTRecordsStartAddress(vector<string> tRecords);
vector<string> addressCalculationWithTRecord(string hRecord, vector<string> tRecordSize, vector<string> tRecordsStartPosition, vector<string> tRecord, vector<string> formats, vector<string> symTable);

vector<string> getSymTable(string filePath);
vector<string> getLitTable(string filePath);
string getLabel(vector<string> symTable, string address);

vector<string> getAllLabels(vector<string> allAddresses, vector<string> symTable);
string getLiteralAtAddress(vector<string> litTable, string address);
#endif //PROGRAM2_OPENFILES_H
