#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Person.h"

class Employee : public virtual Person
{
protected:
	int employeeNum;

public:
	Employee ();
	Employee (int, const char*);
	Employee (const Employee&);
	~Employee();
};

#endif