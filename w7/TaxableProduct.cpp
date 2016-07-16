// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#include "TaxableProduct.h"

namespace w7{
	//TaxableProduct Class
	TaxableProduct::TaxableProduct(const int id, const double cost, const char tax) :Product(id, cost), tax_(tax) {}

	double TaxableProduct::getCharge() const {
		return Product::getCharge() * (tax_ == 'H' ? 1.13 : 1.08);
	}

	void TaxableProduct::display(std::ostream& os) const {
		Product::display(os);
		os << " " << (tax_ == 'H' ? "HST" : "PST");
	}

}