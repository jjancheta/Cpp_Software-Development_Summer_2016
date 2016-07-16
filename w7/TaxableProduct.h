// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#pragma once
#include "Product.h"

namespace w7{
	//TaxableProduct class = derived class (based class: Product class)
	class TaxableProduct : public Product {
		char tax_;
	public:
		TaxableProduct(const int id, const double cost, const char tax);
		double getCharge() const;
		void display(std::ostream& os) const;
	};
}
