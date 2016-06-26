// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 1

//#ifndef W1_CSTRING_H_
//#define W1_CSTRING_H_

#pragma once

#include <iostream>
#define MAX 3

namespace w1{
	class CString{
		char str[MAX+1];
	public:
		CString(const char* S);
		std::ostream& display(std::ostream& os) const;
	};

	std::ostream& operator<<(std::ostream& ostr, const CString& out);
}

//#endif