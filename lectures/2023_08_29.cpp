/**
 * Syracuse University CIS 554
 * date: 2023-08-29
 *  
 * Pointer, dyanmica memory allocation (new, delete), 2D array structures
 * call (pass) by value, call (pass) by reference
*/

#include <iostream> //cin cout

using namespace std;

  			
int main() {
	int j{ 10 }; //most up-to-date.  j is a static object stored in stack
	int j1 = 10;
	int j2(10);
	int j3 = { 10 };
	int j4 = (10);

	int k;
	//cout << k << endl; Error,   object does not have default value.

	//pointer

	int* p1 { &j };
	/*
	p1 points to j.
	p1 is of type int *
	p1 carries the memory address of j (i.e., &j)
	*/

	cout << p1 << " " << *p1 << endl;
	/*
	*p1 will return the value stored at the memory position whose address is carried by p1.
	*p1 is the same as j
	*/

	*p1 = 1000; //j is 1000

	int i1, * p2, i2, * p3;// i1, i2 of type int, p2 , p3 of type int *

	int A[5]{ 1,2,3,4,5 };

	cout << A[0] << " " << A[1] << " " << A[2] << " " << A[3] << " " << A[4] << "\n";
	cout << A << " " << A + 1 << " " << A + 2 << " " << A + 3 << " " << A + 4 << endl;
	//Pointer arithmetics are logical.
	cout << *A << " " << *(A + 1) << " " << *(A + 2) << " " << *(A + 3) << " " << *(A + 4) << "\n";
	/*
	For 1D array, array name (without index or subsricpt) is the same as the address of the first element.
	*/

	//dynamic object  : in heap

	int* p4 = new int{ 5 };
	/*
	The operator new requests a memory space from system for an int object (initialized to 5), and returns
	the address of the storage space.
	p4 points to the new int object.
	*/

	return 0;//indicates a successful execution.
}



