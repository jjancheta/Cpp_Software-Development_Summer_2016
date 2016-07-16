// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#pragma once
#include "iProduct.h"

namespace w7{
	//Product class = derived class (based class: iProduct class)
	class Product : public iProduct {
		int id_;
		double cost_;
	public:
		Product(const int id, const double cost);
		double getCharge() const;
		void display(std::ostream& os) const;
	};

	//Helper functions
	std::ostream& operator<<(std::ostream&, const iProduct&);
	iProduct* readProduct(std::ifstream&);

}