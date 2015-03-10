#include <string>
#include <iostream>
#include "Person.hpp"

using namespace std;


int main(){
  //Creating frank(an object of type Person)
  Person frank("frank", 42, 5555556);

  //Using contracts to output frank's value
  cout << frank<< endl;

  //Changing frank
  frank.setName("Frank");
  frank.setAge(43);
  frank.setID(0000002);

  //Frank got older and a new ID
  cout << frank << endl;
  return 0;
}
