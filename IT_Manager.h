#ifndef IT_MANAGER_H
#define IT_MANAGER_H
#include "Employee.h"

class IT_Manager : public Employee
{
private:


public:
	IT_Manager ();
	IT_Manager (const char*, int&);
	IT_Manager (const IT_Manager&);
	~IT_Manager ();
	int getEmployeeNum () const;
};

#endif