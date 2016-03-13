#include "data.h"

data::data()
{
	init(0, 0);
}

data::data(SVMINT new_total, SVMINT new_dim)
{
	init(new_total, new_dim);
}

void data::init(SVMINT new_total, SVMINT new_dim)
{
	// initialize the data
	the_data = new svm_data[1];
	the_data[0].data = 0;
	dim = 0;
	capacity = 0;
	data_total = 0;
	filename = new char[MAXCHAR];
	dim = new_dim;
}


data::~data()
{

}

void data::resize(SVMINT new_total){
	svm_data* new_set = 0;
	SVMINT i;
	if (new_total > capacity){
		// add new space to set
		new_set = new svm_data[new_total];
		// copy old values
		for (i = 0; i < capacity; i++){
			new_set[i] = the_data[i];
		};
		for (i = capacity; i < new_total; i++){
			new_set[i].data = 0;
			new_set[i].length = 0;
		};
		delete[]the_data;
		the_data = new_set;
		capacity = new_total;
	}
	else if (new_total < capacity){
		new_set = new svm_data[new_total];
		// copy remaining values
		for (i = 0; i < new_total; i++){
			new_set[i] = the_data[i];
		};
		// delete obsolete values
		for (i = new_total; i < capacity; i++){
			if (the_data[i].data != 0){
				delete[](the_data[i].data);
				the_data[i].data = 0;
				data_total--;
			};
		};
		delete[]the_data;
		the_data = new_set;
		capacity = new_total;
	};
};

void readnext(istream& i, char* s)
{
	SVMINT pos = 0;
	char next = i.peek();
	if (next == EOF){
		// set stream to eof
		next = i.get();
	};
	// skip whitespace at the beginning 
	while ((!i.eof()) &&
		(('\n' == next) ||
		(' ' == next) ||
		('\t' == next) ||
		('\r' == next) ||
		('\f' == next))){
		i.get();
		next = i.peek();
		if (next == EOF){
			// set stream to eof
			next = i.get();
		};
	};
	// read data
	while ((!i.eof()) &&
		('\n' != next) &&
		(' ' != next) &&
		('\t' != next) &&
		('\r' != next) &&
		('\f' != next) &&
		(pos < MAXCHAR - 1)){
		s[pos] = i.get();
		pos++;
		next = i.peek();
		if (next == EOF){
			// set stream to eof
			next = i.get();
		};
	};
	// set the end of s to be null
	s[pos] = '\0';
	if (!(i.eof() || ('\n' == next))){
		// remove the extra space character
		i.get();
	};
}

istream& operator >> (istream& data_stream, data& datas)
{
	char* s = new char[MAXCHAR]; // next item in the stream
	char next = 0; // first character in the stream
	SVMINT pos; // dummy for pos of attribute in data
	SVMINT dim = datas.get_dim();
	SVMFLOAT* new_data = new SVMFLOAT[dim + 1]; // datas to be inserted

	while ((next != EOF) && (!data_stream.eof())){
		next = data_stream.peek();
		if (next == EOF){
			// set the stream to the end of file
			next = data_stream.get();
		}
		else if (('\n' == next) ||
			(' ' == next) ||
			('\r' == next) ||
			('\f' == next) ||
			('\t' == next)){
			// ignore
			next = data_stream.get();
		}
		else if ('#' == next){
			// line contains commentary
			data_stream.getline(s, MAXCHAR);
		}
		else if (('+' == next) || ('-' == next) ||
			(next >= '0') && (next <= '9')){

			// read all the x values
			for (pos = 0; pos < dim; pos++) {
				readnext(data_stream, s);
				new_data[pos] = string2svmfloat(s);
			}
			// read the y values
			readnext(data_stream, s);
			new_data[dim] = string2svmfloat(s);

			// insert data
			datas.put_data(new_data);
		}
		else {
			// line contains parameter , set the dimension of the data
			data_stream >> s;
			if ((0 == strcmp("dimension", s)) || (0 == strcmp("dim", s))){
				// dimension already set => error
				SVMINT new_dim;
				data_stream >> new_dim;
				datas.set_dim(new_dim);
				dim = new_dim;
				if (new_data != 0){ delete[]new_data; };
				new_data = new SVMFLOAT[dim + 1];
			}
		}
	}

	// clear the memory
	if (new_data) delete[]new_data;
	delete[]s;

	return data_stream;
}

void data::put_data(const SVMINT pos, const SVMFLOAT* data){
	// datas is SVMFLOAT-array 1..dim
	SVMINT non_zero = 0;
	svm_attrib* new_att;
	SVMINT i;
	for (i = 0; i < dim; i++){
		if (0 != data[i]){
			non_zero++;
		};
	};
	if (pos >= capacity){
		// make set bigger
		resize(2 * capacity + 1);
	};
	if (0 == the_data[pos].data){
		// add new data, reserve space for y
		data_total++;
	}
	else{
		delete[](the_data[pos].data);
		the_data[pos].data = 0;
	};
	new_att = new svm_attrib[non_zero];
	the_data[pos].data = new_att;
	// add attributes
	SVMINT j = 0;
	for (i = 0; i < non_zero; i++){
		while (0 == data[j]) j++;
		new_att[i].att = data[j];
		new_att[i].index = j;
		j++;
	};
	the_data[pos].y = data[dim];
	the_data[pos].length = non_zero;
}

void data::put_data(const SVMFLOAT* data){
	put_data(data_total, data);
}
