// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 2

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Station.h"

using namespace std;

namespace w2{
	Station::Station(){
		stationName = "";
		passes[STUDENT] = 0;
		passes[ADULT] = 0;
	}

	Station::Station(fstream& is){
		string name;
		int S, A;
		getline(is, name, ';');  //reads from the file until it reaches semi-colon
		is >> S;                 //reads from the file the number of student passes
		is >> A;                 //reads from the file the number of adult passes
		is.ignore(2000, '\n');   //ignore all characters until reaches the \n and proceed to the next line
		set(name, S, A);         //assign read data to the private members

	}
	
	void Station::set(const std::string& name, int student, int adult){
			stationName = name;
			passes[STUDENT] = student;
			passes[ADULT] = adult;
	}

	void Station::update(PassType passType, int numPasses){
			passes[passType] += numPasses;
	}

	int Station::inStock(PassType passType) const{
		return passes[passType];
	}

	const std::string& Station::getName() const{
		return stationName;
	}
}