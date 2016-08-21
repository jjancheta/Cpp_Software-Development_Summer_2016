// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Order implementation

#include "Util.h"
#include "o.h"

using namespace std;

//*************class Order****************
Order::Order(vector<string>field){
	if (field.size() >= 3){
		if (validCustomerName(field[0]))
			customer = field[0];
		else
			throw string("expected customer name, found a ") + field[0];

		if (validProductName(field[1]))
			product = field[1];
		else
			throw string("expected product name, found a ") + field[0];

		for (int i = 2; i <(int)field.size(); i++){
			if (validItemName(field[i])){
				itemList.push_back(field[i]);
			}
			else
				throw string("expected an item, found a ") + field[0];
		}
	}
	else{
		throw string("expected minimum 3 fields, found ") + to_string(field.size());
	}
}

void Order::print(){
	cout << "customer, product, itemList = "
		<< customer << " | " << product << " | ";
	for (int i = 0; i < (int)itemList.size(); i++){
		cout << itemList[i];
		if (i + 1 < (int)itemList.size())
			cout << " | ";
	}
	cout << endl;
}

void Order::graph(ofstream& os){
	auto f = [&os](string symbol) {os << '"' << symbol << '"'; };
	for (int i = 0; i < (int)itemList.size(); i++){
		f(customer);
		os << "->";
		f(itemList[i]);
		os << "[color=green];" << endl;
	}
}


//*********class OrderManager************

OrderManager::OrderManager(vector<vector<string> > & csvdata){
	int line = 0;
	for (auto field : csvdata){
		try{
			line++;
			OrderList.push_back(Order(field));
		}
		catch (string& e){
			cerr << "Problem with line " << line << endl;
			cerr << e << endl;
		}
	}
}

void OrderManager::print(){
	for (auto t : OrderList){
		t.print();
	}
}

void OrderManager::graph(string filename){
	ofstream of(filename + ".gv");         //save digrapgh file with .gv extension
	if (of.is_open()){
		of << "digraph myGraph{\n";
		for (auto t : OrderList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";       // create a graphic file and save it to a new file with extension .gv.png
	cout << cmd << '\n';
	system(cmd.c_str());          // system command expects a char*
}