


//template


#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <string>

using namespace std;

void DB1toDB2(const vector<vector<int>>& DB1, list<vector<int>>& DB2);//prototype
void DB1toDB3(const vector<vector<int>>& DB1, vector<list<int>*>& DB3);
void DB3toDB4(const vector<list<int>*>& DB3, list<list<int*>*>& DB4);


template <typename T> ostream& operator<<(ostream& str, const vector<T>& V);
template <typename T> ostream& operator<<(ostream& str, const list<T>& L);

template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V);
template <typename T> ostream& operator<<(ostream& str, const list<T*>& L);

int main() {

	//NULL is  nullptr or 0

	vector<vector<int>> DB1{ {1,2,3}, {4,5}, {6,7,8} };
	for (const auto& i : DB1) {
		for (const auto& j : i) cout << j << " ";
		cout << " ";
	}
	cout << endl;


	list<vector<int>> DB2;
	DB1toDB2(DB1, DB2);
	for (const auto& i : DB2) {
		for (const auto& j : i) cout << j << " ";
		cout << " ";
	}

	cout << endl;

	vector<list<int>*> DB3;
	DB1toDB3(DB1, DB3);
	for (auto& i : DB3) {
		for (auto& j : *i) {
			cout << j << " ";
		}
		cout << " ";
	}


	list<list<int*>*> DB4;

	/*

	....
	*/

	DB3toDB4(DB3, DB4);
	cout << endl;
	for (auto& i : DB4) {
		for (auto& j : *i) {
			cout << *j << " ";
		}
		cout << " ";
	}
	cout << endl;
	cout << " *************************" << endl;
	cout << DB1 << endl << endl;
	cout << DB2 << endl << endl;
	cout << DB3 << endl << endl;
	cout << DB4 << endl << endl;

}

void DB3toDB4(const vector<list<int>*>& DB3, list<list<int*>*>& DB4) {
	for (auto& i : DB4) {
		for (auto& j : *i) {
			delete j;
		}
		delete i;
	}
	DB4.clear();

	for (auto& i : DB3) {
		list<int*>* p{ new list<int*> {} };
		for (auto& j : *i) {
			p->push_back(new int{ j });
		}
		DB4.push_back(p);
	}

}

void DB1toDB3(const vector<vector<int>>& DB1, vector<list<int>*>& DB3) {

	for (auto& i : DB3) {
		delete i;//fair to do this lead to memory leak
	}
	DB3.clear();

	for (const auto& i : DB1) {//i is of type vector<int>
		list<int>* p { new list<int>{} };
		for (const auto& j : i) {//j is of type int
			p->push_back(j);
		}
		DB3.push_back(p);
	}
	/*  The following is incorrect
	for (auto& i : V) {
		list<int> p;
		for (auto& j : i) {
			p.push_back(j);
		}
		DB3.push_back(&p);
		//p is a local variable. Upon exiting the scope, p will be removed,
		//and thus its address is meaningless.
	}
	*/

}

void DB1toDB2(const vector<vector<int>>& DB1, list<vector<int>>& DB2) {
	DB2.clear();
	for (auto& i : DB1) {// i is vector<int>
		vector<int> V1;
		for (auto& j : i) {
			V1.push_back(j);
		}
		DB2.push_back(V1);
	}
}

template <typename T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "< ";
	for (auto& i : L) str << *i << " ";
	str << ">";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (auto& i : V) str << *i << " ";
	str << "]";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto& i : L) str << i << " ";
	str << ">";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
	str << "]";
	return str;
}