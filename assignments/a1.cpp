
//HW1: due Friday September 15,  at 11:59pm
/*
Implement member functions and  Merge.  Your implementation has to be in-place.
You are required to implement the Merge algorithm to be described in class.
You are not allowed to use any external structures (such as array)
You are not allowed to use any helper function
You are not allowed to create new nodes or any extra structures (such as array, list, etc.).
*/
#include <iostream>
using namespace std;

class Dnode {
public:
   int value;
   Dnode* next;
   Dnode* previous;
   Dnode(int i) { value = i; next = previous = nullptr; }
   Dnode() { next = previous = nullptr; }
};

class DLL {//Doubly Linked List
public:
   Dnode* head;
   Dnode* tail;
   DLL(int n, int m);//Constructor; Construct an n-node DLL with random
   //values in 0 ... m-1
   DLL() { head = tail = nullptr; }
   void PrintF();//Print forward from head
   void PrintB();//Print backward from tail

   //Add the statement below as well as the initializer_list implementation right after class DLL.
   DLL(const initializer_list<int>& I);//Initializer List


   void Sort(Dnode * p1, Dnode *p2);//Sort the portion of a DLL from
   //the Dnode pointed by p1 until the Dnode pointed by p2


   void Merge(Dnode* p1, Dnode* p2, Dnode* p3, Dnode* p4);
   //Merge the two portions of the Linked List, as described in clas and the video recording for merge algoirthm.
   //Note that each of the two portions is already sorted before the merge.

};


DLL::DLL(int n, int m) {
   head = tail = nullptr;
   for (int i = 0; i < n; ++i) {
      Dnode* p1{ new Dnode{rand() % m} };
      if (!head) {//empty
         head = tail = p1;
      }
      else {
         tail->next = p1;
         p1->previous = tail;
         tail = p1;
      }
   }
}

DLL::DLL(const initializer_list<int>& I) {//Implementation of initializer_list for class DLL
   head = nullptr;
   for (auto& i : I) {
      if (!head) head = tail = new Dnode{ i };
      else {
         tail->next = new Dnode{ i };
         tail->next->previous = tail;
         tail = tail->next;
      }
   }
}


void DLL::Sort(Dnode * p1, Dnode *p2) {
   if (!p1 || !p2) {
      return;
   }

   Dnode* outer_p{ p1 };
   Dnode* ending_p{ p2->next };
   // using a double pointer to keep track
   // outer_p holdings the constant node, the node to be swapped at the end
   while (outer_p != ending_p) {
      Dnode* next_in_line = outer_p->next;
      Dnode* inner_p{ outer_p };
      Dnode* min_p{ outer_p }; // holds the node with the minimum value
      int min_value = min_p->value;
      // inner_p is the moving pointer that will eventually hold the minimum pointer
      while ( inner_p != ending_p) {
         if (inner_p->value < min_value) {
            min_value = inner_p->value;
            min_p = inner_p;
         }
         inner_p = inner_p->next;
      }
      // have to check who is the HEAD node
      if (outer_p->previous == nullptr) {
         this->head = min_p;
      }
      if (outer_p->next == nullptr) {
         this->tail = min_p;
      }
      /*
       * in both cases its own pointer swapping is the same, the problem arises when updating the external references
       * to the newly swapped pointers
       *
       * assuming a right to left motion, inner_p is updating first
       */
      Dnode* temp_p_previous = outer_p->previous;
      Dnode* temp_p_next = outer_p->next;

      if (min_p != outer_p) {
         /* we need to check if the node is next to each other
          * Assuming right to left
          * if P_m_p = P_o then nodes are next to each other
          * special edge case where that you cant swap prev and next pointers because the min pointer previous will
          * not the previous's next, but the previous
          */
         if (min_p->previous == outer_p) {
            // external ptr swapping
            if (outer_p->previous) {
               outer_p->previous->next = min_p; // if there is a previous, we KNOW theres a next
            }
            if (min_p->next) {
               min_p->next->previous = outer_p; // if there is a next, we KNOW theres a previous
            }
            // internal ptr swapping
            temp_p_next = min_p->next;

            min_p->next = outer_p;
            min_p->previous = outer_p->previous;

            outer_p->previous = min_p;
            outer_p->next = temp_p_next;

         } else { // else case is the pointers have "space" in between (probably will refactor out to do an early return)
            //external ptr swapping
            if (outer_p->previous) {
               outer_p->previous->next = min_p;
            }
            if (outer_p->next) {
               outer_p->next->previous = min_p;
            }

            if (min_p->previous) {
               min_p->previous->next = outer_p;
            }
            if (min_p->next) {
               min_p->next->previous = outer_p;
            }

            // internal ptr swapping
            outer_p->previous = min_p->previous;
            outer_p->next = min_p->next;

            min_p->previous = temp_p_previous;
            min_p->next = temp_p_next;
         }
      }
      outer_p = next_in_line;
   }
}

