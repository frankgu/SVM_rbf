// The c++ standard library that this program used
#include <iostream>
#include <fstream>
// Customize file 
#include "globals.h"
#include "data.h"

// Using the namespace
using namespace std;

// global svm objects
data* training_set = 0;

// read input data from the file function
void read_input(istream& input_stream, char* filename);

int main(int argc, char* argv[]){
	// first read data from the file 
	ifstream input_file("training.dat");
	if (input_file.bad()) {
		cout << "ERROR: Could not read file " << endl;
		exit(1);
	};
	read_input(input_file, "training.dat");
	input_file.close();
}

void read_input(istream& input_stream, char* filename){
	// read the training data
	char *s = new char[MAXCHAR];
	char next;
	next = input_stream.peek();
	if (next == EOF) {
		// set the stream to end of file
		next = input_stream.get();
	}
	// the while loop to read the data
	while (!input_stream.eof()){
		if ('#' == next){
			// ignore comment
			input_stream.getline(s, MAXCHAR);
		}
		else if (('\n' == next) ||
			(' ' == next) ||
			('\r' == next) ||
			('\f' == next) ||
			('\t' == next)){
			// ignore these key words
			next = input_stream.get();
		}
		else {
			// start to read the data from the stream 
			if (0 == training_set){
				// input the training set
				training_set = new data();
				input_stream >> *training_set;
				// set the training set file name 
				training_set->set_filename(filename);
				
			}
		}
	}

}