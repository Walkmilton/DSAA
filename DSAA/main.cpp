#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::ifstream;
using std::ofstream;
using std::to_string;

typedef std::chrono::steady_clock the_clock;


void menuChoice(int menu);

void radix();
void radixSize(int menu);
void radixRange(int *list, int size);
void radixInit(int menu, int *list, int size);
void radixExecute(int *list, int size, int range, string file);
void radixSort(int *input, int n);


void merge();
void mergeSize(int menu);
void mergeRange(int *list, int size);
void mergeInit(int menu, int *list, int size);
void mergeExecute(int *list, int size, int range, string file);
void mergeSort(int* input, int p, int r);
void merge(int* input, int p, int r);

void populateList(int *list, int size, int range);
void print(int *input, int n);


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
		cout << "Choose a sort:" << endl;
		cout << "1: Radix" << endl;
		cout << "2: Merge" << endl;
		cin >> menu;
		cout << endl << endl;
		menuChoice(menu);
	}

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
		merge();	//merge sort menu
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
		cout << "Choose the list size:" << endl;
		cout << "1: 10" << endl;
		cout << "2: 100" << endl;
		cout << "3: 1000" << endl;
		cout << "4: 10,000" << endl;
		cout << "5: 100,000" << endl;
		cin >> menu;
		cout << endl << endl;
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
		radixRange(list, ten);
	}
	else if (menu == 2)
	{
		const int oneHundred = 100;
		int list[oneHundred];
		radixRange(list, oneHundred);
	}
	else if (menu == 3)
	{
		const int oneThousand = 1000;
		int list[oneThousand];
		radixRange(list, oneThousand);
	}
	else if (menu == 4)
	{
		const int tenThousand = 10000;
		int list[tenThousand];
		radixRange(list, tenThousand);
	}
	else if (menu == 5)
	{
		const int oneHundredThousand = 100000;
		int list[oneHundredThousand];
		radixRange(list, oneHundredThousand);
	}
	else if (menu > 5)
	{
		cout << "Invalid Choice" << endl;
	}
}

void radixRange(int *list, int size)
{
	int menu = 0;

	cout << "Radix Sort" << endl;
	cout << "Choose the list range:" << endl;
	cout << "1: 0-10" << endl;
	cout << "2: 0-100" << endl;
	cout << "3: 0-1000" << endl;
	cout << "4: 0-10,000" << endl;
	cout << "5: 0-100,000" << endl;
	cin >> menu;
	cout << endl << endl;
	radixInit(menu, list, size);

}


void radixInit(int menu, int *list, int size)
{
	if (menu == 1)
	{
		const int range = 10;
		populateList(list, size, range);
		string file = to_string(size) + "Radix" + to_string(range) + ".csv";
		radixExecute(list, size, range, file);

	}
	else if (menu == 2)
	{
		const int range = 100;
		populateList(list, size, range);
		string file = to_string(size) + "Radix" + to_string(range) + ".csv";
		radixExecute(list, size, range, file);

	}
	else if (menu == 3)
	{
		const int range = 1000;
		populateList(list, size, range);
		string file = to_string(size) + "Radix" + to_string(range) + ".csv";
		radixExecute(list, size, range, file);

	}
	if (menu == 4)
	{
		const int range = 10000;
		populateList(list, size, range);
		string file = to_string(size) + "Radix" + to_string(range) + ".csv";
		radixExecute(list, size, range, file);

	}
	if (menu == 5)
	{
		const int range = 100000;
		populateList(list, size, range);
		string file = to_string(size) + "Radix" + to_string(range) + ".csv";
		radixExecute(list, size, range, file);

	}
	if (menu > 5)
	{
		cout << "Invalid Choice" << endl;
	}
}

void radixExecute(int *list, int size, int range, string file)
{

	char temp;
	cout << "List size " << size << " selected" << endl;
	cout << "List range " << range << " selected" << endl;
	cout << "Enter 'g' to begin benchmark" << endl;
	cin >> temp;
	

	ofstream my_file(file);

	for (int i = 0; i < 1000; i++)
	{
		the_clock::time_point start = the_clock::now();
		radixSort(list, size);
		the_clock::time_point end = the_clock::now();
		auto time_taken = duration_cast<nanoseconds>(end - start).count();
		my_file << time_taken << ", " << i << endl;
	}

	cout << endl << endl << endl;
	cout << "Sorts completed. Data saved to a file called " << file << endl;
	cout << "File name is as follows: [List Size][Sort Type][List Range].csv" << endl << endl;
	cout << "Enter 'g' to go to previous menu" << endl;
	cin >> temp;
	cout << endl << endl;

	//cout << "Sort took " << time_taken << " ms. " << endl;
}

void radixSort(int *input, int n)
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


	}
}

void merge()
{
	//Menu variable
	int menu = 0;

	//Displaying the menu and inputting a menu choice
	while (menu != -1)
	{
		cout << "Merge Sort" << endl;
		cout << "Choose the list size:" << endl;
		cout << "1: 10" << endl;
		cout << "2: 100" << endl;
		cout << "3: 1000" << endl;
		cout << "4: 10,000" << endl;
		cout << "5: 100,000" << endl;
		cin >> menu;
		cout << endl << endl;
		mergeSize(menu);
	}

}

