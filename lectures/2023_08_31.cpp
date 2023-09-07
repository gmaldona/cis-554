//Topics to cover:
//Dynamic memory management: New, delete, 
//Call by value,  by reference
//structures of multi-dimentional arrays
//Passing array to function


//What applications will use C++?
//system level codes, large scale system,
// Performance sensitive applications,
// applications that needs interaction with external devices
// 

// visual studio community edition 2022 .  Free download
#include <iostream> //for cin and cout : input from console and output to console

using namespace std;

void  f0();

void f1(int i);


void f2(int& i);

void f22(const int& i);

/*

Call by reference skip the step of copying an object, and will be faster, especially true for complicated objects.

*/

void f3(const int& i) {

	cout << "const  call by value" << endl;
	//++i;  error !  i is read only.
}

int main() {//Program execution starts at a function called main;



	//data type:  int, char, float, double, long, short, bool, string, int *, double *, ...
		/*
		Data Types:
	Primitive Built-in types:  bool, char, int, float, double, void, wchar_t, size_t
	Modifier: singed, unsigned, long, short


	Type				Typical Bit Width	Typical Range
	char				1byte				-127 to 127 or 0 to 255
	unsigned char		1byte				0 to 255
	signed char			1byte				-127 to 127
	int					4bytes				-2147483648 to 2147483647
	unsigned int		4bytes				0 to 4294967295
	signed int			4bytes				-2147483648 to 2147483647
	short int			2bytes				-32768 to 32767
	unsigned short int	2bytes				0 to 65,535
	signed short int	2bytes				-32768 to 32767
	long int			8bytes				-2,147,483,648 to 2,147,483,647
	signed long int		8bytes				same as long int
	unsigned long int	8bytes				0 to 4,294,967,295
	long long int		8bytes				-(2^63) to (2^63)-1
	unsigned long long int	8bytes			0 to 18,446,744,073,709,551,615
	float				4bytes
	double				8bytes
	long double			12bytes
	wchar_t				2 or 4 bytes	1 wide character
	32-bit windows	    4 bytes address
	64-bit windows		8 bytes address
	Derived type: function, array, pointer, reference

	User-defined type: class, struct, enum, union, typedef

		*/

	int i1000;
	//cout << i1000 << endl;  error. i1000 undefined

	int i300;//in stack
	double d300;
	char c300;
	//cin >> i300 >> d300 >> c300; //>> extract operator
	//cout << i300 << "    " << d300 << " "<< c300 << endl; //<< insert operator

	//cout << "************" << endl;

	cout << sizeof(int) << " " << sizeof(bool) << " " << sizeof(double) << " " << sizeof(float) << '\n'; //4 1 8 4
	cout << sizeof(i300) << endl;//4




	int i0{ 10 };  //variable i (a static object) has type int and is initialized to value 10. This is the newest style, and I will use it most of the time.
	int i1 = 10;
	int i2(10);
	int i3 = { 10 };
	int i4 = (10);
	cout << i0 << " " << i1 << " " << i2 << " " << i3 << " " << i4 << "  \n" << '\n' << endl;//10 10 10 10 10
	//All the above 5 works; we will use the first one most of the time in class.



	int j1;
	//cout << j1 << endl;  Error!  j's value is undefined.  Variables will not have default values.
	j1 = 25;

	int j{ 20 };




	//Pointers
	int* p1{ &j };//p1 is variable of type int * and has address as value.  (a pointer to int object)
	//p1's value is the address of variable j in the memory or p1 carries the address of j;


	cout << j << " " << *(&j) << " " << *p1 << endl;// 20. *(address) will return the value at the memory address.
	//20 20 20


	//cout << "**********" << endl;
	*p1 = 25; //j becomes 25.  j = 25;
	cout << p1 << " " << *p1 << endl;
	//64-bit memory address  25

	cout << "***********" << endl;
	int A[5]{ 11,12,13, 14,15 }; //array of 5 int with initial values.
	cout << A << " " << *A << "\n";//*A is the same as A[0]   *x   x is either address or pointer carrying address
	//64-bit address of A[0] and 11

	//For 1-D array, array name without subscript (or index)
	//is the address of first element of the array, i.e., &A[0]

	//A is the same as &A[0]   *A is the same as A[0]

	cout << A[3] << " " << 3[A] << endl;//14 14   will converted into *(A+3) or  *(3+A)
	//both will be converted to *(A+3) or *(3+A)

	cout << "&&&&&&&&&&&&&&&" << endl;
	cout << "Number of bytes for memory address is " << sizeof(&j) << endl;//64-bit address
	cout << "Number of bytes for A is " << sizeof(A) << " " << sizeof(&A[0]) << endl;
	//20  64-bit address

	//Note that in the above statement, A by itself is not interpreted as &A[0].
	//cout << "*********" << endl;
	cout << A << " " << A + 1 << " " << A + 2 << " " << A + 3 << " " << A + 4 << endl;//each int is 4 bytes

	//Address arithmetic is "Logical".


	cout << *A << " " << *(A + 1) << " " << *(A + 2) << " " << *(A + 3) << " " << *(A + 4) << endl;
	cout << A[0] << " " << A[1] << " " << A[2] << " " << A[3] << " " << A[4] << endl;
	//the above two statements print the same


	cout << *(A + 7) << " " << A[30] << endl;//no error, but will print whatever in those memory locations
	//C++ does not check out of bound error for arrays

	int A1[]{ 3,4,5 };//A1 has size 3
	int A2[5]{ 2,1 }; //A1 has 5 elements: 2 1 0 0 0; remaining unspecified will be filled with 0
	int A3[5]; //A1's element values are not initialized.
	cout << endl;
	cout << A3[2] << endl;
	cout << "************************************************" << endl;
	int A4[5]{}; //{0,0,0,0,0}
	cout << sizeof(A) / sizeof(int) << endl;//20/4= 5 elements in the array

	//sizeof(A) will return 20
	//note that A here is not &A[0]


	p1 = nullptr; //p1 is now not pointing to any object.  This allows us to check if the pointer is not pointing to any object.
	//do not use p1 = NULL;

	if (p1 == nullptr) cout << "p1 is not pointing to any object" << endl;

	int w1{ NULL }; // w1 is initialized to 0; avoid using it though


	//in heap

	//Dynamic Memory management
	//int * p2 {new int{});
	//*p2 = 5;
	int* p2{ new int{ 5 } }; //Create a dynamic int object with value 5 whose address is assigned to p2. p2 carries the address of the new int object.
	//new is an operator which request the system to allocate a memory space for int object and initialize the object to the specified value, and return 
	//the address of the memory space.
	//p2 points to the new dynamic object.


	cout << *p2 << endl; //5
	*p2 = 15;//the dynamic object now contains value 15
	delete p2; //the dynamic object pointed by p2 is now deleted and memory space is returned to the system
	//p2 is not deleted; only the object pointed by p2 is now deleted.

	p2 = new int{ 100 }; //you can re-use p2;

	cout << p2[0] << endl;//the same as *(p2+0)
	//p2[0] is the same as *p2


	int* p10;//an array is created


	//cout << p2[10] << endl;


	delete p2;

	p2 = new int[5] { 23, 24, 25, 26, 27 };
	//cout << *p2 <<endl;  23

	cout << *p2 << " " << *(p2 + 1) << " " << *(p2 + 2) << " " << *(p2 + 3) << " " << *(p2 + 4) << endl;
	cout << p2[0] << " " << p2[1] << " " << p2[2] << " " << p2[3] << " " << p2[4] << endl;

	short int* p3;
	p3 = new short int[5] { 23, 24, 25, 26, 27 };
	cout << *p3 << " " << *(p3 + 1) << " " << *(p3 + 2) << " " << *(p3 + 3) << " " << *(p3 + 4) << endl;
	cout << p3[0] << " " << p3[1] << " " << p3[2] << " " << p3[3] << " " << p3[4] << endl;
	cout << p3 << " " << p3 + 1 << " " << p3 + 2 << " " << p3 + 3 << " " << p3 + 4 << '\n';


	delete[] p2;//delete the array pointed by p2.  You should avoid deleting partial array.
	//delete p2; BAD usage -- can lead to surprise!



	int B[4][3]{ {11,12, 13}, {14,15,16}, {17,18, 19}, {20, 21, 22} };


	cout << B[2][2] << " " << *(*(B + 2) + 2) << " " << *(B[2] + 2) << " " << *(&B[0][0] + 3 * 2 + 2) << endl;

	//19 19 19 19






	int c100{ 4 };
	//int AAA[c100]; //error

	int* p150;
	p150 = new int[c100] {5, 6, 7, 8};//OK




	int k{ 1 };
	f1(k);//call/pass by value
	cout << k << endl;//1
	f2(k);//call/pass by reference
	cout << k << endl;//2

	return 0;//When 0 is returned, it indicates a successful execution.
}

void  f0() {
	int* p3 = new int{ 250 };
	int j{ *p3 };//j = 250;
	delete p3;//delete the object pointed by p3
	//Fail to delete will lead to memory leak

	//cout << *p3 << endl;  *p3 will be undefined.

	
}


void f1(int i) {//void :  f1 does not return anything.
	//a new copy of the passed object is created and is called i inside the function.
	//Any modification of object i will not affect the original object outside the function.

	cout << " Call(pass) by value" << endl;
	++i;//increment before return
}
void f2(int& i) {
	//The same object outside the function is used directly inside the functin,
	//although can be used under different name inside the function.
	//Any modification on i, will at the same time modify the object outside the function.
	cout << " Call (pass) by reference" << endl;
	++i;
}

void f22(const int& i) {//still call by reference; make it read only to protect the object
	//The same object outside the function is used directly inside the functin,
	//although can be used under different name inside the function.
	//Any modification on i, will at the same time modify the object outside the function.
	cout << " Call (pass) by reference" << endl;
	//++i;  compile error.  i is read only.
}