// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Machine header


#pragma once
#include <queue>
#include "t.h"
#include "j.h"
#include "i.h"

class Machine : public Task{
	bool bInstaller;
	bool bRemover;
	bool bSink;
	std::queue<Job> inputQ;
	Job job;
public:
	Machine(Task& tt, ItemManager& im);
	void push(Job&& j);
	bool empty() { return inputQ.empty(); }
	void print(std::ostream& os);
	void classify(ItemManager& im);
	void run(ItemManager& im, std::vector<Machine>& machineList);
	bool isSink(){return getAccept().empty() && getReject().empty(); }
};