void DLL::Merge(Dnode *p1, Dnode *p2, Dnode *p3, Dnode *p4) {
   if (!p1 || !p2 || !p3 || !p4) {
      return;
   }
   /**
    * Class note: p1 is the start of the first list
    *             p2 is the end of the first list
    *
    *             p3 is the start of the second list
    *             p4 is the end of the second list
    *  Class implementation:
    *       Have one inner_p_1 for list one and have another inner_p_2 for the second list
    *       compare inner_p_1 and inner_p_2
    * Class discussion of implementation:
    *       iterate over (p1,p2) and (p3,p4) at the same time. Compare inner_p's
    *       Assume: (p3,p4) > (p1,p2)
    *
    * e.g. p3_n where p3 < n < p4
    * if p3_n < p1_n then
    *   node belongs on the left side p1_n
    * else node belongs on the right side of p1_n
    *
    * if one interval ends before the other then finish. Copy the remaining of the longer list
    *
    * Note: Make sure if a node is merged in and is overriding the head/tail then update head/tail
    *       if two lists are connected:
    *           use p2->next will be the start of the next list. If the head of the second list is moved,
    *               possibility of infinite loop.
    *
    */

//   /*TODO: if the lists are next to each other and second list head moves then this pointer
//    * needs to be updated as well*/
      Dnode* ending_p1{ p2->next };
      Dnode* ending_p2{ p4->next };
      Dnode* inner_p1{ p1 };
      Dnode* inner_p2{ p3 };

      while (inner_p1 != ending_p1 && inner_p2 != ending_p2) {
         Dnode* next_p1 = inner_p1->next;
         Dnode* next_p2 = inner_p2->next;
         if (ending_p1 == inner_p2) { // if the lists are next to each other, then you need to update each iter
            ending_p1 = inner_p2->next;
         }

         if (inner_p2->value < inner_p1->value) {
            if (inner_p1->previous) {
               inner_p1->previous->next = inner_p2;
            }

            // L2 next needs to be updated
            inner_p2->previous->next = inner_p2->next;
            if (inner_p2->next) {
               inner_p2->next->previous = inner_p2->previous;
            }

            inner_p2->previous = inner_p1->previous;
            if (! inner_p2->previous) { // new head pointer
               this->head = inner_p2;
            }
            inner_p2->next = inner_p1;
//            if (! inner_p2->next) { // new tail pointer
//               this->tail = inner_p2;
//            }

            inner_p1->previous = inner_p2;

            inner_p2 = next_p2;
         } else {
            inner_p1 = next_p1;
         }
         // iterate over each node and manually find the tail node
         // not the best implementation :) 
         Dnode* p{this->head};
         while (p) {
            if (p->next == nullptr) {
               this->tail = p;
            }
            p = p->next;
         }
      }
}

void DLL::PrintF() {
   cout << endl;
   Dnode* p1{ head };
   while (p1) {
      cout << p1->value << " ";
      p1 = p1->next;
   }
}

void DLL::PrintB() {
   cout << endl;
   Dnode* p1{ tail };
   while (p1) {
      cout << p1->value << " ";
      p1 = p1->previous;
   }
}



int main() { //During grading, TA might use differnt examples to test your code.
   DLL  L1(5, 20);
   L1.PrintF();
//   L1.PrintB();

   L1.Sort(L1.head, L1.tail );
   L1.PrintF();

//   L1.PrintB();

   DLL L2(5, 15 );
   L2.Sort(L2.head, L2.tail);
   L2.PrintF();
   L1.tail->next = L2.head;
   L2.head->previous = L1.tail;
   L1.tail = L2.tail;
   L1.PrintF();

   L1.Merge(L1.head, L2.head->previous, L2.head, L1.tail);

   L1.PrintF();
   L1.PrintB();

   return 0;
}

