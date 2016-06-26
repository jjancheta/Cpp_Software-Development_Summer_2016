// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 1

#include <iostream>
#include "CString.h"
#include "Process.h"

using namespace std;

int main(int argc, char *argv[]) {
	int errorCode = 0;
	int i;
	
	cout << "Command Line : ";
	for (i = 0; i < argc; i++){
		cout << argv[i] << " ";
	}
	
	if (argc > 1){
		cout << endl << "Maximum number of characters stored : " << MAX << endl;
		for (i = 1; i < argc; i++){
			process(argv[i]);
		}
	}
	else{
		cout << endl << "Insufficient number of arguments (min 1)" << endl;
		errorCode++;
	}

	return errorCode;
}




