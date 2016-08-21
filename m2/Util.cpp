// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: Util implementation

#include "Util.h"
using namespace std;

bool validTaskName(string name){
	bool result = false;
	if (name.size() && isalpha(name[0])){
		result = true;
	}
	return result;
}

bool validItemName(string name){
	bool result = false;
	if (name.size() && isalpha(name[0])){
		result = true;
	}
	return result;
}

bool validCustomerName(string name){
	bool result = false;
	if (name.size() && isalpha(name[0])){
		result = true;
	}
	return result;
}

bool validProductName(string name){
	bool result = false;
	if (name.size() && isalpha(name[0])){
		result = true;
	}
	return result;
}

void printcsv(vector <vector<string>>& csvdata){

	////loop using indeces
	//for (int line = 0; line < csvdata.size(); line++){
	//	for (int column = 0; column < csvdata[line].size(); column++){
	//		cout << "[" << csvdata[line][column] << "]";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	////loop with iterators
	//for (auto line = csvdata.begin(); line != csvdata.end(); line++){
	//	for (auto column = line->begin(); column <line->end(); column++){
	//		cout << "<" << *column << ">";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	// loop using range-based
	for (auto line : csvdata){
		for (auto column : line){
			cout << "{" << column << "}";
		}
		cout << endl;
	}
	cout << endl;
}

void trimSpaces(string& s){
	//while (s.size() && s[0] == ' '){                  // trim leading spaces             
	while (s.size() && isspace(s[0])){
		s.erase(0, 1);
	}
	//while (s.size() && s[s.size() - 1] == ' '){       //trim trailing spaces
	while (s.size() && isspace(s[s.size() - 1])){
		s.erase(s.size() - 1, 1);
	}

}

void readcsv(string& filename, char delimeter, vector <vector<string>>& csvdata){
	ifstream is(filename);
	if (!is.is_open()){
		throw ("Cannot open file ") + filename;
	}

	//int count = 0;
	string line;
	while (getline(is, line)){
		auto cr = line.find('\r');
		if (cr != string::npos){
			line.erase(cr);
		}
		string field;
		unsigned column = 0;
		//int numField = 0;
		vector<string> columnData;
		trimSpaces(line);
		if (line.size()){                                 //save only non-empty line
			//cout << "line" << ++count << ":" << line << endl;
			while (column < line.size()){
				if (line[column] == delimeter){
					column++;                             // skip delimeter
					trimSpaces(field);
					if (!field.empty()){
						//cout << "field" << ++numField << "= " << field << endl;
						columnData.push_back(field);
					}
					field.clear();
				}
				field += line[column];
				column++;
			}
			trimSpaces(field);                            //last record 
			if (!field.empty() && (int)field[0]){         //only save non-empty field to inner vector
				//cout << "field" << ++numField << "= " << field << endl;
				columnData.push_back(field);
			}
			field.clear();
			if (!columnData.empty()){                    //only save non-empty vector to outer vector
				csvdata.push_back(columnData);
			}
			columnData.clear();
			//cout << endl;
		}
		
	}
	is.close();
}
