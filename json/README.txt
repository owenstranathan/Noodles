This is the README accompanying the files json.hpp json.cpp and
parser.cpp

json.hpp defines the json object model
json.cpp extends the visitor pattern therein to give runtime type info

parser.cpp defines a parser for read and interpreting raw json text via curl

The program is to be used for building Abstract
Syntax Trees from raw json text.

to compile the program run cmake on the CMakeLists.txt file then run make.

once compiled you will see an executable file called json

run this program in the following manner

	curl <jsonTextUrl> | ./json

EX:

	curl http://www.reddit.com/r/climbing.json | ./json

The program will then execute and create an in memory object model of
the json document.

And print information on:

	Total Nodes

	Total Objects

	Total Arrays

	Total Strings

	Total Numbers

	Total Bools

	Total Nulls

	Maximum nesting depth

TO COMPILE:

	Using terminal, navigate to the director containing the file json,
	once in the json directory enter json/build and run cmake on
	json/build/CMakeLists.txt

	ex.
			cmake json/build/CMakeLists.txt

	this will create a Makefile that will look for the files in json/src/
	so don't move the files in that directory

	run make

	ex.
			make

	that will make build an executable called json,
	use the commands detailed above to use the program


All source code can be found on my public github repository "noodles"

link: https://github.com/owenstranathan/noodles/json

if you have questions email ods7@zips.uakron.edu

of ask Professor Google ;)
