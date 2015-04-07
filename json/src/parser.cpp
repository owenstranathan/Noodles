//This is a JSON document parser that uses the JSON Object model(defined in
//json.hpp and json.cpp) to create an in memory representation of a JSON
//document. The parser also determines the number of each kind of json object
//created, and determines the maximum nesting depth the json document.
//For lack of a better option, the program will simply output data on:
//TOTAL NUMBER OF NODE
//TOTAL NUMBER OF EACH TYPE OF NODE (OBJECT, ARRAY, STRING, NUMBER, BOOL, NULL)
//MAXIMUM NESTING DEPTH


//AUTHOR : OWEN STRANATHAN


//Created on: 03/31/15
//LAST EDITED ON: 04/07/15

#include <iostream>
#include <string>
#include <stdexcept>
#include "json.hpp"

using namespace std;

Base * parse(std::string, int&);
Object * parseObject(std::string, int &);
Array* parseArray(std::string, int &);
String* parseString(std::string, int &);
Number* parseNumber(std::string, int &);
Bool* parseBool(std::string, int &);
Null * parseNull(std::string, int&);
void parseWhiteSpace(std::string, int &);
void parseColon(std::string, int&);
bool parseComma(std::string, int&);
void parsePeriod(std::string, int&);
void countTypes(vector<Base *>);


vector<Base *> nodeVector;
int nestingdepth;

int main()
{
	//We start by loading the document into memory, via cin
	//the CLI process of using this program is:
	// curl $URL | json
	//where json is the name of the compiled executable of this parser
	string jsonDoc;
	string line;
	//A while loop is needed otherwise the cin buffer overflows and the program
	//will crash
	while(getline(cin, line)){ jsonDoc.append(line); }

  try
  {
		int i = 0;
		parse(jsonDoc, i);
		cout << "total nodes:"<< nodeVector.size() << endl;
		cout << "nesting depth:" << nestingdepth << endl;
		countTypes(nodeVector);
  }
  catch(string error)
  {
		cout << error << endl;
		return -1;
  }
	return 0;
}

void countTypes(vector<Base *> vec)
{
	int objects = 0,
			arrays = 0,
			strings = 0,
			numbers = 0,
			bools = 0,
			nulls = 0;

	for(auto a: vec)
	{
		string type = typeof(a);

		if(type == "Object")
		{
			++objects;
		}
		else if(type == "Array")
		{
			++arrays;
		}
		else if(type == "String")
		{
			++strings;
		}
		else if(type == "Number")
		{
			++numbers;
		}
		else if(type == "Bool")
		{
			++bools;
		}
		else if(type == "Null")
		{
			++nulls;
		}
	}
	cout << "there are " << objects << " objects" << endl;
	cout << "there are " << arrays << " arrays" << endl;
	cout << "there are " << strings << " strings" << endl;
	cout << "there are " << numbers << " numbers" << endl;
	cout << "there are " << bools << " bools" << endl;
	cout << "there are " << nulls << " nulls" << endl;
}

Base* parse(string document, int &i)
{
		switch(document[i])
		{
			//IGNORE WHITESPACE
			parseWhiteSpace(document, i);
			//PARSE OBJECT
			case '{':
				//DEPTH IS ONLY INCREASED WHEN ENTERING AND ARRAY OR OBJECT
				++nestingdepth;
				++i;
				return parseObject(document, i);
				break;
			//PARSE ARRAY
      case '[':
				++nestingdepth;
				++i;
				return parseArray(document, i);
				break;
			//PARSE STRING
      case '"':
				return parseString(document, i);
				break;
			//PARSE NUMBER
			case '-':
				return parseNumber(document, i);
				break;
			//PARSE BOOL
			case 't':
				return parseBool(document, i);
				break;
			//PARSE BOOL
			case 'f':
				return parseBool(document, i);
				break;
			//PARSE NULL
			case 'n':
				return parseNull(document, i);
			default:
				//PARSE NUMBER
				if(isdigit(document[i]))
				{
					return parseNumber(document, i);
				}
				else
				{
					string charNum = to_string(i);
					throw ("Expected expression char # "
					+ charNum + " culprit: " + document[i]);
				}
				break;
		}
		return NULL;
}

//PARSE AN OBJECT
Object* parseObject(string document,int &i)
{
	Object* object = new Object();
	while(true)
	{
		Base * value;
		String * name;

		//IGNORE WHITESPACE
		parseWhiteSpace(document, i);
		//CATCH AN EMPTY OBJECT
		if(document[i] == '}')
		{
			++i;
			nodeVector.push_back(object);
			return object;
		}
		//PARSE A STRING
		name = parseString(document, i);
		//IGNORE WHITESPACE
		parseWhiteSpace(document, i);
		//PARSE A COLON
		parseColon(document, i);
		//IGNORE WHITESPACE
		parseWhiteSpace(document, i);
		//PARSE ANYTHING
		value = parse(document, i);

		//ADD PAIR TO OBJECT
		object->o.insert( pair<String*, Base*>(name, value) );

		//IGNORE WHITESPACE
		parseWhiteSpace(document, i);

		//PARSE EITHER A COMMA
		if(parseComma(document, i))
		{
			continue;
		}
		//OR END OF OBJECT
		else if(document[i] == '}')
		{
			++i;
			break;
		}
	}
	nodeVector.push_back(object);
	return object;
}

