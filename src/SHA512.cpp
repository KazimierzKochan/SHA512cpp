/***************************************************************************************
*    Title: SHA512 C++ implementation
*    Author: Kazimierz Kochan
*    Date: April 2022
*    Code version: 1.2
*    Availability: https://github.com/KazimierzKochan/SHA512cpp
*
***************************************************************************************/
#include "SHA512.h"

using namespace std;

/**
* Constructor
*/
SHA512::SHA512(){
}

/**
* Deconstructor
*/
SHA512::~SHA512(){
}

/**
* Calculate and return hash of a given string
*/
string SHA512::hashString(string message){
	string preprocessed = preprocess(message);
	string result = digest(preprocessed);
	return result;
}

string SHA512::hashFile(const string fileName){
	//check if file exists and can be opened
	ifstream inputFile(fileName);
	if(!inputFile.is_open()){
		cerr << "Could not open file: '" << fileName << "'" << endl;
		exit(EXIT_FAILURE);
	}
	//read file
	string fileChars = string(istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>());
	//preprocess
	string preprocessed = preprocess(fileChars);
	//digest
	string result = digest(preprocessed);
	//return
	return result;
}

/**
* Preprocess string message
*/
string SHA512::preprocess(string message){
	//message len in bits
	size_t messageLength = message.size()*8;

	//find k
	//k - number such as, messageLength+1+k is congruent to 896 modulo 1024
	int k = 0;
	do{
		k++;
	}while((messageLength + 1 + k) % 1024 != 896);

	//0b10000000 and 0b00000000 chars
	char oneChar = (char)0x80;
	char zeroChar = (char)0x0;

	//add bits: 1  and 7 zeros
	message += oneChar;

	//add k-7 zeros and additional 64 bits of zeros from length
	//len should be on 128 bits, no such datatype so we put 64 zeros
	k = (k - 7)/8 + 8;

	for(int i = 0; i < k; i++){
		message += zeroChar;
	}

	//64 bit result
	string result;

	//write len bitwise in result string
    for (int i = 0; i < 8; ++i)
    {
       	result += (unsigned char)(((messageLength) >> (56 - (8*i))) & 0xFFu);
    }
    //add 64 length bits
	message += result;

	//return preprocessed message
	return message;
}

/**
* Calculate hash of a preprocessed string
*/
string SHA512::digest(string preprocessedMessage){

	//number of blocks
	size_t n = preprocessedMessage.length()/128;

	//h array with initial values
	uint64_t h[8] = {};
	memcpy(h, hStart, 8*sizeof(uint64_t));

	//for each block
	for(int i = 0; i < n; i++){

		//get new block
		string part = preprocessedMessage.substr(i*128, 128);

		uint64_t w[80];

		//divide part to 16 64-bits pieces
		for(int j = 0; j < 16; j++){
			string myuint = part.substr(j*8, 8);
			unsigned long long a = 	((uint64_t)(myuint[0]) << 56 |
            						((uint64_t)(myuint[1]) << 48)&0x00ff000000000000ULL|
            						((uint64_t)(myuint[2]) << 40)&0x0000ff0000000000ULL|
            						((uint64_t)(myuint[3]) << 32)&0x000000ff00000000ULL|
            						((uint64_t)(myuint[4]) << 24)&0x00000000ff000000ULL|
            						((uint64_t)(myuint[5]) << 16)&0x0000000000ff0000ULL|
            						((uint64_t)(myuint[6]) << 8 )&0x000000000000ff00ULL|
            						((uint64_t)(myuint[7])      )&0x00000000000000ffULL);
            myuint.clear();
            w[j] = a;
		}

		//Extend 16 words to 80 
		for(int b = 16; b < 80; b++){
			uint64_t sZero = s0(w[b-15]);
			uint64_t sOne = s1(w[b-2]);
			w[b] = w[b-16] + sZero + w[b-7] + sOne;
		}

		//a-H variables with initial values
		uint64_t a = h[0];
		uint64_t b = h[1];
		uint64_t c = h[2];
		uint64_t d = h[3];
		uint64_t e = h[4];
		uint64_t f = h[5];
		uint64_t g = h[6];
		uint64_t H = h[7];

		for(int m = 0; m < 80; m++){
			uint64_t t1 = H + S1(e) + Ch(e,f,g) +  k[m] + w[m];
			uint64_t t2 = S0(a) + Maj(a,b,c);

			H = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}
		//Add new values
		h[0] = h[0] + a;
		h[1] = h[1] + b;
		h[2] = h[2] + c;
		h[3] = h[3] + d;
		h[4] = h[4] + e;
		h[5] = h[5] + f;
		h[6] = h[6] + g;
		h[7] = h[7] + H;
	}

	//Add missing 0s at the beginnings of each h value
	string result;
	for(int i = 0; i < 8; i++){
		stringstream hStream;
		hStream << hex << h[i];
		string hString(hStream.str());

		int zeros = 16-hString.length();
		for(int z = 0; z < zeros; z++){
			result+='0';
		}
		result+=hString;
	}

	return result;
}
