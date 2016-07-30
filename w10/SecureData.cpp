// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 10  // Implemented backup and secure functions & created threading in code function


// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "SecureData.h"

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++){
			t[i] = c(t[i], key);         //assign new value for t[i] with the bitwise XOR result of t[i] & key 
		
		}
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];        //memory allocation as per total char of the file including whitespaces

		int i = 0;
		while (input.good())
			input >> text[i++];            //write content of the file to text variable  
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	void SecureData::code(char key) {
		//converter(text, key, nbytes, Cryptor());
		std::thread t1(std::bind(converter, text, key, nbytes / 2, Cryptor()));
		
		//this points the mid element of text array and put it as thread 2
		std::thread t2(std::bind(converter, text + nbytes / 2, key, nbytes - (nbytes / 2), Cryptor()));
		t1.join();
		t2.join();
		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			std::fstream input(file, std::ios::out|std::ios::binary | std::ios::trunc);
			// write binary file here
			if (!input.is_open()){
				throw std::string("\n***Failed to open file ") +
					std::string(file) + std::string(" ***\n");
			}
			input << text;
			input.close();
		}
	}

	void SecureData::restore(const char* file, char key) {
		// open binary file
		std::fstream input(file, std::ios::in | std::ios::binary);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		
		// de/allocate memory here
		if (text){
			delete[] text;
		}
		text = new char[nbytes + 1];        //memory allocation as per total char of the file including whitespaces
		
		// read binary file here
		int i = 0;
		while (input.good())
			input >> text[i++];            //write content of the file to text variable  
		text[--i] = '\0';

		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;
		input.close();

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}

}