// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 5


#include <iostream>
#include "Notifications.h"
using namespace std;


namespace w5{
	static const int NOTIFICATIONS_MAX = 10;
	//default constructor
	Notifications::Notifications():count(0),message(new Message[NOTIFICATIONS_MAX]){}
	
	//copy constructor
	Notifications::Notifications(const Notifications& rhs):count(0), message(new Message[NOTIFICATIONS_MAX]){
			count = rhs.count;
			for (int i = 0; i < count; i++){
				message[i] = rhs.message[i];
			}
		}
	
	//copy assignment operator
	Notifications& Notifications::operator=(const Notifications& rhs){
			if (this != &rhs){
				if (!message){
					message = new Message[NOTIFICATIONS_MAX];
				}
				count = rhs.count;
				for (int i = 0; i < count; i++){
					message[i] = rhs.message[i];
				}
			}
			return *this;
		}

	//move constructor
	Notifications::Notifications(Notifications&& rhs):count(rhs.count), message(rhs.message){
			rhs.count = 0;
			rhs.message = nullptr;
		}

	//move assignment operator
	Notifications&& Notifications::operator=(Notifications&& rhs){
			if (this != &rhs){
				delete[] message;
				count = rhs.count;
				message = rhs.message;

				rhs.count = 0;
				rhs.message = nullptr;
			}
			return move(*this);
		}
	
	//destructor
	Notifications::~Notifications(){
			delete[] message;

		}
	
	void Notifications::operator+=(const Message& msg){
			if (count < NOTIFICATIONS_MAX){
				message[count] = msg;
				count++;
			}

		}
		
	void Notifications::display(std::ostream& os) const{
			for (int i = 0; i < count; i++){
				message[i].display(os);
			}
		}
}