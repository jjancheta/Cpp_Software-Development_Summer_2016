// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 2

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Stations.h"


using namespace std;

namespace w2{
	Stations::Stations(const char* dataFile):filename(dataFile), stationTable(nullptr), stationCount(0){
		std::fstream is(dataFile, ios::in);
		if (is.is_open()){
			is >> stationCount;
			char c;
			is.get(c);
			if (c != ';') {
				cerr << "Syntax error line 1: expected ';' found " << c << endl;
				exit(1);
			}
			is.ignore(2000, '\n');
			stationTable = new Station[stationCount];
			for (int i = 0; i < stationCount; i++){
				stationTable[i] = Station(is);       //call the Station constructor and pass fstream as an argument
			}
			is.close();
		}
		else{
			cerr << "Cannot open file! " << filename << endl;
			exit(3);
		}
		
	}

	Stations::~Stations(){
		fstream os(filename, ios::out|ios::trunc);    //updates data in the file
		if (os.is_open()) {
			os << stationCount << ";" << endl;
			for (int i = 0; i < stationCount; i++) {
				os << stationTable[i].getName() << ";"
				   << stationTable[i].inStock(STUDENT) << " "
				   << stationTable[i].inStock(ADULT) << endl;
			}
			os.close();
		}
		delete[] stationTable;
		stationTable = nullptr;
	}
    
	void Stations::update() const{
		cout << endl << "Passes Sold :" << endl;
		cout << "-------------" << endl;
		for (int i = 0; i < stationCount; i++) {
			int studentSold, adultSold;
			cout << stationTable[i].getName() << endl;   //get the name of the station
			cout << " Student Passes sold : ";
			cin >> studentSold;
			cout << " Adult Passes sold   : ";
			cin >> adultSold;
			stationTable[i].update(STUDENT, -studentSold); //subtract sold qty
			stationTable[i].update(ADULT, -adultSold);     //subtract sold qty
		}
	}
	
	void Stations::restock() const{
		cout << endl << "Passes Added :" << endl;
		cout << "-------------" << endl;
		for (int i = 0; i < stationCount; i++) {
			int studentAdd, adultAdd;
			cout << stationTable[i].getName() << endl;
			cout << " Student Passes added : ";
			cin >> studentAdd;
			cout << " Adult Passes added   : ";
			cin >> adultAdd;
			stationTable[i].update(STUDENT, studentAdd);  //add new stock 
			stationTable[i].update(ADULT, adultAdd);      //add new stock
		}
	}

	void Stations::report() const{
		cout << endl << "Passes in Stock : Student Adult" << endl;
		cout << "-------------------------------" << endl;
		for (int i = 0; i < stationCount; i++) {
			cout << left << std::setw(20) << stationTable[i].getName()
			     << right << setw(5) << stationTable[i].inStock(STUDENT)
			     << right << setw(6) << stationTable[i].inStock(ADULT) 
				 << endl;
		}	
	}
}