// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 5

#pragma once
#include <fstream>
#include <string>
#include "Message.h"

namespace w5{
	class Notifications{
		size_t count;
		Message* message;
	public:
		Notifications();
		Notifications(const Notifications& rhs);
		Notifications& operator=(const Notifications& rhs);
		Notifications(Notifications&& rhs);
		Notifications&& operator=(Notifications&& rhs);
		~Notifications();
		void operator+=(const Message& msg);
		void display(std::ostream& os) const;
	};

}