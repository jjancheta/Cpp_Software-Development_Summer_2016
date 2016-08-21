// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 3 - Task implementation

#include "Util.h"
#include "t.h"

using namespace std;

//***********class Task*******************

bool Task::validSlots(string slots){
	//if (!slots.size()) return 0;
	bool result = false;
	for (int i = 0; i < (int)slots.size(); i++){
		if (slots.size() && isdigit(slots[i]))
			result = true;
	}
	return result;
}


Task::Task(vector<string>field) :slots("1"){
	switch (field.size()){
	case 4:
		if (validTaskName(field[3]))
			reject = field[3];
		else
			throw string("expected a name, found a ") + field[3];
	case 3:
		if (validTaskName(field[2]))
			accept = field[2];
		else
			throw string("expected a name, found a ") + field[2];
	case 2:
		if (validSlots(field[1]))
			slots = field[1];
		else
			throw string("expected a slot, found a ") + field[1];
	case 1:
		if (validTaskName(field[0]))
			name = field[0];
		else
			throw string("expected a name, found a ") + field[0];
		break;
	default:
		throw string("expected 1,2,3 or 4 fields, found ") + to_string(field.size());
		}
	}

void Task::print(){
	cout << "name, slots, accept, reject = "
		<< name << ","
		<< slots << ","
		<< accept << ","
		<< reject << "," << endl;
}

void Task::graph(ofstream& os){
	auto f = [&os](string symbol) {os << '"' << symbol << '"'; };
	if (!accept.empty()){
		f(name);
		os << "->"; f(accept);  
		os << "[color=green];\n";
	}
	if (!reject.empty()){
		f(name); 
		os << "->"; 
		f(reject);  
		os << "[color=red];\n";
	}
	if (accept.empty() && reject.empty()){
	    f(name); 
		os << endl;
	}
}


//*********class TaskManager************

TaskManager::TaskManager(vector<vector<string> > & csvdata){
	int line = 0;
	for (auto field : csvdata){
		try{
			line++;
			TaskList.push_back(Task(field));
		}
		catch (string& e){
			cerr << "Problem with line " << line << endl;
			cerr << e << endl;
		}
	}
}

void TaskManager::print(){
	for (auto t : TaskList){
		t.print();
	}
}

void TaskManager::graph(string filename){
	ofstream of(filename + ".gv");         //save digrapgh file with .gv extension
	if (of.is_open()){
		of << "digraph myGraph{\n";
		for (auto t : TaskList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";       // create a graphic file and save it to a new file with extension .gv.png
	cout << cmd << '\n';
	system(cmd.c_str());       // system command expects a char*
}

int TaskManager :: validate(){
	int errors = 0;
	for (unsigned int i = 0; i < TaskList.size(); i++){
		string s = TaskList[i].getAccept();
		if (!s.empty()){
			if (!find(s)){
				cerr << "Cannot find accept task" << s << endl;
				errors++;
			}
		}

		s = TaskList[i].getReject();
		if (!s.empty()){
			if (!find(s)){
				cerr << "Cannot find reject task" << s << endl;
				errors++;
			}
		}
	}
	return errors;
}


Task* TaskManager::find(std::string nameKey){
	for (unsigned int i = 0; i < TaskList.size(); i++){
		if (TaskList[i].getName() == nameKey)
			return &TaskList[i];
	}
	return nullptr;
}

bool TaskManager::checkSource(std::string taskName){
	for (size_t i = 0; i < size(); i++){
		if (TaskList[i].getAccept() == taskName
			|| TaskList[i].getReject() == taskName){
			return false;
			break;
		}
	}
	return true;
}