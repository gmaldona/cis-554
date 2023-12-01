//HW6.  Due: Monday, Nov. 27 at 11:59pm

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional>

using namespace std;

class node {
 public:
  int value;
  node *next;
  node(int i) {
    value = i;
    next = nullptr;
  }//construct
  node() { next = nullptr; }//default constructor

};

class LinkedList {
 public:
  node *head;
  LinkedList(int n, int m);//Constructor for an n-node linked list
  //with values randomly in 0 ... m-1


  LinkedList() { head = nullptr; } //default constructor

  void Sort();
  //You need to change this to allow the Sort examples in the main functions.
  void Sort(const std::function<bool(int, int)>&);
  //You can re-use code from lecture 2023_09_07 .

};

// Taken from lecture cis-554/lectures/2023_09_07.cpp <<------------------------------------------------------ 80 ------
LinkedList::LinkedList(int n, int m) {
  head = nullptr;
  for (int i = 0; i < n; ++i) {
    node* p{ new node{ rand() % m } };
    p->next = head;
    head = p;
  }
}

// Taken from lecture cis-554/lectures/2023_09_07.cpp <<------------------------------------------------------ 80 ------
void LinkedList::Sort() {
  LinkedList::Sort(less<int>{});
}

struct MyDisasterOfAHashingFunction {
  bool operator()(const map<map<int *, string> *, set<int> * >& m1, const map<map<int *, string> *, set<int> * >& m2) const;

  size_t operator()(const map<map<int *, string> *, set<int> * > &m) const;
};

size_t MyDisasterOfAHashingFunction::operator()(const map<map<int *, string> *, set<int> * > &m) const {
  int count = 0;
  for (const auto& [p, s] : m) {
    for (const auto& X : *s) {
      count += X;
    }
  }
  return hash<int>{}(count) ^ hash<int>{}(count * -1) >> 1;
}

bool MyDisasterOfAHashingFunction::operator()(const map<map<int *, string> *, set<int> * >& m1, const map<map<int *, string> *, set<int> * >& m2) const {
  int count1 = 0;
  int count2= 0;

  for (const auto& [X, Y] : m1) {
    for (const auto& Z : *Y) {
      count1 += Z;
    }
  }

  for (const auto& [X, Y] : m2) {
    for (const auto& Z : *Y ) {
      count2 += Z;
    }
  }

  return count1 == count2;
}

/**
 * Copy sort from above BUT... instead of checking for less than, pass in func.
 * @param func Function that compared two integers. Don't care how just care about the output true/false :)
 */
void LinkedList::Sort(const std::function<bool(int, int)>& func) {

  if (!head || !head->next) return;

  node* p1{ head };
  while (p1->next) {
    node* p2 = p1->next;
    node* pmin = p1;
    int min{ p1->value };
    while (p2) {
      if (func(p2->value, min)) { // <============ BAZINGA =============================================================
        min = p2->value;
        pmin = p2;
      }
      p2 = p2->next;
    }
    if (pmin != p1) {
      pmin->value = p1->value;
      p1->value = min;
    }
    p1 = p1->next;
  }

}

//When sorting structures, always sort the sums of all numbers within the structure.
//when comparing equality of two structures, always compare sums of all int values in the structures
//When Hashing a structure, always hash the sum of all int values in the structure
//For printing, following the following natations.  map: { ...}   set(or unordered set): <...>
ostream &operator<<(ostream &oss, set<map<map<int *, string> *, set<int> *>> set) {
  oss << "<" << endl;
  oss << "{" << endl;
  for (auto const& entry : set) {
    // cool c++ looping c++17 and above
    // https://stackoverflow.com/questions/26281979
    for (auto const& [key, val] : entry) {
      auto& peopleTheGovernmentAreWatching = *key;
      auto& CoffeesYum = *val;
      oss << "{ ";

      for (auto const& [governmentID, governmentName] : peopleTheGovernmentAreWatching) {
        oss << *governmentID << " " << governmentName << " ";
      }

      oss << " }   ";

      oss << "< ";
      for (auto const& numberOfCoffeesTheyBought : CoffeesYum) {
          oss << numberOfCoffeesTheyBought << " ";
      }
      oss << ">   ";
    }
    oss << endl;

  }
  oss << "}" << endl;
  oss << ">" << endl;

  return oss;
}

