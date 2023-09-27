
//Template -- A way to pass certain generic data type to a class or function
// Generic Programming
//Programming with templates is called generic programming
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ThreeD1 {
public:
	int ht;
	int wid;
	int dep;
};
class ThreeD2 {
public:
	float ht;
	float wid;
	float dep;
};
template <typename T> class ThreeD {
	//template <class T> is alos OK
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) {
		ht = 10 * i;
		wid = 10 * j;
		dep = 10 * k;
	}
	ThreeD() { ht = wid = dep = (T)0; }
	T vol() const { return ht * wid * dep; }
	T area () const;
	bool operator<(const ThreeD<T>& t) const { return area() < t.area(); }//vol() is this->vol()
	//second const is to protect this->ht, this->wid, this->dep
};

template <typename T> T ThreeD<T>::area() const{
	return 2 * (ht * wid + wid * dep + dep * ht);
}
template <typename T> T f1(T i) { return i * (T)2; }

template <typename T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <typename T1, typename T2> ostream& operator<<(ostream& str, const map<T1, T2>& m);
//typename can be replaced with class.


template <class T> ostream& operator<<(ostream& str, const vector<T>& V);


int main() {




	ThreeD1 tt1{ 1,2,3 };
	ThreeD2 tt2{ 1.1f,2.2f,3.3f };

	ThreeD<int> t1{ 1,2,3 }, t11{ 1,1,1 }, t12{ 2,2,1 };
	ThreeD<float> t2{ 1.11f, 2.22f, 3.34f };

	cout << t1 << t2 << endl;


	ThreeD<float> t3{ 7.22f, 3.11f, 4.41f }, t4{ 1.15f, 1.25f, 1.15f };

	map<ThreeD<float>, ThreeD<int>> m1{ {t2, t1}, {t3,t11 }, {t4, t12} };
	cout << m1 << endl;

	cout << "&&&&&&&&&&&&" << endl;
	cout << f1<char>('9') << endl;

	vector<int> V250{ 1,2,3,4,5,6 };
	vector<float> V251{ 1.11f, 2.22f, 3.33f, 4.44f };
	vector<ThreeD<int>> V252{ t1, t11, t12 };
	cout << V250 << endl << V251 << endl << V252 << endl;
	//The following is something I fortgot to mention in the lecture of operator overloading.

	map<ThreeD<int>, int> M55{ {t12, 10}, {t1, 500}, {t11,11} };



	return 0;
}


template <class T> ostream& operator<<(ostream& str, const vector<T>& V) {

	str << "[ ";
	for (auto& i : V) {//range based for loop
		str << i << " ";
	}
	str << "]";
	return str;

}

template <typename T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "[" << t.ht << ", " << t.wid << ", " << t.dep << "]";
	return str;

}
template <typename T1, typename T2> ostream& operator<<(ostream& str, const map<T1, T2>& m) {
	str << "{ ";
	for (auto& i : m) str << i.first << " " << i.second << "  ";
	str << "}";
	return str;
}