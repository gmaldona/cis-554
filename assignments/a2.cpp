//HW2
//Due: 11:59PM, Friday September 29.

/*
float f1{3.79652}, f2{3.4213};
cout << fixed<<setprecision(2) << f1 << " " << f2 <<endl;
will print 3.80  3.42
It will do rounding and keep 2 digits after decimal point.

You need to
#include <iomanip>

For GPA calculation:
if you have three courses

3.667 3 credits
4.0  1 credit
3.0  4 credits

GPA = (3.667 * 3 + 4.0 * 1 + 3.0 * 4)/(3+1+4)

*/

#include <iostream>
#include <list>
#include <map>
#include <string>
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

/**
* Semester numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.
Implement the following functions.
When adding a student, if the student is already in DB, then ignore the operation.
TODO: When adding a course, if the course is already in DB (even if it is in
a different semester), then ignore the operation.
All courses in a semester should be sorted according to name (increasing order)

When dropping a course, if the course does not exist, then ignore the operation.
When removing a student, if the student does not exist, then ignore the operation.
All courses in a semester need to be sorted.
When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.
If after drop_course, the list becomes empty, you don't need to remove the list.


*/
//Implement the following functions.
void add_student(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB, int id);
void remove_student(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB, int id);
void add_course(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id,
   course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
void drop_course(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id,
   course c);
void print_student_semester_courses(map<int,
                                        pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id);
void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int id);

//Implement additional functions such that you can do
//cout << DB << endl;
ostream& operator<<(ostream& oss, map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB)
{
   oss << endl << "DB:" << endl;
   for (auto& student : DB)
   {
      const int& student_id = student.first;
      const auto& student_data = student.second;
      const auto& student_cumulative = student_data.first;
      const auto& student_cumulative_credits = student_cumulative->first;
      const auto& student_cumulative_gpa = student_cumulative->second;

      oss << "ID: " << student_id << endl
          << "Overall GPA: " << student_cumulative_gpa << endl
          << "Overall Credits: " << student_cumulative_credits << endl;

      auto& student_semester_map = *student_data.second;
      for (auto& student_semester : student_semester_map)
      {
         auto& student_semester_id = student_semester.first;
         const int& student_semester_credits = get<0>(*student_semester.second);
         const float& student_semester_gpa = get<1>(*student_semester.second);

         oss << "Semester: " << student_semester_id << endl
             << "GPA: " << student_semester_gpa << endl
             << "Credits: " << student_semester_credits << endl;

         const list<course*>& student_semester_courses = get<2>(*student_semester.second);
         for (auto& student_semester_course : student_semester_courses)
         {
            oss << "(" << student_semester_course->name << " "
                << student_semester_course->section << " "
                << student_semester_course->credits << " "
                << student_semester_course->grade << ") ";
         }
         oss << char(0x08) << endl;

      }
   }

   return oss;
}

void print_student_semester_courses(map<int,
                                        pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id)
{
   auto it1{ DB.find(id) };
   if (it1 == DB.end()) return;

   auto& semester_map{ *DB[id].second }; //R1 is map, semester map
   auto it2{ semester_map.find(semester) };
   if (it2 == semester_map.end()) return;
   auto& semester_entry = it2->second;
   int semester_credits{ get<0>(*semester_entry) };
   float semester_gpa{ get<1>(*semester_entry) };
   list<course*> student_courses{ get<2>(*semester_entry) };

   cout << "ID: " << id << endl
        << "Semester: " << semester << endl
        << "GPA: " << fixed << setprecision(2) << semester_gpa << endl
        << "Credits: " << semester_credits << endl;
   for (course* student_course : student_courses)
   {
      cout << "(" << student_course->name << " "
           << student_course->section << " "
           << student_course->credits << " "
           << student_course->grade << ") ";
   }
   cout << char(0x08);

   cout << endl;
}

