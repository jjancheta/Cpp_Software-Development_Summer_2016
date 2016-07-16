// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "iProduct.h"

namespace w7 {
	class Sale {
	private:
		std::vector<iProduct*> productList;
	public:
		Sale(const char*);
		void display(std::ostream&);
	};
}