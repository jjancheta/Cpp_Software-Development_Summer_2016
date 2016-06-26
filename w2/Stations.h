// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 2

#pragma once
#include <iostream>
#include <string>
#include "Station.h"

namespace w2{
	class Stations{
		const char* filename;
		Station* stationTable;
		int stationCount;	
	public:
		Stations();
		Stations(const char* dataFile);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};
}  //namespace w2