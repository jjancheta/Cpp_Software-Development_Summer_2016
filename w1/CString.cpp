// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 1

#include <iostream>
#include <cstring>
#include "CString.h"

namespace w1{
	CString::CString(const char* S){
		if (S){
			strncpy(str, S, MAX);
			str[MAX] = '\0';
		}
		else{
			str[0] = '\0';	
		}
	}
	
	std::ostream& CString::display(std::ostream& os) const{
		return os << str;
	}

	std::ostream& operator<<(std::ostream& ostr, const CString& out){
		static int count = 0;
		ostr << count << ": ";
		count++;
		return out.display(ostr);
	}
}