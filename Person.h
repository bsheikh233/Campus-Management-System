#ifndef PERSON_H
#define PERSON_H

class Person
{
protected:
	char *name;

public:
	Person ();
	Person (const char*);
	Person (const Person&);
	~Person ();
};

#endif