void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int id)
{
   auto it1{ DB.find(id) };
   if (it1 == DB.end()) return;

   auto& student = it1->second;
   auto& student_cumulative = student.first;

   cout << "ID: " << id << endl
        << "Overall GPA: " << fixed << setprecision(2) << student_cumulative->second << endl
        << "Overall Credits: " << student_cumulative->first << endl;

   auto& student_semesters = student.second;
   for (auto& student_semester_entry : *student_semesters)
   {
      auto& student_semester{ *student_semester_entry.second };
      int semester_credits{ get<0>(student_semester) };
      float semester_gpa{ get<1>(student_semester) };
      list<course*> student_courses{ get<2>(student_semester) };
      cout << "Semester: " << student_semester_entry.first << endl
           << "GPA: " << semester_gpa << endl
           << "Credits: " << semester_credits << endl;
      for (auto& student_course : student_courses)
      {
         cout << "(" << student_course->name << " "
              << student_course->section << " "
              << student_course->credits << " "
              << student_course->grade << ") ";
      }
      cout << char(0x08);

      cout << endl;
   }
}

// inserting courses in ascending order
void add_course(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id,
   course c)
{
   auto it1{ DB.find(id) };
   if (it1 == DB.end()) return;
   auto& semester_map{ *DB[id].second }; //R1 is map, semester map
   auto it2{ semester_map.find(semester) };
   if (it2 == semester_map.end())
   {
      semester_map[semester] = new tuple<int, float, list<course*> >{ 0, 0.0f, {}};
   }
   // find if any semester has the class. IF so SKIP
   // iter over each semester and then iter over each course
   for (auto& student_semester_entry : semester_map)
   {
      auto& student_semester = *student_semester_entry.second;
      list<course*>* student_courses{ &get<2>(student_semester) };
      for (course* course : *student_courses)
      {
         if (*course == c) return;
      }
   }

   it2 = semester_map.find(semester);
   auto& semester_entry{ it2->second };
   list<course*>* student_courses{ &get<2>(*semester_entry) };
   // we need to sort

   course* course_ptr = nullptr;
   for (auto& course : *student_courses)
   {
      if (course_ptr == nullptr)
      {
         course_ptr = course;
      }
      if (c < *course)
      {
         course_ptr = course;
      }
   }
   // c passed by value, creating a pointer to a new course using the same values of c
   // insert before sorting and then list gets sorted.
   student_courses->push_back(new course{ c.name, c.section, c.credits, c.grade });
   // Sorting using a lambda function.
   // Learned lambdas from Java, applying to C++ (not as pretty as Java)
   // used: https://stackoverflow.com/questions/22281962/c11-sorting-list-using-lambda to help with the structure of a lambda in C++
   student_courses->sort([](course*& c1, course*& c2)
   { return c1->name < c2->name; });

   // update semester cumulative

   // for each semester
   float cumulative_gpa = 0.0f;
   float total_quality_points = 0.0f;
   int total_credits = 0;
   for (auto& student_semester : semester_map)
   {
      const int semester_id = student_semester.first;
      auto& semester_n = student_semester.second;
      list<course*> semester_courses{ get<2>(*semester_n) };
      // for each course in each semester
      float semester_gpa = 0.0f;
      float quality_points = 0;
      int semester_credits = 0;
      for (course*& student_course : semester_courses)
      {
         quality_points += (student_course->num_grade() * (float)student_course->credits);
         semester_credits += student_course->credits;

         total_quality_points += (student_course->num_grade() * (float)student_course->credits);
         total_credits += student_course->credits;
      }
      semester_gpa = (quality_points) / (float)semester_credits;

      semester_map[student_semester.first] =
         new tuple<int, float, list<course*> >{ semester_credits, semester_gpa, semester_courses };
   }
   cumulative_gpa = (total_quality_points) / (float)total_credits;
   auto& student_cumulative = DB[id].first;
//   delete student_cumulative;
   DB[id].first = new pair<int, float>{ total_credits, cumulative_gpa };

}

