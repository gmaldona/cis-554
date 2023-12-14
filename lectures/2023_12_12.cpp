#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

class myData {
	int* pI;
	double d;
	map<list<int*>*, vector<int*>> M;
	vector<list<float*>>* pV;
public:
	myData();
	myData(const myData& D);
	myData(myData&& D);
	void operator=(const myData& D);
	void operator=(myData&& D);
	~myData();
};


myData::myData() {
	pI = nullptr;
	d = 0.0;
	pV = nullptr;
}

myData::myData(const myData& D) {
	pI = new int(*(D.pI));
	d = D.d;
	for (auto& i : D.M) {
		list<int*>* l1 = new list<int*>();
		for (auto& j : *(i.first)) {
			l1->push_back(new int(*j));
		}
		vector<int*> V1;
		for (auto& j : i.second) {
			V1.push_back(new int(*j));
		}
		M[l1] = V1;
	}
	pV = new vector<list<float*>>();
	for (auto& i : *(D.pV)) {
		list<float*> l1;
		for (auto& j : i) {
			l1.push_back(new float(*j));
		}
		pV->push_back(l1);
	}

}

myData::myData(myData&& D) {
	pI = D.pI;
	D.pI = nullptr;
	d = D.d;
	M = D.M;
	D.M.clear();
	pV = D.pV;
	D.pV = nullptr;
}

void myData::operator=(const myData& D) {
	if (this == &D) return;
	//release the memory already used
	delete pI;
	for (auto& i : M) {
		for (auto& j : *(i.first)) {
			delete j;
		}
		delete i.first;
		for (auto& j : i.second) {
			delete j;
		}
	}
	if (pV) {
		for (auto& i : *(pV)) {
			for (auto& j : i) {
				delete j;
			}
		}
		delete pV;
	}
	

	//Copying the values
	pI = new int(*(D.pI));
	d = D.d;
	for (auto& i : D.M) {
		list<int*>* l1 = new list<int*>();
		for (auto& j : *(i.first)) {
			l1->push_back(new int(*j));
		}
		vector<int*> V1;
		for (auto& j : i.second) {
			V1.push_back(new int(*j));
		}
		M[l1] = V1;
	}
	pV = new vector<list<float*>>();
	for (auto& i : *(D.pV)) {
		list<float*> l1;
		for (auto& j : i) {
			l1.push_back(new float(*j));
		}
		pV->push_back(l1);
	}
}

void myData::operator=(myData&& D) {
	//release the memory already used
	delete pI;
	for (auto& i : M) {
		for (auto& j : *(i.first)) {
			delete j;
		}
		delete i.first;
		for (auto& j : i.second) {
			delete j;
		}
	}
	if (pV) {
		for (auto& i : *(pV)) {
			for (auto& j : i) {
				delete j;
			}
		}
		delete pV;
	}

	//move the values
	pI = D.pI;
	D.pI = nullptr;
	d = D.d;
	M = D.M;
	D.M.clear();
	pV = D.pV;
	D.pV = nullptr;
}

myData::~myData() {
	delete pI;
	for (auto& i : M) {
		for (auto& j : *(i.first)) {
			delete j;
		}
		delete i.first;
		for (auto& j : i.second) {
			delete j;
		}
	}
	if (pV) {
		for (auto& i : *(pV)) {
			for (auto& j : i) {
				delete j;
			}
		}
		delete pV;
	}
}