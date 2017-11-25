#include <iostream>
#include "md5wrapper.h"

int main()
{

	// This will allow us to access the md5wrapper class.
	md5wrapper md5;
	// This will store the md5 hash of a file called test.txt in a string hash1
	std::string hash1 = md5.getHashFromFile("test.txt");
	// This will store the md5 hash of some text into a string hash2
	std::string hash2 = md5.getHashFromString("Hello World");
	// This will print, the hash from the file and from the string
	std::cout << hash1 << std::endl << hash2 << std::endl;
	system("PAUSE"); // Remove if your using Linux.
	return 0;

}