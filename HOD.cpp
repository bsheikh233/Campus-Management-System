#include "HOD.h"
#include <iostream>
#include <fstream>
using namespace std;

HOD :: HOD ()
{

}

HOD :: HOD (const char *infoFile, int& ignore, const char *facultyAccountLogin) : Teacher (infoFile, ignore, facultyAccountLogin)
{
	/*
	username = nullptr;
	password = nullptr;
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
	fin.close ();*/
}

HOD :: HOD (int employeeNum, const char *name): Teacher(employeeNum, name), Person (name)
{

}

HOD :: HOD (const HOD& obj): Teacher(obj), Person (obj)
{

}

HOD:: ~HOD ()
{

}