void mergeSize(int menu) 
{
	//Follow up on menu choice
	if (menu == 1)
	{
		const int ten = 10;
		int list[ten];
		mergeRange(list, ten);
	}
	else if (menu == 2)
	{
		const int oneHundred = 100;
		int list[oneHundred];
		mergeRange(list, oneHundred);
	}
	else if (menu == 3)
	{
		const int oneThousand = 1000;
		int list[oneThousand];
		mergeRange(list, oneThousand);
	}
	else if (menu == 4)
	{
		const int tenThousand = 10000;
		int list[tenThousand];
		mergeRange(list, tenThousand);
	}
	else if (menu == 5)
	{
		const int oneHundredThousand = 100000;
		int list[oneHundredThousand];
		mergeRange(list, oneHundredThousand);
	}
	else if (menu > 5)
	{
		cout << "Invalid Choice" << endl;
	}
}

void mergeRange(int *list, int size)
{
	int menu = 0;

	cout << "Merge Sort" << endl;
	cout << "Choose the list range:" << endl;
	cout << "1: 0-10" << endl;
	cout << "2: 0-100" << endl;
	cout << "3: 0-1000" << endl;
	cout << "4: 0-10,000" << endl;
	cout << "5: 0-100,000" << endl;
	cin >> menu;
	cout << endl << endl;
	mergeInit(menu, list, size);

}

void mergeInit(int menu, int *list, int size)
{
	if (menu == 1)
	{
		const int range = 10;
		populateList(list, size, range);
		string file = to_string(size) + "Merge" + to_string(range) + ".csv";
		mergeExecute(list, size, range, file);

	}
	else if (menu == 2)
	{
		const int range = 100;
		populateList(list, size, range);
		string file = to_string(size) + "Merge" + to_string(range) + ".csv";
		mergeExecute(list, size, range, file);

	}
	else if (menu == 3)
	{
		const int range = 1000;
		populateList(list, size, range);
		string file = to_string(size) + "Merge" + to_string(range) + ".csv";
		mergeExecute(list, size, range, file);

	}
	if (menu == 4)
	{
		const int range = 10000;
		populateList(list, size, range);
		string file = to_string(size) + "Merge" + to_string(range) + ".csv";
		mergeExecute(list, size, range, file);

	}
	if (menu == 5)
	{
		const int range = 100000;
		populateList(list, size, range);
		string file = to_string(size) + "Merge" + to_string(range) + ".csv";
		mergeExecute(list, size, range, file);

	}
	if (menu > 5)
	{
		cout << "Invalid Choice" << endl;
	}
}

void mergeExecute(int *list, int size, int range, string file)
{
	const int zero = 0;
	char temp;
	cout << "List size " << size << " selected" << endl;
	cout << "List range " << range << " selected" << endl;
	cout << "Enter 'g' to begin benchmark" << endl;
	cin >> temp;

	ofstream my_file(file);

	for (int i = 0; i < 1000; i++)
	{
		the_clock::time_point start = the_clock::now();
		mergeSort(list, zero, size - 1);
		the_clock::time_point end = the_clock::now();
		auto time_taken = duration_cast<nanoseconds>(end - start).count();
		my_file << time_taken << ", " << i << endl;
	}

	cout << endl << endl << endl;
	cout << "Sorts completed. Data saved to a file called " << file << endl;
	cout << "File name is as follows: [List Size][Sort Type][List Range].csv" << endl << endl;
	cout << "Enter 'g' to go to previous menu" << endl;
	cin >> temp;
	cout << endl << endl;

	//cout << "Sort took " << time_taken << " ms. " << endl;

}
	
void mergeSort(int* input, int p, int r)
{
	if (p < r)
	{
		int mid = floor((p + r) / 2);
		mergeSort(input, p, mid);
		mergeSort(input, mid + 1, r);
		merge(input, p, r);
	}
}

void merge(int* input, int p, int r)
{
	int a = r - p + 1;
	int mid = floor((p + r) / 2);
	int i1 = 0;
	int i2 = p;
	int i3 = mid + 1;

	// Temp array
	int *temp = new int[a];

	// Merge in sorted form the 2 arrays
	while (i2 <= mid && i3 <= r)
	{
		if (input[i2] < input[i3])
		{
			temp[i1++] = input[i2++];
		}
		else
		{
			temp[i1++] = input[i3++];
		}
	}
	
	// Merge the remaining elements in left array
	while (i2 <= mid)
	{
		temp[i1++] = input[i2++];
	}

	// Merge the remaining elements in right array
	while (i3 <= r)
	{
		temp[i1++] = input[i3++];
	}

	// Move from temp array to master array
	for (int x = p; x <= r; x++)
	{
		input[x] = temp[x - p];
	}

	delete[] temp;
}


void populateList(int *list, int size, int range)
{
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		list[i] = rand() % range + 1;
	}
}

void print(int *input, int n)
{
	for (int i = 0; i < n; i++)
		cout << input[i] << "\t";
}