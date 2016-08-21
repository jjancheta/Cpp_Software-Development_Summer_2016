// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Milestone: 2 - Order header

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Util.h"

//***********class Order******************
class Order{
	std::string customer, product;
	std::vector<std::string> itemList;
public:
	Order(std::vector<std::string>field);
	void print(); 
	void graph(std::ofstream& os);
	size_t size() { return itemList.size(); }
	std::string& item(size_t itemIndex){ return itemList[itemIndex]; }
};

//*********class OrderManager************
class OrderManager{
	std::vector<Order> OrderList;
public:
	OrderManager(std::vector<std::vector<std::string> > & csvdata);
	void print();
	void graph(std::string filename);
	size_t size(){ return OrderList.size(); }
	size_t itemListSize(size_t orderIndex){
		return OrderList[orderIndex].size(); 
	}
	std::string& getItem(size_t orderindex, size_t itemIndex){
		return OrderList[orderindex].item(itemIndex);
	}
};

