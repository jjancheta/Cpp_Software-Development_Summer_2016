// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 5



#include <fstream>
#include <string>
#include "Message.h"
using namespace std;

namespace w5 {
	
		Message::Message(){}
		Message::Message(std::ifstream& in, char recDelim){
			name.clear();
			reply.clear();
			text.clear();
			string line;
			//get first line
			getline(in, line, recDelim);
			int index = 0;
			
			//get the name of the user
			while (index < line.size() && line[index] != ' '){
				name += line[index++];
			}
			index++;  //skip space

			//get the name who reply with the message
			if (index < line.size() && line[index] == '@'){
				index++;
				while (index < line.size() && line[index] != ' '){
					reply += line[index++];
				}
				index++;
			}

			//get the message up to end of the line
			while (index < line.size()){
				text += line[index++];
			}
		}

		bool Message::empty() const{
			return text.empty();

		}

		void Message::display(std::ostream& os) const{
			os << "Message" << endl;
			os << " User  : " << name << endl;
			if (!reply.empty()){
				os << " Reply : " << reply << endl;
			}
			os << " Tweet : " << text << endl << endl;
			
		}
}
 