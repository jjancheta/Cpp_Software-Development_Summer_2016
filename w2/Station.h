// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 2

#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace w2{
	enum PassType {STUDENT, ADULT};
	class Station{
		std::string stationName;
		int passes[2];
	public:
		Station();
		Station(std::fstream& is);
		void set(const std::string& name, int student, int adult);
		void update(PassType passType, int numPass);
		int inStock(PassType passType) const;
		const std::string& getName() const;

	};
}