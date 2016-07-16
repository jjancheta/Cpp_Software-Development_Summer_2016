// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 7

#include <string>
#include "Sale.h"
#include "Product.h"
using namespace std;

namespace w7 {
	Sale::Sale(const char* fn) {
		string temp;
		std::ifstream file(fn);
		while (file.good())	{
			iProduct* ip = readProduct(file);
			productList.push_back(ip);
		}
		productList.pop_back();
		file.close();
	}

	void Sale::display(std::ostream& os)	{
		double total = 0;
		os << "Product No      Cost Taxable" << endl;
		for (auto p : productList){
			os << *p << endl;
			total += p->getCharge();
		}
		os << setw(10) << right << "Total" 
		   << setw(10) << right << total << endl;
	}
}