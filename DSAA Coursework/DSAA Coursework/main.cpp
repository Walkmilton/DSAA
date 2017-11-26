#include <iostream>
#include <chrono>
#include <fstream>

using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::ofstream;

typedef std::chrono::steady_clock the_clock;


void print(int *input, int n);
void radixsort(int *input, int n);


const int INPUT_SIZE = 10;

int main()
{

	ofstream my_file("Radix.csv");

	for (int i = 0; i < 1000; i++)
	{
		//Start
		the_clock::time_point start = the_clock::now();

		int input[INPUT_SIZE] = { 143, 123, 222, 186, 235, 9, 905, 428, 543, 373 };
		cout << "Input: ";
		print(input, INPUT_SIZE);
		radixsort(input, INPUT_SIZE);
		cout << endl << "Output: ";
		print(input, INPUT_SIZE);
		cout << endl;

		//Stop
		the_clock::time_point end = the_clock::now();

		auto time_taken = duration_cast<milliseconds>(end - start).count();
		cout << "It took " << time_taken << " ms." << endl;

		my_file << time_taken << ", ";
		my_file << i << endl;
	}

	getchar();

	return 0;
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