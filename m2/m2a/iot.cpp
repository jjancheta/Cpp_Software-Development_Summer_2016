// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 2 - Main function

#include "Util.h"
#include "i.h"
#include "o.h"
#include "t.h"

using namespace std;

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
		cout << "No errors found." << endl;
	
	return errors;
}

int main(int argc, char* argv[]){
	if (argc != 5){
		cerr << " Usage : " << argv[0] << ":item-csv order-csc task-csv separator-char\n";
		return 1;
	}

	string itemfile = argv[1];
	string orderfile = argv[2];
	string taskfile = argv[3];
	char delimeter = argv[4][0];
	cout << "file delimeter is " << delimeter << endl;

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
		cout << "Validate returned " << errors << " syntax errors." << endl;
	}
	
	catch (string& e){
		cerr << e << endl;
	}
}