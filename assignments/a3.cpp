// HW3 by Gregory Maldonado
// SU Net ID: gmaldo02 SUID: 2012920852
//HW3
//Due: 11:59PM, Wednesday Oct. 11
//Reminder: Midterm Exam will be held on Tuesday, Oct. 17
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <iomanip>
using namespace std;

class course
{
 public:
   string name;//CIS554
   int section;//1
   int credits;//3
   string grade;//A-
   course()
   {
   }
   course(string n, int s, int c, string g)
   {
      name = n;
      section = s;
      credits = c;
      grade = g;
   }

   bool operator<(const course& c) const;
   bool operator==(const course& c) const;
   float num_grade();

};
float course::num_grade()
{
   map<string, float> M{
      { "A", 4.0f },
      { "A-", 3.667f },
      { "B+", 3.333f },
      { "B", 3.0f },
      { "B-", 2.667f },
      { "C+", 2.333f },
      { "C", 2.0f },
      { "C-", 1.667f },
      { "D", 1.0f },
      { "D-", 0.667f },
      { "F", 0.0f }
   };
   return M[grade];
}
bool course::operator<(const course& c) const
{
   return (name < c.name);
}
bool course::operator==(const course& c) const
{
   return (name == c.name);

}

class DBclass
{
 public:
   map<int, tuple<int, float, list<course*> >*>* pDB;
   DBclass();//default constructor
   DBclass(const initializer_list<pair<int,
                                       initializer_list<course>>>& I);//{"20222", "CIS554", "CS#381", "MAT398", "PSY205"};

   DBclass(const DBclass& D);//Copy Constructor

   //Implement copy constructor, copy assignment, move constructor, move assignment, destructor, RemoveFirst.
   //Also implement operator<< to allow cout << DBclassObject<<endl;

   ~DBclass();//Destructor
   void operator=(const DBclass& D);//Copy Assignment (i.e., Lvalue operator=)
   DBclass(DBclass&& D);//move constructor
   void operator=(DBclass&& D); //Move Assignment (i.e., Rvalue operator=)

   DBclass RemoveFirst();//Return a DBclass which is the same as *this,
   // but the removal of the first element of the map.
};

ostream& operator<<(ostream& str, const course& c);

ostream& operator<<(ostream& str, const DBclass& D);

DBclass::DBclass()
{//default constructor
   pDB = new map<int, tuple<int, float, list<course*> >*>{};
   cout << "Constructor" << endl;
}

DBclass::DBclass(const DBclass& D)
{
   cout << "Constructor" << endl;
   cout << "Copy Constructor" << endl;
   pDB = new map<int, tuple<int, float, list<course*> >*>{};

   for (auto& semester : *D.pDB)
   {
      const int semester_id = semester.first;
      auto& semester_data = *semester.second;

      auto& credits = std::get<0>(semester_data);
      auto& gpa = std::get<1>(semester_data);
      list<course*> newCourses{};
      for (auto& c : std::get<2>(semester_data))
      {
         newCourses.push_back(new course(c->name, c->section, c->credits, c->grade));
      }
      auto* newSemester = new tuple<int, float, list<course*>>{ credits, gpa, newCourses };
      pDB->insert({ semester_id, newSemester });
   }
}

void DBclass::operator=(const DBclass& D)
{
   cout << "Copy Assignment" << endl;
   for (auto& semester : *this->pDB)
   {
      for (auto& c : std::get<2>(*semester.second))
      {
         delete c;
      }
      delete semester.second;
   }
   delete this->pDB;

   // same code as copy constructor
   pDB = new map<int, tuple<int, float, list<course*> >*>{};

   for (auto& semester : *D.pDB)
   {
      const int semester_id = semester.first;
      auto& semester_data = *semester.second;

      auto& credits = std::get<0>(semester_data);
      auto& gpa = std::get<1>(semester_data);
      list<course*> newCourses{};
      for (auto& c : std::get<2>(semester_data))
      {
         newCourses.push_back(new course(c->name, c->section, c->credits, c->grade));
      }
      auto* newSemester = new tuple<int, float, list<course*>>{ credits, gpa, newCourses };
      pDB->insert({ semester_id, newSemester });
   }
}

