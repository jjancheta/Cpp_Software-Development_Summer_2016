// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 2 - Item implementation

#include "Util.h"
#include "i.h"

using namespace std;

bool Item::validCode(string code){
	//if (!slots.size()) return 0;
	bool result = false;
	for (int i = 0; i < (int)code.size(); i++){
		if (code.size() && isdigit(code[i]))
			result = true;
	}
	return result;
}

Item::Item(vector<string>field){
	switch (field.size()){
	case 5:
		description = field[4];
	case 4:
		if (validCode(field[3])){
			code = field[3];
		}
		else{
			throw string("expected a code , found a ") + field[3];
		}

		if (validTaskName(field[2]))
			remover = field[2];
		else
			throw string("expected a remover, found a ") + field[2];

		if (validTaskName(field[1]))
			installer = field[1];
		else
			throw string("expected a installer, found a ") + field[1];

		if (validItemName(field[0]))
			itemName = field[0];
		else
			throw string("expected a name, found a ") + field[0];
		break;

	default:
		throw string("expected 4 or 5 fields, found ") + to_string(field.size());
	}
}

void Item::print(){
	cout << "itemName, installer, remover, code, [description] = "
		<< itemName << ","
		<< installer << ","
		<< remover << ","
		<< code << ",";
		if (!description.empty()) 
			cout << description << ",";
		cout << endl;
}

void Item::graph(ofstream& os){
	auto f = [&os](string symbol) {os << '"' << symbol << '"'; };
	f("Item: " + itemName);
	os << "->";
	f(installer);
	os << "[color=green];" << endl;
	f("Item: " + itemName);
	os << "->";
	f(remover);
	os << "[color=red];" << endl;
}

//*********class ItemManager************

ItemManager::ItemManager(vector<vector<string> > & csvdata){
	int line = 0;
	for (auto field : csvdata){
		try{
			line++;
			ItemList.push_back(Item(field));
		}
		catch (string& e){
			cerr << "Problem with line " << line << endl;
			cerr << e << endl;
		}
	}
}

void ItemManager::print(){
	for (auto t : ItemList){
		t.print();
	}
}

void ItemManager::graph(string filename){
	ofstream of(filename + ".gv");         //save digrapgh file with .gv extension
	if (of.is_open()){
		of << "digraph myGraph{\n";
		for (auto t : ItemList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";       // create a graphic file and save it to a new file with extension .gv.png
	cout << cmd << '\n';
	system(cmd.c_str());                  // system command expects a char*
}

Item* ItemManager::find(std::string nameKey){
	for (unsigned int i = 0; i < ItemList.size(); i++){
		if (ItemList[i].getName() == nameKey)
			return &ItemList[i];
	}
	return nullptr;
}
