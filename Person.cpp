#include "Person.h"
#include <iostream>
#include <cstring>
using namespace std;

Person :: Person ()
{
	name = nullptr;
}

Person :: Person (const char *name)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
}

Person :: Person (const Person& obj)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
}

Person :: ~Person ()
{
	if (name != nullptr)
	{
		delete [] name;
		name = nullptr;
	}
}