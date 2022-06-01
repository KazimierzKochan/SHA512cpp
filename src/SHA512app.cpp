/***************************************************************************************
*    Title: SHA512 C++ app
*    Author: Kazimierz Kochan
*    Date: April 2022
*    Code version: 1.2
*    Availability: https://github.com/KazimierzKochan/SHA512cpp
*
***************************************************************************************/
#include "SHA512.h"

void printHelp(string argv0){
	cout << "Syntax: " << argv0<< " option input" << endl;
	cout << "options: " << endl;
	cout << "\t -f/-file fileName\t calculate hash value of a file" << endl;
	cout << "\t -s/-string string\t calculate hash value of a string" << endl; 
}

int main(int argc, char** argv){
	SHA512 sha512;

	//check option and input
	if(argc != 3){
		printHelp(argv[0]);
		exit(EXIT_FAILURE);
	}else{
		//file option
		if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "-file") == 0){
			cout << "SHA512 sum of file '" << argv[2] << "':\n" << sha512.hashFile(argv[2]) << endl;
		}
		//string option
		if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-string") == 0){
			printf("hehe");
			cout << "SHA512 sum of string '" << argv[2] << "':\n" << sha512.hashString(argv[2]) << endl;
		}
		//help
		if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0){
			printHelp(argv[0]);
		}

	}
	return 0;
}
