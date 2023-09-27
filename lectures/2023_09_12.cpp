

//STL (Standard Template Library)
//STL has many containers, such as vector, list, map, stack, queue, set,
//multi_set, multi_map, unordered_map, unordered_set, etc.
//Iterator: next class

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>

#include <string>

using namespace std;

int main() {
	//reference
	int w1{ 25 };
	const int& r1{ w1 };
	w1 = 100;
	//r1 = 200;

	//vector
	vector<int> V1(5); //vector of size 5; all values are 0; {0,0,0,0,0}
	//all STL containers come with default element values
	vector<int*> V101(10);//size 10; all with nullptr
	vector<int> V2(5, 3); //{3,3,3,3,3}
	vector<int> V3{ 1,2,3,4,5 };//size 5 
	cout << V3.front() << " " << V3.back() << " " << V3.size() << endl;//first last and size
	for (size_t i = 0; i < V3.size(); ++i) {//size_t non-negative int

		cout << V3[i] << " ";//vector allow array like substript or index
	}

	cout << endl;

	//range based for loop

	for (int i : V3) { cout << i << " "; ++i; }//for each element of V3
	cout << endl;//1 2 3 4 5

	for (auto i : V3) { cout << i << " "; }//call by value
	cout << endl;//1 2 3 4 5

	for (auto& i : V3) { cout << i << " "; ++i; }//for each element of V3
	cout << endl;//1 2 3 4 5

	for (const auto& i : V3) { cout << i << " "; } //call by reference
	cout << endl;//2 3 4 5 6  const makes int read only



	auto i1{ 20 };//int


	V3.push_back(8);//Add 8 to the last  2 3 4 5 6 8
	V3.push_back(4);// 2 3 4 5 6 8 4
	V3.pop_back();//Delete the last      2 3 4 5 6 8
	//cout << V3[2] << " " << V3[10] << endl;//run time error: V3[10] is out of bound
	//STL containers will check for out of bound error

	int A[5]{ 2,3,4,5,6 };
	cout << A[3] << " " << A[10] << endl;//NO error

	cout << sizeof(A) << endl;//20  A is not &A[0]   an exception
	cout << sizeof(&A[0]) << endl;//8

	//A is &A[0]; 
	//array will not check out of bound errors.
	//vector will check out of bound errors.
	V1.clear();//set the size to 0
	cout << V3.front() << " " << V3.back() << " " << V3.size() << endl;

	//list : doubly linked list
	list<int> L1(3); //0 0 0
	list<int> L2(5, 3); //3 3 3 3 3
	list<int> L3{ 1, 2,3,4,5 }; //1 2 3 4 5
	L3.push_back(34);
	L3.pop_back();
	L3.pop_front();//Remove the first 
	L3.push_front(22);//Add to the front


	//L3 has the same front, back, size, clear, push_back, pop_back functions.

	//map  key-mapped value pair
	cout << "**************" << endl;
	map<int, string> M1{ {25, "Apple"}, {11, "Banana"}, {5, "Grape"}, {11, "Cherry"}, {17, "Apple"} };
	// duplicate keys will be ignored  {11, "Cherry"} will be removed
	for (const auto& i : M1) { cout << i.first << " " << i.second << "   "; }
	cout << endl;
	M1[100] = "Pineapple";//adding {100, "Pineapple"} to M1.
	M1[5] = "Cherry";//update  {5, "Grape"} will be replaced by {5, "Cherry"} .

	M1.insert({ 25, "Blue Berry" });
	M1.insert({ 25, "Strawberry" });//will be ignored
	//{25, "Apple"}   25: key   "Apple" : mapped value
	// Each map element is a pair
	//map will automatically sort elements based on keys
	cout << endl;
	pair<int, string> p{ 1025, "Bob" };
	cout << p.first << "  " << p.second << endl;
	//1025 Bob

	map<string, int> M150{ {"John",21}, {"Dave", 23} };


	cout << endl;

	//set

	set<int> Set1{ 7, 3, 2, 5, 11, 5, 2, 3 };
	for (auto& i : Set1) cout << i << " ";//2 3 5 7 11
	//set will also sort elements and allows no duplicates
	cout << endl;
	Set1.insert(4);
	Set1.insert(7); //no operation


	//stack
	stack<int> S;//{1,2,3,4}  error.   Queue and stack does not allow initialization.
	S.push(1);
	S.push(2);
	for (auto& i : { 3,4,5,6,7,8 }) { S.push(i); }//initializer_list
	while (!S.empty()) {//empty() works for stack, queue, list, vector, map
		cout << S.top() << " ";
		S.pop();
	}//8 7 6 5 4 3 2 1
	//Only vector support array like subscript
	//Deque is another container that supports subscript
	cout << endl;


	//queue
	queue<int> Q;//{1,2,3} Error!
	Q.push(5);
	Q.push(4);
	for (int i : {7, 8, 9, 10}) Q.push(i);
	while (!Q.empty()) {
		cout << Q.front() << " ";
		Q.pop();
	}




	vector<int*> V11{ new int{8}, new int {14}, new int {3} };
	V11.push_back(new int{ 22 });
	for (auto& i : V11) cout << *i << " ";
	cout << endl << endl;//8 14 3 22


	cout << "&&&&&&" << endl;
	vector<set<int>> V12{ {3,1, 4, 5}, {5,7,2,8}, {4,4,4,4} };
	for (auto& i : V12) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << endl;
	}

	vector<int*>* pV;
	pV = new vector<int*>;// vector of address of int objects

	//(*pV).push_back( new int {9});
	pV->push_back(new int{ 9 });
	pV->push_back(new int{ 4 });
	for (auto& i : { 4,5,1,23 }) pV->push_back(new int{ i });
	for (auto i : *pV) cout << *i << " ";
	cout << endl << endl;//9 4 4 5 1 23

	vector<list<int*>*> V22;
	for (auto& i : { new list<int*>{}, new list<int*>{},new list<int*> }) {
		V22.push_back(i);
		for (auto j : { rand() % 10, rand() % 10, rand() % 10 }) i->push_back(new int(j));

	}

	cout << endl << endl;

	for (auto& i : V22) {
		for (auto& j : *i) {
			cout << *j << " ";
		}
		cout << endl;
	}

	return 0;
}