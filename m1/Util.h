// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: Util header

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool validTaskName(std::string name);
bool validItemName(std::string name);
bool validCustomerName(std::string name);
bool validProductName(std::string name);
void printcsv(std::vector <std::vector<std::string>>& csvdata);
void trimSpaces(std::string& s);
void readcsv(std::string& filename, char delimeter, std::vector <std::vector<std::string>>& csvdata);