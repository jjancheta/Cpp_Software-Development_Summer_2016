// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 2 - Item header

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Util.h"

//*************class Item**************************
class Item{
	std::string itemName, installer, remover, code, description;
	bool validCode(std::string code);
public:
	Item(std::vector<std::string>field);
	void print(); 
	void graph(std::ofstream& os);
	std::string& getInstaller() { return installer; }
	std::string& getRemover() { return remover; }
	std::string& getName() { return itemName; }
};

//*********class ItemManager************
class ItemManager{
	std::vector<Item> ItemList;
public:
	ItemManager(std::vector<std::vector<std::string> > & csvdata);
	void print();
	void graph(std::string filename);
	size_t size() { return ItemList.size(); }
	std::string getInstaller(size_t index) { return ItemList[index].getInstaller(); }
	std::string getRemover(size_t index) { return ItemList[index].getRemover(); }
	Item* find(std::string nameKey);
};



