//HW5 Due: 11:59pm, Wednesday, Nov. 8
/*

For the class triangle, implement construcotr, copy constructor,
move constructor, copy assignment,
move assignment, destructor, FirtThreeRow.
Also, implement operator<< to allow cout of triangle object.
See the sample screehshot for output requirement

Only smart pointers are allowed.

No raw pointers allowed.
No extra helper functions allowed.
No external structures allowed.

*/

#include <iostream>
#include <memory>
using namespace std;

class node {
 public:
  int value;
  shared_ptr<node> Lchild;
  shared_ptr<node> Rchild;
  weak_ptr<node> next;
  node(int i) : value(i) {}
  node() {}

};

class triangle {
 public:
  shared_ptr<node> top;
  triangle(int n, int m);//constructor, n levels with node being random values in 0 ... m-1
  triangle() { cout << "Default Constructor\n\n"; }
  triangle(const triangle &t);//copy constructor
  void operator=(const triangle &t); //copy assignment
  ~triangle();//destructor
  triangle(triangle &&t);//move constructor
  void operator=(triangle &&t);//move assignment
  triangle FirstThreeRow();//return a triagle which is the first three rows of *this.
  //Assume the triangle *this have three or more than three rows.
};

triangle::triangle(const triangle &t) {
  cout << "Copy Constructor" << endl;
  this->top = t.top;
}

triangle::triangle(triangle &&t) {
  cout << "Move Assignment" << endl;
  this->top = t.top;
  t.top.reset();
}

void triangle::operator=(const triangle &t) {
  cout << "Copy Assignment" << endl;
  this->top.reset();
  this->top = t.top;
}

void triangle::operator=(triangle &&t) {
  cout << "Move Assignment" << endl;
  this->top.reset();
  this->top = t.top;
  t.top.reset();
}

triangle triangle::FirstThreeRow() {
  cout << "FirstThreeRows" << endl;
  weak_ptr<node> node_ptr = this->top;
  for (int i = 0; i < 6; ++i) { // starting to looking like a freshman coded this lol
    if (auto p = node_ptr.lock()) {
      if (i == 5) {
        p->next.reset();
      }
      node_ptr = p->next;
      continue;
    } else {
      break;
    }
  }
  return *this;
}

triangle::~triangle() {
  cout << "Destructor" << endl;
  top.reset();
}

triangle::triangle(int n, int m) {
  cout << "Constructor" << endl;

  int total = 0;

  if (n == 0) return;

  // save this for getting values for nodes
  // int value = rand() % m;
  for (int i = 1; i <= n; ++i) { total = total + i; }

  shared_ptr<node> root_ptr;
  weak_ptr<node> node_ptr; // a tracking node for which ever node we currently are on.
  // the way the loop is going to work is that node_ptr is init'ed and we are allocating node->next so then
  // the next iteration is node_ptr = node_ptr->next; !!!
  // this is a test. we start off with a weak_ptr that is set to null. we want to set the value of the pointer
  // to a new node.
  root_ptr = make_shared<node>(rand() % m); // the root!
  node_ptr = root_ptr;
  if (auto p = node_ptr.lock()) {
    p->Lchild = p; // trick so that the memory doesnt disappear
  }
  // create all the nodes in the tree := total
  for (int i = 1; i < total; ++i) {
    // double trick !
    if (auto p = node_ptr.lock()) {// de-referencing a weak_ptr: https://en.cppreference.com/w/cpp/memory/weak_ptr/lock
      p->Lchild = make_shared<node>(rand() % m);
      p->next = p->Lchild;
      node_ptr = p->next; // ew.

    }

  }

  // now that the nodes are created, we can modify the inner nodes to make the tree structure.
  // The pattern:
  // let the weak linked list represent an array with indices [0, len(arr)].
  // let N be the index a node.
  // let l be the level where the node N is.
  // let N>>L be the left node of N, N>>R be the right node of N.

  // N>>L := N + l + 0 , N>>R := N + l + 1
  // this can be done with two loops. Inefficiency here I come!
  node_ptr = root_ptr;
  int N = 0;
  int L = 1;
  int till_next_level = 1; // yes, I have given up, this is going to be some weird code.
  int next_level_counter = 0; // no regerts.
  while (auto p = node_ptr.lock()) {  //gimme all nodes.

    int left = N + L + 0;
    int right = N + L + 1;

    weak_ptr<node> left_node = root_ptr;
    for (int i = 0; i < left; ++i) {
      if (auto p = left_node.lock()) { // this is going to be miserable debugging !
        left_node = p->next;
      }
    }
    weak_ptr<node> right_node = root_ptr;
    for (int j = 0; j < right; ++j) {
      if (auto p = right_node.lock()) { // this is going to be miserable debugging !
        right_node = p->next;
      }
    }

    if (auto l = left_node.lock(); auto r = right_node.lock()) {
      if (auto p = node_ptr.lock()) {
        p->Lchild = l;
        p->Rchild = r;
      }
    }

    node_ptr = p->next; // thank you, next.
    N++;
    next_level_counter++;
    if (next_level_counter == till_next_level) { // ew.
      till_next_level++;
      next_level_counter = 0;
      L++;
    }
  }

//   test to see if all the nodes were properly generated 0.0 - GOOD!
  node_ptr = root_ptr;
  int test_count = 0;
  while (auto p = node_ptr.lock()) {
//    cout << p->value << " ";
    node_ptr = p->next;
    test_count++;
  }
//  cout << endl;
//  cout << "Expected: " << total << endl;
//  cout << "Actual: " << test_count << endl;

  this->top = root_ptr;
}

ostream &operator<<(ostream &oss, triangle triangle) {

  weak_ptr<node> node_ptr = triangle.top;
  int till_next_level = 1; // yes, I have given up, this is going to be some weird code.
  int next_level_counter = 0; // no regerts.

  while (auto p = node_ptr.lock()) {
    oss << p->value << " ";
    node_ptr = p->next;
    next_level_counter++;
    if (next_level_counter == till_next_level) {
      next_level_counter = 0;
      till_next_level++;
      oss << endl;
    }
  }
  return oss;
}

int main() {

  triangle T1(7, 10);
  cout << T1 << "\n\n";
  triangle T2{T1};
  cout << T2 << "\n\n";
  triangle T3;
  T3 = T2;
  cout << T3 << "\n\n";

  T3 = T2.FirstThreeRow();
  cout << T3 << "\n\n";

  return 0;
}