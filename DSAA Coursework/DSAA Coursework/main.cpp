#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::ifstream;
using std::ofstream;

typedef std::chrono::steady_clock the_clock;


void menuChoice(int menu);
void radix();
void radixSize(int menu);
void populateArray(int *list, int size, string file);
void radixInit(int *list, int size, string file);

void print(int *input, int n);
void radixsort(int *input, int n);


//const int INPUT_SIZE = 10;

int main()
{


	//Menu variable
	int menu = 0;

	//Displaying the menu and inputting a menu choice
	while (menu != -1)
	{
		cout << "Declan Doyle Data Structures and Algorithms 1 Coursework Program" << endl;
		cout << "Enter -1 to exit any menu screen" << endl;
		cout << "Chose a sort:" << endl;
		cout << "1: Radix" << endl;
		cout << "2: PUT SORT NAME HERE" << endl;
		cin >> menu;
		menuChoice(menu);
	}

	cout << "Press any button to end" << endl;
	getchar();

	return 0;
}

void menuChoice(int menu)
{
	//Follow up on menu choice
	if (menu == 1)
	{
		radix();	//radix sort menu
	}
	else if (menu == 2)
	{
		//PUT NEW SORT HERE
	}
	else if (menu > 2)	//display error if invalid choice
	{
		cout << "Invalid Choice" << endl;
	}

}

void radix()
{
	//Menu variable
	int menu = 0;

	//Displaying the menu and inputting a menu choice
	while (menu != -1)
	{
		cout << "Radix Sort" << endl;
		cout << "Chose the list size:" << endl;
		cout << "1: 10" << endl;
		cout << "2: 100" << endl;
		cout << "3: 1000" << endl;
		cout << "4: 10,000" << endl;
		cin >> menu;
		radixSize(menu);
	}

}

void radixSize(int menu)
{
	//Follow up on menu choice
	if (menu == 1)
	{
		const int ten = 10;
		int list[ten];
		string array = "ten.txt";
		populateArray(list, ten, array);
		string file = "Radix10.csv";
		radixInit(list, ten, file);
	}
	else if (menu == 2)
	{
		const int oneHundred = 100;
		int list[oneHundred];
		string array = "oneHundred.txt";
		populateArray(list, oneHundred, array);
		string file = "Radix100.csv";
		radixInit(list, oneHundred, file);
	}
	else if (menu == 3)
	{
		const int oneThousand= 1000;
		int list[oneThousand];
		string array = "oneThousand.txt";
		populateArray(list, oneThousand, array);
		string file = "Radix1000.csv";
		radixInit(list, oneThousand, file);
	}
	else if (menu == 4)
	{
		const int oneHundredThousand = 10000;
		int list[oneHundredThousand];
		string array = "oneHundredThousand.txt";
		populateArray(list, oneHundredThousand, array);
		string file = "Radix10000.csv";
		radixInit(list, oneHundredThousand, file);
	}
	else if (menu > 4)
	{
		cout << "Invalid Choice" << endl;
	}
}

void populateArray(int *list, int size, string file)
{
	ifstream textFile(file);

	for (int i = 0; i < size + 1; ++i)
	{
		textFile >> list[i];
	}
}

void radixInit(int *list, int size, string file)
{
	cout << "List size " << size << " selected" << endl;
	cout << "Press any key to begin benchmark" << endl;
	getchar();

	ofstream my_file(file);

	for (int i = 1; i < 1001; i++)
	{
		the_clock::time_point start = the_clock::now();
		radixsort(list, size);
		the_clock::time_point end = the_clock::now();
		auto time_taken = duration_cast<milliseconds>(end - start).count();
		my_file << time_taken << ", " << i << endl;
	}

	cout << "Sorts completed. Data saved to a file called " << file << endl;

	//cout << "Sort took " << time_taken << " ms. " << endl;

}

void print(int *input, int n)
{
	for (int i = 0; i < n; i++)
		cout << input[i] << "\t";
}

void radixsort(int *input, int n)
{
	int i;

	// find the max number in the given list.
	// to be used in loop termination part.
	int maxNumber = input[0];
	for (i = 1; i < n; i++)
	{
		if (input[i] > maxNumber)
			maxNumber = input[i];
	}

	// run the loop for each of the decimal places
	int exp = 1;
	int *tmpBuffer = new int[n];
	while (maxNumber / exp > 0)
	{
		int decimalBucket[10] = { 0 };
		// count the occurences in this decimal digit.
		for (i = 0; i < n; i++)
			decimalBucket[input[i] / exp % 10]++;

		// Prepare the position counters to be used for re-ordering the numbers
		// for this decimal place.
		for (i = 1; i < 10; i++)
			decimalBucket[i] += decimalBucket[i - 1];

		// Re order the numbers in the tmpbuffer and later copy back to original buffer.
		for (i = n - 1; i >= 0; i--)
			tmpBuffer[--decimalBucket[input[i] / exp % 10]] = input[i];
		for (i = 0; i < n; i++)
			input[i] = tmpBuffer[i];

		// Move to next decimal place.
		exp *= 10;

		cout << endl << "PASS   : ";
		print(input, n);
	}
}