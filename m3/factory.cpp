// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Main function

#include "Util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "j.h"
#include "m.h"

using namespace std;

class Factory{
	ItemManager im;
	OrderManager om;
	TaskManager tm;
	vector<Job> jobList;
	vector<Machine> machineList;
public:
	Factory(ItemManager&& IM, OrderManager&& OM, TaskManager&& TM):im(move(IM)), om(move(OM)), tm(move(TM)){
		//step1: Load Machines - 1 machine per task
		for (size_t m = 0; m < tm.size(); m++){
			machineList.push_back(Machine(tm.getTask(m),im));
		}

		//step2: Find source machine
		enum{SOURCE_NOT_FOUND = -1};
		int sourceMachine = SOURCE_NOT_FOUND;

		for (size_t m = 0; m < machineList.size(); m++){
			//cout << machineList[m].getName() << endl;
			if (tm.checkSource(machineList[m].getName()) && !machineList[m].isSink()){
				cout << "Source found:" << machineList[m].getName() << endl;
				if (sourceMachine == SOURCE_NOT_FOUND){
					sourceMachine = m;
				}
				else{
					throw string("Cannot build factory: multiple source! Fix data and resubmit.");
				}
			}
		}

		if (sourceMachine == SOURCE_NOT_FOUND){
			throw string("Cannot build factory: No source found! Fix data and resubmit.");
		}
		
		cout << "Source Machine = " << machineList.size() << ": ";
        machineList[sourceMachine].print(cout);


		//step3: load jobs into soure machine. 1 job per order
		for (size_t j = 0; j < om.size(); j++){
			machineList[sourceMachine].push(move(Job(om.getOrder(j))));
		}

		//step4: Time Loop
		for (int time = 0;; time++){
			cout << "\n\nTIME LOOP TOP, time: " << time << endl;


			bool finished = true;
			for (size_t m = 0; m < machineList.size(); m++){
				if (!machineList[m].empty()){
					finished = false;
					cout << "Machine Scan: " << machineList[m].getName() << " has jobs.\n";
				}
			}
			if (finished){
				cout << "\n*******No Jobs Waiting for processing********\n";
				cout << "********Factory Simulation Complete**********\n";
				break;
			}

			//step5: Machine Loop
			for (size_t m = 0; m < machineList.size(); m++){
				machineList[m].run(im, machineList);
			}
		}
	} 
};


int validate(ItemManager& im, OrderManager& om, TaskManager& tm){
	int errors = 0;
	
	//taskList : checks if accept & reject tasks are available as task names in Task Class
	errors += tm.validate();

	//itemList : checks if installer & remover tasks are available as task names in Task Class
	for (size_t i = 0; i < im.size(); i++){
		string s = im.getInstaller(i);
		if (!tm.find(s)){
			cerr << "cannot find installer task: " << s << endl;
			errors++;
		}

		s = im.getRemover(i);
		if (!tm.find(s)){
			cerr << "cannot find remover task: " << s << endl;
			errors++;
		}
	}

	//orderList : checks if itemList vector are available as item name in Item Class
	for (size_t o = 0; o < om.size(); o++){                 //order index
		for (size_t i = 0; i < om.itemListSize(o); i++){    //item index
			string s = om.getItem(o, i);   
			if (!im.find(s)){
				cerr << "Item: cannot find installer task: " << s << endl;
				errors++;
			}

		}
	}

	if (errors)
		cerr << "Not good, " << errors << " errors in data. Please fix and resubmit." << endl;
	else
		cout << "*************No errors found.**************" << endl;
	
	return errors;
}    //end validate function

//main function
int main(int argc, char* argv[]){
	if (argc != 5){
		cerr << " Usage : " << argv[0] << ":item-csv order-csc task-csv separator-char\n";
		return 1;
	}

	string itemfile = argv[1];
	string orderfile = argv[2];
	string taskfile = argv[3];
	char delimeter = argv[4][0];
	cout << "file delimeter is " << "--> "<< delimeter <<" <--"<< endl;

	try{
		string graphfile;
		vector <vector<string>> itemcsv;
		vector <vector<string>> ordercsv;
		vector <vector<string>> taskcsv;

		readcsv(itemfile, delimeter, itemcsv);
		//printcsv(csvdata);
		ItemManager im(itemcsv);
		im.print();
		im.graph(itemfile);
		cout << endl;

		readcsv(orderfile, delimeter, ordercsv);
		//printcsv(csvdata);
		OrderManager om(ordercsv);
		om.print();
		om.graph(orderfile);
		cout << endl;

		readcsv(taskfile, delimeter, taskcsv);
		//printcsv(csvdata);
		TaskManager tm(taskcsv);
		tm.print();
		tm.graph(taskfile);
		cout << endl;

		int errors = validate(im, om, tm);
		cout << "****Validate returned " << errors << " syntax errors.*****\n\n";
		
		Factory f(move(im), move(om),move(tm));

		cout << "\n******************ALL DONE*******************\n\n";
	}
	
	catch (string& e){
		cerr << e << endl;
	}
}