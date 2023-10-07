#include <iostream>

class String 
{
   public:
   String() = default;
   String(const char* string)
   {
      m_Size = strlen(string);
      m_Data = new char[m_Size];
      memcpy(m_Data, string, m_Size);
   }
   ~String()
   {
      delete m_Data;
   }
   String(const String& other)
   {
      m_Size = other.m_Size;
      m_Data = new char[m_Size];
      memcpy(m_Data, other.m_Data, m_Size);
   }

   String(String&& other) {
      m_Size = other.m_Size;
      m_Data = other.m_Data; // pointing to already existing memory
      
      other.m_Size = 0;
      other.m_Data = nullptr; // when other.m_Data is delete then it deletes
                              // nullptr instead of the memory location
   }

   String& operator=(String&& other)
   {  
      if (this == &other) {
         return *this;
      }
      
      delete[] m_Data; // moving another object into an already created object

      m_Size = other.m_Size;
      m_Data = other.m_Data; 
      
      other.m_Size = 0;
      other.m_Data = nullptr;
   }

private:
   char* m_Data;
   uint32_t m_Size;
};

class Entity
{
public: 
   Entity(const String& name) : m_Name(name)
   {

   }

   Entity(String&& name) : m_Name(std::move(name))
   {

   }
private:
   String m_Name;
};


void SetValue(int& value)
{

}

void PrintName(const std::string& name) // both L and R values
{
   std::cout << name << std::endl;
   // L values can be thought of a location
}

void PrintName(std::string&& name) // R values only
{
   std::cout << name << std::endl;
   // R values can be thought of temporary values
   // usefully for optimizations because you know R values might
   // not be around for to long
}

int main() {
   int i = 10;
   const int& 
   SetValue(i);
   // SetValue(10); // initial value of reference to non-const must be an lvalue

   // works for both
   std::string firstname = "greg";
   std::string lastname = "maldonado";
   PrintName(firstname + lastname);
   PrintName(firstname);

   // move semantics: https://www.youtube.com/watch?v=ehMg6zvXuMY

   Entity entity(String("greg"));
   return 0;
}