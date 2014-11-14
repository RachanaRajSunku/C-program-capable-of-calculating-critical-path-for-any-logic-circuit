//---------------------------------------------------------------------------------------------------------------------//
//
// ECE 474A/574A - Example C++ program with support for checking commandling arguments required for Assignment 1
//
// Author: Roman Lysecky (this should be changed to your name before submitting)
// Date: 01-12-2010
//
//---------------------------------------------------------------------------------------------------------------------//

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	
	if( argc != 4 && argc != 5 ) {
		cerr << endl << "Usage: " << argv[0] << " -cp techlib netlist " << endl << endl;
		return -1;
	}
	
	if( string(argv[1]) == "-cp") {
		if( argc != 4 ) {
			cerr << endl << "Usage: " << argv[0] << " -cp techlib netlist" << endl << endl;
			return -1;
		}

		cout << "Command Executed: " << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << endl;
	}
	else {
		cerr << endl << "Usage: " << argv[0] << " -cp techlib netlist" << endl << endl;
		return -1;
	}
	
	return 0;
}
