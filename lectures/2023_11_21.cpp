
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <vector>



using namespace std;


class myFunctorClass {
public:
	bool operator()(const vector<int*>* p1, const vector<int*>* p2) const;
};
bool myFunctorClass:: operator()(const vector<int*>* p1, const vector<int*>* p2) const {

	int sum1{ 0 }, sum2{ 0 };
	for (auto& i : *p1) { sum1 += *i; }
	for (auto& i : *p2) { sum2 += *i; }
	return sum1 < sum2;
}

class myFunctorClass1 {
public:
	size_t operator()(const vector<int*>* p) const;
	bool operator()(const vector<int*>* p1, const vector<int*>* p2) const;
};
bool myFunctorClass1:: operator()(const vector<int*>* p1, const vector<int*>* p2) const {

	int sum1{ 0 }, sum2{ 0 };
	for (auto& i : *p1) { sum1 += *i; }
	for (auto& i : *p2) { sum2 += *i; }
	return sum1 == sum2;
}

size_t myFunctorClass1::operator()(const vector<int*>* p) const {
	int sum{ 0 };
	for (auto& i : *p) { sum += *i; }
	return hash<int>{}(sum);

}

ostream& operator<<(ostream& str, const set<vector<int*>*, myFunctorClass>& S);
ostream& operator<<(ostream& str, const unordered_set<vector<int*>*, myFunctorClass1, myFunctorClass1>& H);
int main() {

	set<vector<int*>*, myFunctorClass>  S1{
	new vector<int*> { new int {6}, new int{8}, new int {5}},
	new vector<int*> { new int {4}, new int{2}, new int {15}},
	new vector<int*>{ new int {7}, new int{1}, new int {0}},
	new vector<int*>{ new int {4}, new int{2}, new int {6}}
	};
	cout << S1 << endl;
	cout << endl;

	unordered_set<vector<int*>*, myFunctorClass1, myFunctorClass1> H1{
		//The first myFunctorClass1 is for the functor of hashing and the second myFunctorClass1 is for the functor
		//of equal_to
	new vector<int*> { new int {6}, new int{8}, new int {5}},
	new vector<int*> { new int {4}, new int{2}, new int {15}},
	new vector<int*>{ new int {7}, new int{1}, new int {0}},
	new vector<int*>{ new int {4}, new int{2}, new int {6}}
	};
	cout << H1 << endl;



	return 0;
}
ostream& operator<<(ostream& str, const set<vector<int*>*, myFunctorClass>& S) {
	str << "<" << endl;
	for (auto& i : S) { //i is vector<int *> *
		str << "[ ";
		for (auto& j : *i) //j is int *
		{
			str << *j << " ";
		}
		str << "]" << endl;
	}
	str << ">" << endl;
	return str;

}
ostream& operator<<(ostream& str, const unordered_set<vector<int*>*, myFunctorClass1, myFunctorClass1>& H) {

	str << "<" << endl;
	for (size_t i = 0; i < H.bucket_count(); ++i){
		str << "Bucket " << i << "containts: " << endl;
		for (auto it1 = H.begin(i); it1 != H.end(i); ++it1) {
			str << "[ ";
			for (auto j : **it1) {
				str << *j << " ";
			}
			str << "]" << endl;
		}
	}
	str << ">" << endl;

	return str;

}