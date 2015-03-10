//the Person class represents a Person by
//name (string)
//age (int)
//StudentID (int)

//A person must all ways be initiated,
//failure to do so will resut in a compiler Error

//a Person is outputted via stream operators
//and takes the form of an easily parsible triple
//of the form (name,age,studentID)

//a Persons members can ONLY be modified through
//mutator functions

#include <string>
#include <iostream>

class Person{
private:
  std::string name;
  int age;
  int StudentID;


public:

  Person(std::string n, int a, int ID);
  //Accessors
  std::string getName() const;
  int getAge() const;
  int getID() const;


  //mutators
  void setName( std::string );
  void setAge( int );
  void setID( int );

};

std::ostream& operator<<(std::ostream&, Person&);