//PARSE AND ARRAY
Array * parseArray(string document, int &i)
{
	Array * array = new Array();

	while(true)
	{
		Base * value = nullptr;

		//IGNORE WHITESPACE
		parseWhiteSpace(document,i);

		if(document[i] == ']')
		{
			++i;
			nodeVector.push_back( array );
			return array;
		}

		//PARSE ANYTHING
		value = parse(document, i);

		//IGNORE WHITESPACE AGAIN
		parseWhiteSpace(document, i);

		//PUSH THE VALUE ONTO THE ARRAY
		array->a.push_back(value);

		if(parseComma(document, i))
		{
			continue;
		}
		else if (document[i] == ']')
		{
			++i;
			break;
		}
		else
		{
			throw ("Expected ',' or ']' before expression or end of document");
		}
	}
	nodeVector.push_back(array);
	return array;
}

//PARSE A STRING
String * parseString(string document, int &i)
{
	//IF YOU FIND THE START OF A STRING
	if(document[i] == '"')
	{

		string val = "";

		//SKIP THE '"'
		++i;

		//LOOP THRU UNTILL YOU FIND THE END OF THE STRING
		while(document[i] != '"')
		{
			//IF YOU REACH THE END OF THE DOCUMENT BEFORE THE END OF THE STRING
			if(i == document.length())
			{
				//THROW AND EXCEPTION
				throw "expected \"  before end of document";
			}
			//IF YOU HAVE AN ESCAPE CHARACTER IGNORE '"'
			else if(document[i] == '\\')
			{
				//PUT CHARACTER IN THE STRING
				val += document[i];
				//INCREMENT i
				++i;
				//PUT NEXT CHARACTER IN THE STRING REGARDLESS OF WHAT IT IS
				val += document[i];
				//INCREMENT i
				++i;
			}
			else
			{
				//OTHERWISE PUT THE CHARACTER IN THE STRING
				val += document[i];
				//INCREMENT i
				++i;
			}
			//DO THE LOOP TILL YOU FIND THE END OF THE STRING
		}
		//SKIP OVER THE LAST '"'
		++i;
		//PROBLEMS CAUSE A THROW
		//SO GETTING HERE YOU SHOULD BE CORRECT
		//MAKE THE STRING'S VALUE = FOUND STRING
 		String * str = new String(val);
		//KEEP TRACK OF THE NODE COUNT
		nodeVector.push_back(str);
		//RETURN STRING POINTER
		return str;
	}
	else
	{
		throw "Expected string expression";
	}
}

//PARSE A NUMBER
Number * parseNumber(string document, int &i)
{
	string number;
	Number * num;
	number += document[i];
	++i;
	while(true)
	{
		if(isdigit(document[i]))
		{
			number += document[i];
		}
		else if(document[i] == '.')
		{
			number += document[i];
		}
		else if(document[i] == 'e' || document[i] == 'E')
		{
			number += document[i];
		}
		else if(document[i] == '+' || document[i] == '-')
		{
			number += document[i];
		}
		else
		{
			break;
		}
		++i;
	}
	num =  new Number(atof(number.c_str()));
	nodeVector.push_back(num);
	return num;
}

Bool * parseBool(string document, int &i)
{
	bool boolean;
	Bool * value;
	if(document[i] == 'f')
	{
		++i;
		if(document[i] == 'a')
		{
			++i;
			if(document[i] == 'l')
			{
				++i;
				if(document[i] == 's')
				{
					++i;
					if(document[i] == 'e')
					{
						++i;
						boolean = false;
					}
				}
			}
		}
	}
	else if(document[i] == 't')
	{
		++i;
		if(document[i] == 'r')
		{
			++i;
			if(document[i] == 'u')
			{
				++i;
				if(document[i] == 'e')
				{
					++i;
					boolean = true;
				}
			}
		}
	}
	else
	{
		throw ("Expected boolean expression at char # " + to_string(i));
	}
	value =  new Bool(false);
	nodeVector.push_back(value);
	return value;
}

Null * parseNull(string document, int &i)
{
	Null * null = NULL;
	if(document[i] == 'n')
	{
		++i;
		if(document[i] == 'u')
		{
			++i;
			if(document[i] == 'l')
			{
				++i;
				if(document[i] == 'l')
				{
					++i;
					null = new Null();
				}
			}
		}
	}
	else
	{
		throw ("Expected null expression at char * " + to_string(i));
	}
	nodeVector.push_back(null);
	return null;
}

void parseWhiteSpace(string document, int &i)
{
	//IGNORE WHITESPACE
	while(document[i] == ' ' || document[i] == '	')
	{
		++i;
	}
}

void parseColon(string document, int &i)
{
	if(document[i] == ':')
	{
		++i;
	}
	else
	{
		throw "Expected ':' before expression";
	}
}

bool parseComma(string document, int &i)
{
	if(document[i] == ',')
	{
		++i;
		return true;
	}
	else
	{
		return false;
	}
}
