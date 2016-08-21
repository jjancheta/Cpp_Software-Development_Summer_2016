// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Job header & implementation

#pragma once
#include <iostream>
#include "o.h"

class Job : public Order{
	std::vector<bool> installed;
public:
	Job(){}
	Job(Order& oo) :Order(oo){
		for (size_t i = 0; i < size(); i++)
			installed.push_back(false);
	}

	bool isComplete(){
		for (auto e : installed)
			if (!e) return false;
		return true;
	}

	void install(int i){ installed[i] = true; }
	void remove(int i){ installed[i] = false; }
	bool isInstalled(int i) { return installed[i]; }
};