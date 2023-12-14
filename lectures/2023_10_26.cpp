
//Smart Pointers  -- No more delete
#include <iostream>
#include <memory>
#include <list>

using namespace std;

int gv1;

int main() {
	int* rp1{ new int{5} };//Raw Pointer

	int* ppp3;//ppp3's value is undefined. 

	//There are three types of smart pointers: Unique, Shared, and Weak
	//All smart pointers will have a default value of nullptr

	//Unique pointers
	unique_ptr<int> up1{ make_unique<int>(5) };//up1 points to unique object 5
	//unique_ptr<int> up1{ make_unique<int>{5} }; {} will not work. 

	unique_ptr<int> up2;
	//up2 = up1; Error!  Unique object can only be pointed by one unique pointer

	up1.reset(); //the same as up1 = nullptr;
	//Object 5 will be automatically deleted because number of pointers pointing to it (i.e., reference count (RC)) is 0.

	up1.reset(new int{ 6 });//up1 points to unique object 6.
	//up1.reset(make_unique<int>(8));  won't compile




	//shared pointer -- the regular smart pointers

	shared_ptr<int> sp1{ make_shared<int>(10) }; //sp1 points to shared object 10
	{
		shared_ptr<int> sp2{ sp1 };
		cout << sp1.use_count() << endl;//reference count  is 2  or reference number is 2
	}
	//sp2 is now out of scope
	cout << sp1.use_count() << endl;//reference count 1
	sp1.reset();
	//Object 10 will be automatically deleted because RC = 0

	sp1.reset(new int{ 25 });//sp1 points to shared object 25
	//sp1.reset(make_shared<int>(25)); will not compile


	int* rp2{ new int {30} };

	shared_ptr<int> sp3{ rp2 };//both rp2 and sp3 point to object 30

	cout << *rp2 << " " << *sp3 << endl;//30 30

	if (sp3.get() == rp2) cout << "YES, they point to the same object" << endl;
	cout << sp3 << "  " << rp2 << endl;

	sp3.reset();
	//cout << *rp2 << endl;  error!  The object has been deleted.
	//Raw pointers do not contribute to reference count.


	/*

	For unique_ptr and shared_ptr, operator * and operator -> work like regular pointers.
	*/


	//weak pointers

	//weak_ptr<int> wp1{ make_weak<int>(10) }; Error
	shared_ptr<int> sp5{ make_shared<int>(100) }; //sp5 points to shared object 100
	weak_ptr<int> wp1{ sp5 };//wp1 will point to shared object 100

	cout << sp5.use_count() << endl; //1
	//weak pointers do not contribute to reference count
	//weak pointers do not support operator * and operator ->

	//cout << *wp1 <<endl; Error!
	cout << *wp1.lock() << endl;//lock() temporarily create a shared pointer to be used only within current statement

	*wp1.lock() = 1000;//OK


	weak_ptr<int> wp2{ wp1 };

	weak_ptr<int> wp3;
	wp3 = sp5;//assign shared_ptr to weak_ptr  is OK
	//sp5 = wp2;  Error  you cannot assign weak_ptr to shared_ptr

	shared_ptr<int> sp11{ make_shared<int>(25) }, sp12;
	weak_ptr<int> wp11, wp12;
	wp11 = sp11;
	wp12 = wp11;
	sp12 = wp12.lock();

	cout << sp11.use_count() << endl;//sp11 and sp12

	cout << wp11.use_count() << endl;//2

	wp11.reset();
	
	//expired() checks if a weak_ptr is dangling (i.e., the object it points to has been deleted.)?
	if (wp12.expired()) cout << "the object pointed by wp12 has been deleted" << endl;
	else cout << "The object pointed by wp12 has not been deleted" << endl;



	shared_ptr<int> sp6;
	sp6 = wp1.lock();  //sp6 = wp1; will not compile
	//wp1.lock()-> ....
	sp6.reset();
	sp5.reset(new int{ 33 });
	//Object 100 will be automatically deleted
	//cout << *wp1.lock() << endl; //Error






	weak_ptr<int> wp35{ make_shared<int>(250) };

	//Object 250 will be created and immediately deleted because RC is 0.

	list<int>* p300{ new list<int>{1,2,3,4,5} };


	shared_ptr<list<int>> sp10{ make_shared < list<int>>(initializer_list<int>{1,2,3,4,5}) };



	list<int*>* P11;//It is much easier to use raw pointers.


	// It is quite cumbersome to use smart pointers for long expressions.

	shared_ptr<list< shared_ptr<int>>> sp111{

	make_shared<list<shared_ptr<int>>>(initializer_list<shared_ptr<int>>{make_shared<int>(1), make_shared<int>(2)})
	};

	//for (auto& i : *sp111) {  range-based for loop also works on smart pointer
	//	cout << *i << " ";
	//}
	cout << endl;




	return 0;
}