// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: Task header


#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Util.h"

//************class Task******************
class Task{
	std::string name, slots, accept, reject;
	bool validSlots(std::string slots);
public:
	Task(std::vector<std::string>field);
	void print();
	void graph(std::ofstream& os);
	std::string& getName() { return name; }
	std::string& getAccept() { return accept; }
	std::string& getReject() { return reject; }
};

//*********class TaskManager************
class TaskManager{
	std::vector<Task> TaskList;
public:
	TaskManager(std::vector<std::vector<std::string> > & csvdata);
	void print();
	void graph(std::string filename);
	int validate();
	Task* find(std::string nameKey);
};