DBclass::DBclass(DBclass&& D)
{
   cout << "Move Constructor" << endl;

   pDB = D.pDB;
   D.pDB = nullptr;
   delete D.pDB;
}

void DBclass::operator=(DBclass&& D)
{
   cout << "Move Assignment" << endl;
   for (auto& semester : *this->pDB)
   {
      for (auto& c : std::get<2>(*semester.second))
      {
         delete c;
      }
      delete semester.second;
   }
   delete this->pDB;

   this->pDB = D.pDB; // TODO: This is the problem.
   D.pDB = nullptr;

}

DBclass::~DBclass()
{
   cout << "Destructor" << endl;
   if (this->pDB == nullptr)
   {
      return;
   }
   for (auto& semester : *this->pDB)
   {
      for (auto& c : std::get<2>(*semester.second))
      {
         delete c;
      }
      delete semester.second;
   }
   delete this->pDB;
}

DBclass::DBclass(const initializer_list<pair<int, initializer_list<course>>>& I) : DBclass()
{//{{"20222", "CIS554", "CS#381", "MAT398", "PSY205"}};
   for (auto& i : I)
   {
      auto semester{ i.first };
      (*pDB)[semester] = new tuple<int, float, list<course*>>{ 0, 0.0f, {}};
      auto& R1{ *(*pDB)[semester] };//R1 is tuple
      auto& R2{ get<2>(R1) };//R2 is list
      int credit{ 0 };
      float gpa{ 0.0f };

      for (auto j : i.second)
      {
         R2.push_back(new course{ j });
         gpa = (gpa * credit + j.credits * j.num_grade()) / (credit + j.credits);
         credit += j.credits;
      }
      get<0>(R1) = credit;
      get<1>(R1) = gpa;
   }

   cout << "Initializer List" << endl;
}
DBclass DBclass::RemoveFirst()
{
   DBclass temp{ *this };

   auto first_entry = temp.pDB->begin();
   for (auto& course : std::get<2>(*first_entry->second))
   {
      delete course;
   }
   delete first_entry->second;
   
   temp.pDB->erase(first_entry);

   cout << "RemoveFirst" << endl;
   return temp;
}

int main()
{

   course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A"),
      C5("CSE661", 1, 3, "B+"),
      C6("PSY205", 11, 3, "A-"), C7("MAT297", 8, 4, "B+"), C8("CIS341", 1, 3, "A-"), C9("CIS453", 1, 3, "A");

   DBclass DB1{{ 20222, { C1, C2, C3 }}, { 20221, { C4, C5, C6 }}, { 20231, { C7, C8, C9 }}};
   cout << "DB1:" << endl << DB1 << endl;

   DBclass DB2{ DB1 };
   cout << "DB2:" << endl << DB2 << endl;

   DBclass DB3{};
   DB3 = DB2;
   cout << "DB3:" << endl << DB3 << endl;

   DB3 = DB2.RemoveFirst();

//   cout << DB3.pDB->size() << endl;
   cout << "DB3:" << endl << DB3 << endl;

   return 0;
}

ostream& operator<<(ostream& str, const DBclass& D)
{
   for (auto& semester : *D.pDB)
   {
      str << "Semester: " << semester.first << endl;
      auto& semester_data = *semester.second;
      auto& credits = std::get<0>(semester_data);
      auto& gpa = std::get<1>(semester_data);

      str << "GPA: " << fixed << setprecision(2) << gpa << endl;
      str << "Credits: " << credits << endl;

      for (auto& course : std::get<2>(semester_data))
      {
         str << *course << " ";
      }
      str << char(0x08) << endl << endl;
   }

   return str;
}
ostream& operator<<(ostream& str, const course& c)
{
   str << "(" << c.name << " " << c.section << " " << c.credits << " " << fixed << setprecision(2) << c.grade << ")";
   return str;
}

