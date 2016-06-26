// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 3

#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"

using namespace std;

namespace w3{
	//Default Constructor
	Text::Text(){
		setEmpty();
	}

	//Constructor
	Text::Text(const char* textFile){
		int count = 0;
		string temp;
		fstream file(textFile, ios::in);
		if (file.is_open()){
			while (getline(file, temp)){        //count the number of lines and assign to size_
				size_ = ++count;
			}
			//file.close();
			record_ = new string[count];        //creates dynamic memory

			//fstream file(textFile, ios::in);
			file.clear();						 //clear the error state
			file.seekg(0);						//position the pointer at the beginning of the file
			//is.seekp(0);						//for files, same as seekg(0)
			for (int i = 0; i < count; i++){
				getline(file, record_[i]);      //copy records from file
				auto cr = record_[i].find('\r');
				if (cr != string::npos){
					record_[i].erase(cr);
				}
			}
			file.close();
		}
		else{
			setEmpty();
			cerr << "Cannot open the file " << textFile <<"!" << endl;
			exit(1);

		}
	}

	//return number of records
	size_t Text::size() const{
		return size_;
	}

	//Destructor
	Text::~Text(){
		/*cout << "Deleting....." << endl;*/
		delete[] record_;
	}

	//Assignment Operator
	Text& Text::operator= (const Text& copy){
		if (this != &copy){
			if (record_){
				delete[] record_;
				setEmpty();
			}
			size_ = copy.size_;
			if (size_){
				record_ = new string[size_];
				for (int i = 0; i < size_; i++){
					record_[i] = copy.record_[i];
				}
			}
		}
		return *this;
	}

	//Move Operator
	Text&& Text::operator= (Text&& rhs){
		if (this != &rhs){
			if (record_){
				delete[] record_;
				setEmpty();
			}
			size_ = rhs.size();
			record_ = rhs.record_;
			rhs.setEmpty();
		}
		return std::move(*this);
	}

	/*Text& Text::operator= (Text&& move){
		if (this != &move){
			size_ = move.size_;
			record_ = new string[size_];
			for (int i = 0; i < size_; i++){
				record_[i] = move.record_[i];
			}
			move.setEmpty();                      
		}
		return *this;
	}*/

	//Copy Constructor
	Text::Text(const Text& rhs){
		setEmpty();
		*this = rhs;                                //call assignment operator
	}
	
	//Move Constructor
	Text::Text(Text&& rhs){
		setEmpty();
		*this = move(rhs);                    //call move operator
	}

	//sets object to empty state
	void Text::setEmpty(){
		record_ = nullptr;
		size_ = 0;
	}

	//total lines: 124456
	

}

