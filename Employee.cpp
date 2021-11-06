#include "Employee.h"
#include <iostream>
using namespace std;

Employee :: Employee ()
{
	employeeNum = 0;
}

Employee :: Employee (int employeeNum, const char *name) : Person (name)
{
	this -> employeeNum = employeeNum;
}

Employee :: Employee (const Employee& obj) : Person (obj)
{
	this -> employeeNum = employeeNum;
}
Employee :: ~Employee ()
{

}