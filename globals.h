#ifndef globals_h
#define globals_h 1

// THE GLOBAL PARAMETER FOR THIS PROGRAM --------------------------------------
#include <iostream>
#include <math.h>
using namespace std;

// variable types
typedef long SVMINT;
typedef double SVMFLOAT;

// constants
#define MAXSVMINT 2147483647
#define infinity 1e20
#define MAXCHAR 10000
#define PI 3.1415926535

// store the data x value
typedef struct svm_attrib{
	SVMFLOAT att;
	SVMINT index;
} SVM_ATTRIB;

// store the corresponding one data
typedef struct svm_data{
	SVMINT length;
	svm_attrib* data;
	SVMFLOAT y;
} SVM_DATA;

// return the number of a string
SVMFLOAT string2svmfloat(char* s);

#endif