// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#include <iomanip>
#include "Product.h"
#include "TaxableProduct.h"

using namespace std;

namespace w7 {

	//Product Class
	Product::Product(const int id, const double cost):id_(id),cost_(cost) {}

	double Product::getCharge() const {            
		return cost_;
	}

	void Product::display(std::ostream& os) const {
		os << setw(10) << right << id_
		   << setw(10) << right << fixed << setprecision(2) << cost_;
	}

	
	//Helper functions
	ostream& operator<<(ostream& os, const iProduct& out) {
		out.display(os);
		return os;
	}

	iProduct* readProduct(ifstream& is) {
		int idTemp;
		double costTemp;
		char taxTemp;
		iProduct* temp = nullptr;
		
		is >> idTemp >> costTemp;
		is.ignore();             //ignore the space between id and cost in the file stream
		taxTemp = is.get();
		if (taxTemp == '\n'){
			temp = new Product(idTemp, costTemp);
		}
		else if(taxTemp == 'H' || taxTemp =='P'){
			temp = new TaxableProduct(idTemp, costTemp, taxTemp);
		}
		return temp;
	}
}