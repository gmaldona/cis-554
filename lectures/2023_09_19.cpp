//Operator Overloading
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;


int GlobalVar1;//global variables come with default value  0

class ThreeD {
public://not needed if using struct instead of class
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) : ht(10 * i), wid(10 * j), dep(10 * k) {}
	ThreeD(const initializer_list<int>& I);

	ThreeD() { ht = wid = dep = 0; }//default constructor


	int vol() const { return ht * wid * dep; }

	ThreeD operator+(const ThreeD& t);//t : pass by reference, read-only


	ThreeD operator++();//prefix  ++t3




	ThreeD operator++(int NeverUsed);//postfix
	int& operator[](int k);//return by reference;  operator subscript


	bool operator<(const ThreeD& t) const { return vol() < t.vol(); }

	friend istream& operator >>(istream& str, ThreeD& t);//Need this if not in public mode

	friend ostream& operator << (ostream& str, const ThreeD& t);//Need this if not in public mode

};
ThreeD::ThreeD(const initializer_list<int>& I) {
	auto p{ I.begin() };
	ht = *p;
	p++;
	wid = *p;
	p++;
	dep = *p;
}

int& ThreeD::operator[](int k) {//return by reference
	//It return an object rather than the value of the object.
	switch (k) {
	case 0: return ht;//return t3.ht
	case 1: return wid;
	case 2: return dep;
	}

}
ThreeD ThreeD::operator++(int NeverUsed) {//postfix  t++;
	ThreeD temp{ *this };
	ht++;
	wid++;
	dep++;
	return temp;
}
ThreeD ThreeD::operator++() {//prefix
	++ht;
	++wid;
	++dep;
	return *this;//"this" is a pointer pointing to the current object

}

ThreeD ThreeD::operator+(const ThreeD& t) {
	ThreeD temp;
	temp.ht = ht + t.ht;//t1.operator+(t2);
	temp.wid = wid + t.wid;
	temp.dep = dep + t.dep;
	return temp;

}

istream& operator >>(istream& str, ThreeD& t);//function prototype

//>>  operator extraction


ostream& operator << (ostream& str, const ThreeD& t);

//<<  operator insertion
// cout << t3 <<endl;  //t3 is a ThreeD object


ostream& operator << (ostream& str, const vector<int>& V);
int& F1();//function prototype
int& F2();



int main() {
	ThreeD t233{ 10,20, 30 }; //initializer_list > constructor > aggregate initialization
	ThreeD t234(10, 20, 30);//will invoke constructor


	ThreeD t400;
	cin >> t400;
	cout << t400 << endl;

	int k{ 10 };
	int& r21{ k };//r21 is an alias of k;
	r21 = 15;
	cout << k << endl; //15
	//map<int, vector<list<vector<int>>>> Map1;
	//
	//int &R1 { ( (Map1.begin()->second)[3].front())[2] };
	//R1 = 5; //( (Map1.begin()->second)[3].front())[2] = 5;

	//int& r22; Error.  You need to immediately specify the reference object.

	const int& r23{ k };//the object referenced through r23 is const
	r21 = 50;
	//r23 = 55;
	k = 100;
	cout << r23 << endl;//100

	F2() *= 2;//GlovalVar1 = GlovalVar1 *2;
	//100 = ...  if return by value is used in F2.
	//GlovalVar1 is defined in main.

	cout << GlobalVar1 << endl;
	/*
	General guideline of using return by reference:
	The return object has to be well defined (legal) in the scope of calling function (i.e., caller),

	I suggest that you always follow the general guideline.

	*/


	The following (between &&&&&  ) is unique behavior of Visual Studio.
	&&&&&&&&&&&&&&
	int w;
	w = F1();//directly push value to w without first creating a temporary object.
	//If a compiler implements RVO, it tends to allow the above.
	//RVO: Return Valuie Optimization.
	cout << w << endl;
	cout << F1() << endl;

	w = (F1() = 200);
	cout << w << endl;
	int w1;
	w1 = (w = 55);//w=55; will return 55. w1 becomes 55.
	cout << w1 << endl;//55
	cout << (w1 = 77) << endl;//77

	int& r1{ F1() };

	cout << r1 << endl;
	r1++;
	cout << r1 << endl;

	int* p1{ &F1() };
	cout << *p1 << endl;


	&&&&&&&&&&&&&&&&&&&




	//ThreeD t11;
	//cin >> t11;
	//cout << t11 << endl;
	ThreeD t1{ 1,2,3 }, t2{ 1,1,1 }, t3;
	t3 = t1 + t2;//t3 = t1.operator+(t2);
	//Compiler will change it into t3 = t1.operator+(t2);
	++t3;//prefix operator t3.operator++();

	t3++;//postfix operaotr  compiler will change it to t3.operator++(0); 0 can be any int value






	cout << t3[0] << " " << t3[1] << " " << t3[2] << endl;//operator subscript
	//t3[0] will be converted to t3.operator[](0)
	t3[1] = 25;//40 = 25;
	//t3.wid = 25;


	int q{ 23 };
	//q++ *= 2;  Error  postfix uses return by value
	++q *= 2;//prefix uses return by reference
	cout << q << endl;





	cout << t3 << endl;



	vector<int> V1{ 1,2,3,4,5 };
	cout << V1 << endl;

	set<ThreeD> Set1{ t1, t2 };
	for (auto& i : Set1) cout << t1 << "  " << t2 << endl;



	pair<int, int> p101{ 3,6 };
	p101.first *= 2;
	p101.second *= 3;
	cout << p101.first << "  " << p101.second << endl;

	tuple<int, string, int*> tp1{ 5, "Tuple example", new int{4} };
	cout << get<0>(tp1) << " " << get<1>(tp1) << " " << *get<2>(tp1) << endl;
	get<1>(tp1) = "A new example";

	return 0;
}
istream& operator >>(istream& str, ThreeD& t) { //operator extraction
	str >> t.ht >> t.wid >> t.dep;
	return str;
}

//cin >> t4
ostream& operator << (ostream& str, const ThreeD& t) {//<< is operator insertion
	str << "[" << t.ht << ", " << t.wid << ", " << t.dep << "]";
	return str;

	//cout << t3 <<endl;
}
ostream& operator << (ostream& str, const vector<int>& V) {
	str << "[ ";
	for (auto& i : V) str << i << " ";
	str << "]";
	return str;
}
int& F1() {//Not fillowing the general guideline.
	int i1{ 100 };
	return i1;//many compilers will give errors

}
int& F2() {
	//int i1{ 100 };
	GlobalVar1 = 100;
	//return i1;
	return GlobalVar1;//return by value: will return value 100
	//return by reference:  will return the object GlovalVar1;
}