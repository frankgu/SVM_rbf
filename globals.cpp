#include "globals.h"

SVMFLOAT string2svmfloat(char* s){
	// number =~ [+-]?\d+([.]\d+)?([Ee][+-]?\d+)?
	int size = 0;
	while (s[size] != '\0') size++;

	int char_read = 0;
	SVMFLOAT number = 0;
	int sign = 1;
	// sign
	if ((size > 0) && ('+' == s[0])){
		char_read++;
	}
	else if ((size > 0) && ('-' == s[0])){
		char_read++;
		sign = -1;
	};
	// digits before "."
	while ((char_read<size) && (s[char_read] >= '0') && (s[char_read] <= '9')){
		number = number * 10 + (s[char_read] - '0');
		char_read++;
	};
	// digits after "."
	if ((char_read<size) && (('.' == s[char_read]) || (',' == s[char_read]))){
		SVMFLOAT factor = 0.1;
		char_read++;
		while ((char_read<size) && (s[char_read] >= '0') && (s[char_read] <= '9')){
			number = number + factor*(s[char_read] - '0');
			char_read++;
			factor *= 0.1;
		};
	};
	if (sign<0){
		number = -number;
	};
	// exponent
	if ((char_read<size) && (('e' == s[char_read]) || ('E' == s[char_read]))){
		sign = 1;
		char_read++;
		if ((char_read<size) && ('+' == s[char_read])){
			char_read++;
		}
		else if ((char_read<size) && ('-' == s[char_read])){
			char_read++;
			sign = -1;
		};
		int exponent = 0;
		while ((char_read<size) && (s[char_read] >= '0') && (s[char_read] <= '9')){
			exponent = exponent * 10 + (s[char_read] - '0');
			char_read++;
		};
		number = number*pow(10, sign*exponent);
	};

	return number;
};
