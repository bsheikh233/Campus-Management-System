#include "IT_Manager.h"
#include <iostream>
#include <fstream>
using namespace std;

IT_Manager :: IT_Manager ()
{

}

/*IT_Manager :: IT_Manager (int employeeNum, const char* name): Employee (employeeNum, name), Person (name)
{

}*/

IT_Manager :: IT_Manager (const IT_Manager& obj) : Employee (obj), Person (obj)
{

}

IT_Manager :: ~IT_Manager ()
{

}

IT_Manager :: IT_Manager (const char *infoFile, int &ignore)
{
	name = new char [30];
	ifstream fin (infoFile);
	for (int i = 0; i < ignore; i++)
	{
		fin.ignore (40, '\n');
	}

	fin >> employeeNum;
	fin.clear ();
	fin.ignore (2);
	//cout << employeeNum; // comment this
	
	fin.getline (name, 30);
	fin.clear();
	//cout << ", "<< name << endl; // comment this
	
	ignore++;
	fin.close ();
}

int IT_Manager :: getEmployeeNum () const
{
	return employeeNum;
}