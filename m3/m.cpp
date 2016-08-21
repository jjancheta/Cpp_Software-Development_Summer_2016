// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Machine implementation


#include "m.h"

using namespace std;


Machine::Machine(Task& tt, ItemManager& im) :Task(tt), bInstaller(false), bRemover(false), bSink(false){
	classify(im);
}

void Machine::push(Job&& j){
	inputQ.push(move(j));
}

void Machine::print(std::ostream& os){
	os << "Machine Name is " << getName();
	if (bInstaller) os << "<-- installer";
	if (bRemover) os << "<-- remover";
	if (bSink) os << "<-- SINK!";
	if (!bInstaller && !bRemover) os << "<-- neither installer nor remover";
	os << endl;

}

void Machine::classify(ItemManager& im){
	for (size_t i = 0; i < im.size(); i++){
		if (getName() == im.getInstaller(i)) bInstaller = true;
		if (getName() == im.getRemover(i)) bRemover = true;
	}
	if (bInstaller && bRemover){
		throw getName() + "is both an installer and remover. Fix item data and resubmit.";
	}

}

void Machine::run(ItemManager& im, std::vector<Machine>& machineList){
	if (inputQ.empty()) return;

	job = move(inputQ.front());
	inputQ.pop();

	cout << "Job: ";
	job.print();

	if (bSink){
		if (job.isComplete()){
			cout << job.getProduct() << " completed for customer "
				<< job.getCustomer() << endl;
		}
		else{
			throw "Job at sink node " + getName() + " but job is not complete.";
		}
	}

	auto route = [&machineList, this](Job& job, string destination){
		for (auto m = machineList.begin(); m < machineList.end(); m++){
			if (m->getName() == destination){
				m->push(move(job));
				cout << "route moving job from " << this->getName()
					<< " to " << destination << endl;
				break;
			}
		}
	};

	bool didSomething = false;
	if (bInstaller){
		for (size_t item = 0; item < job.size(); item++){
			if (job.isInstalled(item))
				continue;
			string itemName = job.item(item);
			Item* itemPtr = im.find(itemName);
			if (itemPtr && itemPtr->getInstaller() == getName()){
				job.install(item);
				didSomething = true;
			}
			else{
				cout << "item " << itemName << " needs installer "
					<< itemPtr->getInstaller() << ", (not us)" << endl;
			}
		}
	}

	if (bRemover){
		for (size_t item = 0; item < job.size(); item++){
			if (!job.isInstalled(item))
				continue;
			string itemName = job.item(item);
			Item* itemPtr = im.find(itemName);
			if (itemPtr && itemPtr->getRemover() == getName()){
				job.remove(item);
				didSomething = true;
			}
			else{
				cout << "item " << itemName << " needs remover "
					<< itemPtr->getRemover() << ", (not us)" << endl;
			}
		}
	}

	string accept = getAccept();
	string reject = getReject();

	if (!didSomething){
		route(job, accept);
		return;
	}

	if (reject.empty()){
		route(job, accept);
		return;
	}
	
	if (rand() % 2){
		cout << "Machine " << getName() << ": Coin flip job ***PASSED****" << endl;
		route(job, accept);
		return;
	}
	else{
		cout << "Machine " << getName() << ": Coin flip job ***FAILED****" << endl;
		route(job, reject);
		return;
	}
}
