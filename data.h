#pragma once

#include <iostream>
#include "globals.h"

using namespace std;

// STORAGE CLASS FOR THE DATA -------------------------------------------------
class data
{
	char *filename; // name of the file data were read from
	SVMINT data_total; // number of datas in the set
	svm_data *the_data; // vector of data, each a array of dim + 1 SVMFLOATS (x,y)
	SVMINT capacity; // capacity of the_data
	SVMINT dim; // dimensionality of the datas

public:
	// set the filename
	void set_filename(char* new_filename){strcpy(filename, new_filename);};
	// get the filename
	char* get_filename(){ return(filename); };

	// the main function used to read the data from a data stream
	friend istream& operator >> (istream& data_stream, data& datas);
	
	// Constructor: Get Number of datas and dimensionality and set up data structures
	data();
	data(SVMINT new_total, SVMINT new_dim);
	void init(SVMINT new_total, SVMINT new_dim);
	
	// Destructor: remove all the alle data
	~data();

	// Get the dimension of the data
	SVMINT get_dim(){return dim;};
	void set_dim(SVMINT new_dim){ dim = new_dim; };

	// change the number of the_data
	void resize(SVMINT new_total);

	// Access function to the data
	void put_data(const SVMINT pos, const SVMFLOAT* data);
	void put_data(const SVMFLOAT* data); // add one data
	svm_data get_data(const SVMINT index) { return the_data[index]; }
	
};

istream& operator>> (istream& data_stream, data& datas);

