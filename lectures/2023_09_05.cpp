//Linked List

#include <iostream>  //cout cin

using namespace std;

class ThreeD1 {
public:
	int ht;
	int wid;
	int dep;
	int vol() { return ht * wid * dep; }
};


class ThreeD {
public:
	int ht;
	int wid;
	int dep;

	//constructor
	ThreeD(int i, int j, int k) : ht(2 * i), wid(2 * j), dep(2 * k) {}
	/*
	Alternatively,
	ThreeD(int i, int j, int k){ht = 2*i; wid = 2*j; dep = 2*k};
	*/

	ThreeD() {}//default constructor
	
	
	int vol() { return ht * wid * dep; }
};

class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }//construct
	node() { next = nullptr; }//default constructor

};

class LinkedList {
public:
	node* head;
	LinkedList(int n, int m);//Constructor for an n-node linked list
	//with values randomly in 0 ... m-1


	LinkedList() { head = nullptr; } //default constructor

	void PrintLL();

	void Reverse();//function prototype
	//void Sort();//sorting with selection sort
	//void RemoveOne(int k);//Delete the first occurrance of node with value k

};

//
//
//void LinkedList::RemoveOne(int k) {
//	if (!head) return;//empty linked list
//	if (head->value == k) { //if the first node carries value k
//		node* p{ head->next };
//		delete head;
//		head = p;
//		return;
//	}
//	node* p1{ head }, * p2{ head->next };//  *p2 {p1->next} is also OK
//	while (p2) {//while p2 is not nullptr
//		if (p2->value == k) {
//			p1->next = p2->next;
//			delete p2;
//			return;
//		}
//		p1 = p2;
//		p2 = p2->next;
//	}
//}
//
//
//
//void LinkedList::Sort() {
//	if (!head || !head->next) return;//0 or 1 node
//	node* p1{ head };
//	while (p1->next) {
//		node* p2 = p1->next;
//		node* pmin = p1;
//		int min{ p1->value };
//		while (p2) {//while p2 is not nullptr
//			if (p2->value < min) {
//				min = p2->value;
//				pmin = p2;
//			}
//			p2 = p2->next;
//		}
//		if (pmin != p1) {//swap pmin->value with p1->value
//			pmin->value = p1->value;
//			p1->value = min;
//		}
//		p1 = p1->next;
//	}
//}
//
void LinkedList::Reverse() {//Reverse is a member of class LinkedList (with the notation of LinkedList:: )
	if (!head || !head->next) return;//0 or 1 node   short-circuiting
	/*
	Same as  if (head == nullptr || head->next == nullptr) return;


	if (!head->next || !head) will cause run-time error if the linked list has 0 node.


	SHORT-CIRCUITING
	The sequence of !head and !head->next is important
	The policy of short-circuiting is adopted in C++ .
	For || , if already a value of true is obtained, it will ignore the rest of expression and return true.
	For && , if already a value of false is obtained, it will ignore the rest of expression and return false.

	*/

	node* p1{ head }, * p2{ head->next }, * p3;
	while (p2) {//while p2 != nullptr
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;

}

LinkedList::LinkedList(int n, int m) {//constructor of class LinkedList (with the notation of LinkedList:: )
	head = nullptr;
	for (int i = 0; i < n; ++i) {
		//node* p = new node{ rand() % m }; also OK
		node* p{ new node{ rand() % m } };//rand() % m will be a random value in 0 ... m-1
		//rand() returns an int out of all possible int value
		//% mod
		p->next = head;
		head = p;
	}
}

void LinkedList::PrintLL() {//PrintLL is a member of class LinkedList (with the notation of LinkedList:: )
	cout << endl;
	node* p{ head };
	while (p) {//the same as while (p != nullptr)
		cout << p->value << " ";
		p = p->next;
	}
}



int main() {



	//ThreeD1 t00;//default constructor

	//ThreeD t01;//default constructor



	//t00.ht = 25;
	//t00.wid = 14;
	//t00.dep = 4;



	//ThreeD1 t1{ 1,2,3 };//aggregate initializaiton ht=1, wid = 2, dep = 3


	//cout << t1.ht << " " << t1.wid << " " << t1.dep << endl;
	////1 2 3 



	//ThreeD t2{ 1,2,3 };
	//cout << t2.ht << " " << t2.wid << " " << t2.dep << endl;
	////2 4 6

	//ThreeD* p1 = new ThreeD{ 2,2,2 };//ht = 4; wid = 4; dep = 4;

	//(*p1).ht = 4;//  p1->ht = 4;// p1 select ht

	//cout << (*p1).vol() << endl;//64

	//cout << p1->vol() << " " << p1->ht << endl;
	////-> pronounced as select in this class.  Some people say it arrow.

	//ThreeD* p2{ &t2 };
	//cout << p2->ht << " " << p2->vol() << endl;
	//p2->wid = 21;

	//ThreeD1 t11; //members are not defined initially
	//ThreeD t12;

	LinkedList L1{ 20, 10 };

	L1.PrintLL();

	L1.Reverse();
	L1.PrintLL();
	//L1.RemoveOne(1);
	//L1.RemoveOne(6);
	//L1.RemoveOne(8);
	//L1.PrintLL();
	//L1.Sort();
	//L1.PrintLL();

	return 0;
}