ostream &operator<<(ostream &oss, unordered_set<map<map<int *, string> *, set<int> * >, MyDisasterOfAHashingFunction, MyDisasterOfAHashingFunction>& buckets) {
      int i = 0;
      for (auto& bucket: buckets) {
        oss << "bucket " << i << " contains: " << std::endl;

        if (bucket.size() == 0) {
          i++;
          continue;
        }

        oss << "{" << std::endl;
        // cool c++ looping c++17 and above
        // https://stackoverflow.com/questions/26281979
        for (auto const& [innerMap, innerSet] : bucket) {
          if (! innerMap || ! innerSet) { break; }
          oss << "{ ";
          for (auto const& [someCount, EmployeeName] : * innerMap) {
            oss << *someCount << " " << EmployeeName << " ";
          }
          oss << "} ";

          oss << "< " ;
          for (auto const& someOtherCountHa : * innerSet) {
            oss << someOtherCountHa << " ";
          }
          oss << "> ";
        }
        oss << "}" << std::endl;
        i++;
      }

    return oss;
 }

ostream &operator<<(ostream &oss, LinkedList LL) {
  node*& ptr = LL.head;
  while(ptr) {
    oss << ptr->value << " ";
    ptr = ptr->next;
  }
  return oss;
}

int main() {
  //The following statement won't compile. Fix it.
  //Set initial values for S1.  Every structure, set or map, needs to have at least 3 elements.

  // { 1 Drew 2 Bud 3 Doug }   < 0 1 6 >   { 1 Ray 2 Tim 6 Tracy }   < 1 2 5 >   { 2 Jacob 4 Chris 7 Ken }   < 0 1 7 >
  map<map<int *, string> *, set<int> *>  E1 {
      { new map<int*, string>{
                             { new int{1}, string("Drew")  },
                             { new int{2}, string("Bud")   },
                             { new int{3}, string("Doug")  },
      }, new set{ 0, 1, 6 } },

      { new map<int*, string>{
                             { new int{1}, string("Ray")   },
                             { new int{2}, string("Tim")   },
                             { new int{6}, string("Tracy") },
      }, new set{ 1, 2, 5 } },

      { new map<int*, string>{
                            { new int{2}, string("Jacob")   },
                            { new int{4}, string("Chris")   },
                            { new int{7}, string("Ken")     },
      }, new set{ 0, 1, 7 } },
  };

  // The example does not initial 3 ... Following the example and probably get points off lol
  // { 2 Nancy 5 Jeff 7 Bob }   < 1 5 9 >   { 3 Mary 12 Jim 15 Dan }   < 0 1 2 >
  map<map<int *, string> *, set<int> *>  E2 {
      { new map<int*, string>{
                            { new int{2}, string("Nancy")  },
                            { new int{5}, string("Jeff")   },
                            { new int{7}, string("Bob")    },
      }, new set{ 1, 5, 9 } },

      { new map<int*, string>{
                            { new int{3}, string("Mary")    },
                            { new int{12}, string("Jim")    },
                            { new int{15}, string("Dan")    },
      }, new set{ 0, 1, 2 } },

      { new map<int*, string>{
          { new int{2}, string("Jacob")   },
          { new int{4}, string("Chris")   },
          { new int{7}, string("Ken")     },
      }, new set{ 0, 1, 7 } },
  };

  // { 1 Bill 2 Mike 5 Steve }  < 1 3 6 >   { 1 Jerry 8 Joe 9 Zach }   < 1 2 4 >   { 7 Wendy 9 Marty 12 Ed }   < 0 1 3 >
  map<map<int *, string> *, set<int> *>  E3 {
      { new map<int*, string>{
                           { new int{1}, string("Bill")     },
                           { new int{2}, string("Mike")     },
                           { new int{5}, string("Steve")    },
      }, new set{ 1, 3, 6 } },

      { new map<int*, string>{
                           { new int{1}, string("Jerry")    },
                           { new int{8}, string("Joe")      },
                           { new int{9}, string("Zach")     },
      }, new set{ 1, 2, 4 } },

      { new map<int*, string>{
                           { new int{7}, string("Wendy")    },
                           { new int{9}, string("Marty")    },
                           { new int{12}, string("Ed")      },
      }, new set{ 0, 1, 3 } },
  };


  set<map<map<int *, string> *, set<int> *>> S1 { E1, E2, E3 };

  //You need to support the following statement.
  cout << S1 << endl;

  //The following statement won't compile. Fix it.
  //Set initial values for H1.  Every structure, set or map, needs to have at least 3 elements.

  //The first myFunctorClass1 is for the functor of hashing and the second myFunctorClass1 is for the functor
  //of equal_to

  map<map<int *, string> *, set<int> *> X1 =  map<map<int *, string> *, set<int> * > {

      { new map<int*, string>{
          { new int{2}, string("Nancy")  },
          { new int{5}, string("Jeff")   },
          { new int{7}, string("Bob")    },
      }, new set{ 1, 5, 9 } },

      { new map<int*, string>{
          { new int{3}, string("Mary")    },
          { new int{12}, string("Jim")    },
          { new int{15}, string("Dan")    },
      }, new set{ 0, 1, 2 } }

  };

  map<map<int *, string> *, set<int> *> X2 =  map<map<int *, string> *, set<int> * > {
      { new map<int*, string>{
          { new int{1}, string("Drew")  },
          { new int{2}, string("Bud")   },
          { new int{3}, string("Doug")  },
      }, new set{ 0, 1, 6 } },

      { new map<int*, string>{
          { new int{1}, string("Ray")   },
          { new int{2}, string("Tim")   },
          { new int{6}, string("Tracy") },
      }, new set{ 1, 2, 5 } },

      { new map<int*, string>{
          { new int{2}, string("Jacob")   },
          { new int{4}, string("Chris")   },
          { new int{7}, string("Ken")     },
      }, new set{ 0, 1, 7 } },
  };

  map<map<int *, string> *, set<int> *> X3 =  map<map<int *, string> *, set<int> * > {
      { new map<int*, string>{
          { new int{1}, string("Bill")     },
          { new int{2}, string("Mike")     },
          { new int{5}, string("Steve")    },
      }, new set{ 1, 3, 6 } },

      { new map<int*, string>{
          { new int{1}, string("Jerry")    },
          { new int{8}, string("Joe")      },
          { new int{9}, string("Zach")     },
      }, new set{ 1, 2, 4 } },

      { new map<int*, string>{
          { new int{7}, string("Wendy")    },
          { new int{9}, string("Marty")    },
          { new int{12}, string("Ed")      },
      }, new set{ 0, 1, 3 } },
  };

  unordered_set<map<map<int *, string> *, set<int> * >, MyDisasterOfAHashingFunction, MyDisasterOfAHashingFunction> H1 { X1, X2, X3 };

  //You need to support the following statement.
  // BUCKETS \/\/\/\/\/\/\/
  cout << H1 << endl; //Print bucket.  See sample screenshots.
//
  LinkedList L1{20, 10};
  cout << L1 << endl;
  L1.Sort();
  cout << L1 << endl;

  L1.Sort([](int a, int b) { return a % 3 < b % 3; }); // this function does not want to work

  cout << L1 << endl;
  L1.Sort(greater<int>{});

  cout << L1 << endl;

  std::function<void(const map<map<int *, string> *, set<int> *>&)> del = [&](const map<map<int *, std::string> *, set<int> *>& in) {
      for (auto& [X, Y] : in) {
          for (auto& [A, B] : *X) {
            delete A;
          }
          delete X;
          delete Y;
      }
  };

  for (auto& X : H1) {
    del(X);
  }

  for (auto& X : S1) {
    del(X);
  }
  std::function<void(node*&)> del_L;
//  delete L1.head;
   del_L = [&](node*& n) {
    if (! n) {
      return;
    }
    del_L(n->next);
    delete n;
  };

   del_L(L1.head);

  return 0;
}
