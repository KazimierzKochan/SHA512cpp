/***************************************************************************************
*    Title: SHA512 demo program
*    Author: Kazimierz Kochan
*    Date: April 2022
*    Code version: 1.0
*    Availability: https://github.com/KazimierzKochan/SHA512cpp
*
***************************************************************************************/
#include "SHA512.h"
#include <iostream>

int main(int argc, char** argv){
	SHA512 sha512;
	cout << "SHA512(\"The quick brown fox jumps over the lazy dog\")\n" << sha512.hashString("The quick brown fox jumps over the lazy dog") << "\n\n";
	cout << "SHA512(\"The quick brown fox jumps over the lazy dog.\")\n" << sha512.hashString("The quick brown fox jumps over the lazy dog.") << "\n\n";
	cout << "SHA512(file.txt)\n" << sha512.hashFile("file.txt") << endl;
	return 0;
}