void drop_course(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB,
   int semester,
   int id,
   course c)
{
   auto it1{ DB.find(id) };
   if (it1 == DB.end()) return;

   auto& semester_map = *DB[id].second;
   auto it2{ semester_map.find(semester) };
   if (it2 == semester_map.end()) return;

   auto& student_courses{ get<2>(*it2->second) };
   for (course*& student_course : student_courses)
   {
      if (!(c == *student_course))
      {
         continue;
      }

      student_courses.remove(student_course);
//      delete student_course;
      break;
   }



   // update semester cumulative
   // for each semester
   float cumulative_gpa = 0.0f;
   float total_quality_points = 0.0f;
   int total_credits = 0;
   for (auto& student_semester : semester_map)
   {
      const int semester_id = student_semester.first;
      auto& semester_entry{ student_semester.second };
      list<course*> semester_courses{ get<2>(*semester_entry) };
      // for each course in each semester
      float semester_gpa = 0.0f;
      float quality_points = 0;
      int semester_credits = 0;
      for (course*& student_course : student_courses)
      {
         quality_points += (student_course->num_grade() * (float)student_course->credits);
         semester_credits += student_course->credits;

         total_quality_points += (student_course->num_grade() * (float)student_course->credits);
         total_credits += student_course->credits;
      }
      semester_gpa = (quality_points) / (float)semester_credits;
//      delete student_semester.second;
      semester_map[student_semester.first] =
         new tuple<int, float, list<course*> >{ semester_credits, semester_gpa, student_courses };
   }
   cumulative_gpa = (total_quality_points) / (float)total_credits;
   auto& student_cumulative = DB[id].first;
   delete student_cumulative;
   DB[id].first = new pair<int, float>{ total_credits, cumulative_gpa };

}

void add_student(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB, int id)
{
   auto it1{ DB.find(id) };
   if (it1 != DB.end()) return;
   DB[id] = pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*>{ new pair<int, float>{ 0, 0.0f },
                                                                                    new map<int,
                                                                                            tuple<int,
                                                                                                  float,
                                                                                                  list<course*> >*>{}};

}

void remove_student(map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> >& DB, int id)
{
   auto it{ DB.find(id) };
   if (it == DB.end()) return;

   auto& student_entry = DB[id];
   auto& student_cumulative = student_entry.first;
   auto& semester_map = student_entry.second;
   for (auto& student_semester_entry : *semester_map)
   {
      auto& student_semester = student_semester_entry.second;
      auto& student_courses = get<2>(*student_semester);
      // delete each semester
      for (auto& student_course : student_courses)
      {
//         delete student_course;
      }
      delete student_semester;
   }
   delete student_cumulative;
   delete semester_map;

   DB.erase(id);
}

int main()
{

   map<int, pair<pair<int, float>*, map<int, tuple<int, float, list<course*> >*>*> > DB;
   add_student(DB, 11111);
   course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

   add_course(DB, 20171, 11111, C1);
   add_course(DB, 20171, 11111, C4);
   add_course(DB, 20171, 11111, C3);
   add_course(DB, 20171, 11111, C2);
   print_student_semester_courses(DB, 20171, 11111);

   drop_course(DB, 20171, 11111, C1);

   print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

   course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
   add_course(DB, 20172, 11111, C5);
   add_course(DB, 20172, 11111, C6);
   add_course(DB, 20172, 11111, C7);
   add_course(DB, 20172, 11111, C8);
   add_course(DB, 20172, 11111, C3);
   print_student_all_courses(DB, 11111);//ID GPA

   add_student(DB, 11112);
   add_course(DB, 20171, 11112, C2);
   add_course(DB, 20171, 11112, C5);
   add_course(DB, 20171, 11112, C7);
   add_course(DB, 20171, 11112, C4);
   print_student_semester_courses(DB, 20171, 11112);

   add_course(DB, 20172, 11112, C8);
   add_course(DB, 20172, 11112, C3);
   add_course(DB, 20172, 11112, C5);
   add_course(DB, 20172, 11112, C1);
   print_student_semester_courses(DB, 20172, 11112);

   print_student_all_courses(DB, 11112);

   //Overload operator<< to allow the following cout statements.
   cout << DB << endl;
   remove_student(DB, 11111);
   cout << DB << endl;
   return 0;
}