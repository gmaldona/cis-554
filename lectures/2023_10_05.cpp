//Recursive Operation with Trees
#include <iostream>
#include <typeinfo>
using namespace std;

class node {
public:
	int value;
	node* Lchild;
	node* Rchild;
	node(int i) : value(i), Lchild{ nullptr }, Rchild{ nullptr } {}
	node() { Lchild = Rchild = nullptr; }
};
class tree {//Full binary trees: 1, 3, 7, 15 ,   2^k-1 nodes
public:
	node* root;
	tree() { root = nullptr; }
	tree(int n, int m);//constructor
	node* Const_help(int n, int m);
	node* MakeTree(int n, int m);//Make a full binary tree with n level and random values in 0 ...m-1
	void InOrderT(node* p);//Inorder Traveral of a subtree whose root is pointed by p
	void PreOrderT(node* p);
	void PostOrderT(node* p);
	void Mirror(node* p);//Restructure the subtree pointed by p into its mirror
	int Sum(node* p);//Sum the node values of a subtree pointed by p
	bool Find(int k, node* p);//determine if value k exists in the subtree pointed by p

	node* NewMirror(node* p);//Create a new tree which is mirror of the subtree pointed by p
	void maxHeap(node* p);//rearrange the subtree whose root pointed by p into a maxHeap

};


void tree::maxHeap(node* p) {
	//not as efficient as the heapify algoritm in textbook
	//if (!p || !p->Lchild) return;
	//maxHeap(p->Lchild);
	//maxHeap(p->Rchild);
	//if (p->value < p->Lchild->value) swap(p->value, p->Lchild->value);
	//if (p->value < p->Rchild->value) swap(p->value, p->Rchild->value);
	//maxHeap(p->Lchild);//this can be performed only if swap did happen
	//maxHeap(p->Rchild);//this can be performed only if swap did happen


	if (!p || !p->Lchild) return;
	maxHeap(p->Lchild);
	maxHeap(p->Rchild);
	node* p1{ p->Lchild };
	if (p1->value < p->Rchild->value) p1 = p->Rchild;
	if (p->value < p1->value) {
		swap(p->value, p1->value);
		maxHeap(p1);
	}
}

node* tree::Const_help(int n, int m) {
	if (n == 0) return nullptr;//NULL is nullptr and zero; don't use it anymore
	//int i{ NULL }; i is 0
	node* p{ new node{ rand() % m } };
	p->Lchild = Const_help(n - 1, m);
	p->Rchild = Const_help(n - 1, m);
	return  p;
}


tree::tree(int n, int m) {

	root = Const_help(n, m);

}


node* tree::NewMirror(node* p) {
	if (!p) return nullptr;
	node* p1{ new node{p->value} };
	p1->Lchild = NewMirror(p->Rchild);
	p1->Rchild = NewMirror(p->Lchild);
	return p1;
}
bool tree::Find(int k, node* p) {
	if (!p) return false;
	return Find(k, p->Lchild) || (p->value == k) || Find(k, p->Rchild);
}


int tree::Sum(node* p) {
	if (!p) return 0;
	return Sum(p->Lchild) + p->value + Sum(p->Rchild);
}

void tree::Mirror(node* p) {
	if (!p || !p->Lchild) return;//0 or 1 node
	Mirror(p->Lchild);
	Mirror(p->Rchild);
	swap(p->Lchild, p->Rchild);
	/*
	int i1{5}, i2{6};
	swap(i1, i2}; //i1 : 6   i2 : 5

	int * p1 {new int{1}}, *p2 {  new int{ 3}};
	swap(p1, p2);  //p1 points to 3 and p2 points to 1

	*/

}

void tree::PostOrderT(node* p) {
	if (!p) return;
	PostOrderT(p->Lchild);
	//cout << p->value << " ";
	PostOrderT(p->Rchild);
	cout << p->value << " ";
}

void tree::PreOrderT(node* p) {
	if (!p) return;
	cout << p->value << " ";
	PreOrderT(p->Lchild);
	//cout << p->value << " ";
	PreOrderT(p->Rchild);
}

void tree::InOrderT(node* p) {
	if (!p) return;
	InOrderT(p->Lchild);
	cout << p->value << " ";
	InOrderT(p->Rchild);
}

node* tree::MakeTree(int n, int m) {
	if (n == 0) return nullptr;
	node* p{ new node{rand() % m} };
	p->Lchild = MakeTree(n - 1, m);
	p->Rchild = MakeTree(n - 1, m);
	return p;
}


int main() {
	tree T1;
	T1.root = T1.MakeTree(3, 10);// 7 nodes
	T1.InOrderT(T1.root);
	cout << endl;
	T1.PreOrderT(T1.root);
	cout << endl;
	T1.PostOrderT(T1.root);
	cout << endl;


	T1.Mirror(T1.root);
	T1.InOrderT(T1.root);
	cout << endl;

	//cout << T1.Sum(T1.root) << endl;


	//cout << T1.Find(4, T1.root) << " " << T1.Find(5, T1.root) << " " << T1.Find(9, T1.root) << endl;

	//tree T2;
	//T2.root = T1.NewMirror(T1.root);
	//T1.InOrderT(T1.root);
	//cout << endl;

	//T2.InOrderT(T2.root);
	//cout << endl;

	//cout << "***********" << endl;

	//tree T3{ 3, 9 };
	//T3.InOrderT(T3.root);
	//cout << endl;
	//T3.PreOrderT(T3.root);
	//cout << endl;
	//T3.PostOrderT(T3.root);
	//cout << endl;

	//T3.maxHeap(T3.root);
	//T3.InOrderT(T3.root);
	//cout << endl;


	return 0;
}
