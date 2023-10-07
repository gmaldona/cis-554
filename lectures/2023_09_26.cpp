//Copy, move, Lvalue, Rvalue, 
/*
Anything that can be placed on left side of an assignment statement is Lvalue; otherwise R value;

5 Rvalue
i Lvalue i = 21;
i+1 Rvalue
sqrt(4) Rvalue

++i is Lvalue;  //  ++i = 35;  OK  the same as i= 35;
i++ is Rvalue;// i++ = 35; error.

A[5] is Lvalue;// A[5] = 21;

5 = ....

j = i = 45;

cout << (i = 36) << endl;// 36


*/
/*
Shallow copying vs Deep copying

*/
/*
Copy constructor will be called in three situations:
1. When object is declared and initialized in the same statement.
2. call by value;
3. return by value//can be avoided with return value optimization (RVO) technique


Destructor will be called in two situations:
1. When an object is going out of scope.
2. When explicitly  called by delete .

*/

#include <iostream>
#include <tuple>
#include <vector>
#include <list>
using namespace std;


class myClass {
public:
	int* Pt;
	myClass(int k) { Pt = new int(k); }
	myClass() { Pt = nullptr; }
};

class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }
	node() { next = nullptr; }

};

class LinkedList {
public:
	node* head;
	LinkedList(int n, int m);//Constrctor for an n-node linked list
	//with values randomly in 0 ... m-1
	LinkedList() { head = nullptr; }
	LinkedList(const initializer_list<int>& I);//Initializer List
	LinkedList(const LinkedList& L);//Copy Constructor  L version copy constructor
	void operator=(const LinkedList& L);//copy assignment  L version
	~LinkedList();//Destructor
	LinkedList ThreeTimes();//Return a linked list whose node values are three time of *this.
	LinkedList(LinkedList&& L);//move constructor  -- R version  copy constructor
	void operator=(LinkedList&& L);//move assignment   R version copy assignment
};
LinkedList::LinkedList(LinkedList&& L) {//Move Constructor

	head = L.head;//L is temp   *this is "hidden copy"  for the return temp;
	L.head = nullptr;
	cout << "Move Constructor" << endl;

}
void LinkedList::operator=(LinkedList&& L) {
	while (head) {
		node* p{ head->next };
		delete head;
		head = p;
	}
	head = L.head;
	L.head = nullptr;
	cout << "Move Assignment" << endl;
}




LinkedList LinkedList::ThreeTimes() {
	LinkedList temp{ *this };//will call copy constructor  *this is L3
	node* p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}
	cout << "ThreeTimes" << endl;
	return temp;//compiler will change it to return move(temp) and call move constructor;
	//move() change an Lvalue to Rvalue
	// 
	//return *this; will instead call copy constructor
}

LinkedList::~LinkedList() {//Destructor
	while (head) {//while head is not equal to nullptr
		node* p1{ head->next };
		delete head;
		head = p1;
	}
	cout << "Destructor" << endl;
}

void LinkedList::operator=(const LinkedList& L) {//Copy Assignment
	while (head) {//delete all current nodes
		node* p1{ head->next };
		delete head;
		head = p1;
	}
	node* p1{ L.head };
	while (p1) {//Create a linked List with the same number of nodes as L
		node* p2{ new node {} };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node* p2{ head };
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Assignment" << endl;

}

LinkedList::LinkedList(const LinkedList& L) : LinkedList{} {//Copy Constructor
	//head = nullptr; 
	node* p1{ L.head };
	while (p1) {//Create a linked List with the same number of nodes as L
		node* p2{ new node {} };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node* p2{ head };
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Constructyor" << endl;
}


LinkedList::LinkedList(const initializer_list<int>& I): LinkedList() {//Initializer List
	//head = nullptr;
	auto p1{ I.end() - 1 };//type of p1 is     const int *  or int const *
	while (p1 != I.begin() - 1) {
		node* p2{ new node{*p1} };
		p2->next = head;
		head = p2;
		--p1;
	}
	cout << "Initializer List" << endl;
}


LinkedList::LinkedList(int n, int m) {
	head = nullptr;
	for (int i = 0; i < n; ++i) {
		node* p = new node(rand() % m);
		//rand() returns an int out of all possible int value
		//% mod
		p->next = head;
		head = p;
	}
	cout << "Constructor" << endl;
}






void f1(int& i) { cout << " Lvalue" << endl; }


void f1(int&& i) { cout << "Rvalue" << endl; }

ostream& operator<<(ostream& str, const LinkedList& L);

int main() {
	int ii;
	(ii = 5) = 21;//(ii=5) return by reference  Lvalue
	cout << ii << endl;

	int i{ 5 };
	f1(i);//i is Lvalue
	f1(move(i));//will call R value version        move() change i to R value
	f1(i + 1); //i+1 is Rvalue
	f1(10);//R valuie




	LinkedList L1( 20, 15 );//will call constructor even with initializer_list
	cout << L1 << endl;



	//tuple<int, int, int, int> T1{ 1,2,3,4 };
	LinkedList L2{ 1,2,3,4,5 };
	cout << L2 << endl;
	//initilaizer_list overrides constructor which overrides aggregate initialization

	LinkedList L3{ L2 };//copy constructor
	//LinkedList L3 = L2; also work  ; will call copy constructor

	//L2.head->value = 10;
	//cout << L3.head->value << endl;
	cout << L3 << endl;
	LinkedList L4(25, 50);
	L4 = L2;//assignment by default is shallow assignment
	//Compiler will change it to L4.operator=(L2);// L4 is *this

	cout << L4 << endl;

	cout << "*****************" << endl;
	L4 = L3.ThreeTimes();
	//Compiler will change it to L4.operator=(L3.ThreeTimes());//will call move assignment because
	//L3.ThreeTimes() is R value
	cout << L3 << endl;
	cout << L4 << endl;

	return 0;
}

ostream& operator<<(ostream& str, const LinkedList& L) {
	str << "{ ";
	node* p1{ L.head };
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << "}";
	return str;
}


