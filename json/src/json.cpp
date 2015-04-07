//THIS IS THE ADJOINING CPP FILE FOR JSON.HPP

//THIS FILE ONLY DEFINES A VISISTOR DERIVATIVE FOR TYPEINFO
//AND DEFINES A TYPEOF FUNCTION TO GET THE DYNAMIC TYPE OF
//A BASE POINTER
#include <string>
#include "json.hpp"


using namespace std;

struct Type_visitor : Visitor
{
  string type;
  void visit(Object *) { type =  "Object"; }
  void visit(Array *) { type =  "Array"; }
  void visit(String*) { type =  "String"; }
  void visit(Number *) { type =  "Number"; }
  void visit(Bool*) { type =  "Bool"; }
  void visit(Null *) { type =  "Null"; }
};

string typeof( Base * base)
{
  Type_visitor vis;
  base->accept(vis);
  return vis.type;
}
