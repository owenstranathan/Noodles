#include <iostream>
#include <string>
#include "Person.hpp"

//MEMBER FUNCTIONS
//Constructor
Person::Person(std::string n, int a, int ID):
 name(n), age(a), StudentID(ID)
{}

//Accessors
std::string  Person::getName() const { return name; }
int Person::getAge() const { return age; }
int Person::getID() const { return StudentID;}


//Mutators
void Person::setName( std::string n)
{ name = n;}
void Person::setAge( int a )
{ age = a; }
void Person::setID( int ID )
{ StudentID = ID; }

//output
std::ostream& operator<<(std::ostream& os, Person& person )
{
  os << "("
    << person.getName()
    << ", "
    << person.getAge()
    << ", "
    << person.getID()
    <<")";
  return os;
}
