// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 1


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Util.h"

using namespace std;

//class Task
class Task{
	string name, slots, accept, reject;
	bool validSlots(string slots){
		if (!slots.size()) return 0;
			
		for (unsigned int i = 0; i < slots.size(); i++){
			if (!isdigit(slots[i])) return false;
		}
		return true;
	}
public:
	Task(vector<string>line):slots("1"){
		switch (line.size()){
		case 4:
			if (validTaskName(line[3]))
				reject = line[3];
			else
				throw string("expected a name, found a ") + line[3];
		case 3:
			if (validTaskName(line[2]))
				accept = line[2];
			else
				throw string("expected a name, found a ") + line[2];
		case 2:
			if (validSlots(line[1]))
				slots = line[1];
			else
				throw string("expected a slot, found a ") + line[1];
		case 1:
			if (validTaskName(line[0]))
				name = line[0];
			else
				throw string("expected a name, found a ") + line[0];
			break;
		default:
			throw string("expected 1,2,3 or 4 fields, found ") + to_string(line.size());
		}
	}

	void print(){
		cout << "name, slots, accept, reject ="
			<< name << ","
			<< slots << ","
			<< accept << ","
			<< reject << "," << endl;

	}

	void graph(ofstream& os){
		if (!accept.empty()){
			os << '"' << name << '"' << "->" << '"' << accept << '"' << "[color=green];\n";
		}
		if (!reject.empty()){
			os << '"' << name << '"' << "->" << '"' << reject << '"' << "[color=red];\n";
		}
		if (accept.empty() && reject.empty()){
			os << '"' << name << '"'  << ";\n";
		}
	}

};

//class TaskManager
class TaskManager{
	vector<Task> TaskList;
public:
	TaskManager(vector<vector<string> > & csvdata){
		int line = 0;
		for (auto fields:csvdata){
			try{
				line++;
				TaskList.push_back(Task(fields));
			}
			catch (string& e){
				cerr << "Problem with line " << line << endl;
				cerr << e << endl;
			}
		}
	}
	
	void print(){
		for (auto t : TaskList){
			t.print();
		}
	}

	void graph(string filename){
		ofstream of(filename + ".gv");
		if (of.is_open()){
			of << "digraph myGraph{\n";
			for (auto t : TaskList){
				t.graph(of);
			}
			of << "}\n";
			of.close();
		}
		string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";
		cout << cmd << '\n';
		system(cmd.c_str());    // system expects a char*
	}
};



int main(int argc, char* argv[]){
	if (argc != 3){
		cerr << " Usage : " << argv[0] << ":cs-file separator-char\n";
		return 1;
	}

	string filename = argv[1];
	char delimeter = argv[2][0];
	cout << "file: " << filename << "delimeter is " << delimeter << endl;

	try{
		vector <vector<string>> csvdata;
		readcsv(filename, delimeter, csvdata);
		printcsv(csvdata);

		TaskManager tm(csvdata);
		tm.print();
		tm.graph(filename);
	}
	catch (string& e){
		cerr << e << endl;
	}

}