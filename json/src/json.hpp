//THIS IS THE HPP FILE FOR THE JSON OBJECT MODEL
//THIS OBJECT MODEL REPRESENTS THE JSON LANGUAGE IN MEMORY
//WHEN USED IN CONJUNCTION WITH A SUITABLE PARSE

//THE CONTRACTS FOR THIS OBJECT MODEL ARE VERY LITE
//QUITE SIMPLY, EVERY THING INHERITS FROM BASE
//AND EACH OBJECT REPRESENTS WHAT ITS NAME WOULD SUGGEST
//WITH THE EXCEPTION OF BASE, WHICH SIMPLY GIVE POLYMORPHISM TO
//THE OBJECTS.

//ONE IMPORTANT CONTRACT OF THE OBJECT MODEL IS THAT IT
//IMPLEMENTS THE VISITOR PATTERN FOR OBTAINING RUN-TIME TYPE INFO
//EACH CLASS OVERRIDES THE void accept(Visitor &) FUNCTION
//INHERITED FROM BASE, EACH FUNCTION SIMPLY CALLS VISITOR'S
// visit(this) FUNCTION WITH this AS THE ARGUMENT.

//THIS HPP ALSO DEFINES AN ABSTRACT VISITOR OBJECT THUS MAKING
//THIS MODULE EXTENSABLE AND REUSEABLE
//IF YOU WOULD LIKE TO EXTEND THE FUNTIONALITY TO MORE THAN JUST
//TYPEINFO YOU CAN SIMPLY INCLUDE THIS FILE IN ANOTHER FILE WHERE
//YOU CAN IMPLEMENT NEW VISITOR-DERIVIED OBJECTS THAT ACHIEVE THE
//FUNCTIONALITY YOU DESIRE

//BASE IS PURE VIRTUAL, AND THUS ATTEMPTS TO CREATE INSTANCES OF BASE
//WILL RESULT IN MANY ERRORS, SO DON'T DO THAT ;)

//AUTHOR : OWEN STRANATHAN


#ifndef JSON_HPP
#define JSON_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>


struct Visitor;
struct Base;
struct Object;
struct Array;
struct String;
struct Number;
struct Bool;
struct Null;

struct Visitor{
	virtual void visit(Object *) {}
	virtual void visit(Array *) {}
	virtual void visit(String*) {}
	virtual void visit(Number *) {}
	virtual void visit(Bool*) {}
	virtual void visit(Null *) {}
};

struct Base
{
	virtual void accept(Visitor&) = 0;
};


struct Null : Base
{
	//ACCEPT
	void accept(Visitor & v) { v.visit(this); }
};

struct Bool : Base
{
	//MEMBER
	bool v;

	//CONSTRUCTOR
	Bool(bool value): v(value){}

	//ACCEPT
	void accept(Visitor & v) { v.visit(this); }
};

struct Number : Base
{
	//MEMBER
	double n;

	//CONSTRUCTOR
	Number(double number) : n(number) {}

	//ACCEPT
	void accept(Visitor & v) { v.visit(this); }
};

struct String : Base
{
	//MEMBER
  std::string s;

	//CONSTRUCTOR
	String(std::string str) : s(str) {}

	//ACCPEPT
	void accept(Visitor & v) { v.visit(this); }
};

struct Array : Base
{
	//MEMBER
  std::vector<Base *> a;

	//ACCEPT
	void accept(Visitor & v) { v.visit(this); }
};

struct Object : Base
{
	//MEMBER
  std::map<String*,Base*> o;

	//CONSTRUCTOR
	Object() {}

	//ACCEPT
	void accept(Visitor& v) { v.visit(this); }
};


//FUNCTION TO GET TYPE
std::string typeof(Base *);

#endif
