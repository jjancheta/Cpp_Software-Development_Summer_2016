// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 5

#pragma once
#include <fstream>
#include <string>

namespace w5{
	class Message{
		std::string name, reply, text;
	public:
		Message();
		Message(std::ifstream& in, char recDelim);
		bool empty() const;
		void display(std::ostream& os) const;
	};

}