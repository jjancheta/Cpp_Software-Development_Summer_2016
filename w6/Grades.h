// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 6

#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Grades{
	std::string* studentNo;
	double* mark;
	int counter;
public:
	Grades() :studentNo(nullptr), mark(nullptr), counter(0){}
	
	Grades(char* fileName){
			std::ifstream file(fileName);
			if (file.is_open()){
				std::string temp;
				int count = 0;
			
				while (getline(file, temp)){
					count++;
				}                      //count number of records/line in the file
				
				file.clear();          //reset the file and bring the file pointer at the beginning
				file.seekg(0);
				counter = count;
				studentNo = new std::string[counter];  
				mark = new double[counter];

				for (int i = 0; i < counter; i++){
					file >> studentNo[i];
					file >> mark[i];
				}
				file.close();
				
			}
			else {
				std::cerr << "File is missing!";
				exit(2);
			}
			
	}

	~Grades(){
		delete[] studentNo;
		delete[] mark;
	}

	template<typename Func>
	void displayGrades(std::ostream& os, Func letterMark) const{
		for (int i = 0; i < counter; i++){
			os << studentNo[i] << " " 
			   << mark[i] << " " 
			   << letterMark(mark[i]) 
			   << std::endl;
		}
	}

};