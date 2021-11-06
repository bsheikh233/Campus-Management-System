#include "University.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

University :: University ()
{
	name = nullptr;
	totalNoOfDepartments = 0;
	listOfDepartments = nullptr;
}
	
University :: University (const char *infoFile)
{
	int ignore = 2;
	name = new char [30];
	ifstream fin (infoFile);
	fin.getline (name, 30);
	fin.clear ();
	//cout << name << endl; // comment this

	fin >> totalNoOfDepartments;
	fin.ignore();
	fin.clear();
	//cout << totalNoOfDepartments << endl; // comment this
	
	listOfDepartments = new Department*[totalNoOfDepartments];
	for (int i = 0; i < totalNoOfDepartments; i++)
	{
		listOfDepartments[i] = new Department(infoFile, ignore);
	}
	fin.close ();
}

University :: University (const University& obj)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
	this -> totalNoOfDepartments = totalNoOfDepartments;
	this -> listOfDepartments = listOfDepartments; 
}

University :: ~University ()
{
	for (int i = 0; i < totalNoOfDepartments; i++)
	{
		delete listOfDepartments[i];
	}
	delete [] listOfDepartments;
	listOfDepartments = nullptr;
	
	delete [] name;
	name = nullptr;
}

/*University :: University (const char *name)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
}*/

int University :: getTotalFaculty (int num) const
{
	return (listOfDepartments[num] -> getTotalFaculty());
}

int University :: getTotalStudents (int num) const
{
	return (listOfDepartments[num] -> getTotalStudents());
}

int University :: getTotalITManager (int num) const
{
	return (listOfDepartments[num] -> getTotalITManager());
}

int University :: getTotalDepartments () const
{
	return totalNoOfDepartments;
}

int University :: getTotalCourses (int num) const
{
	return listOfDepartments[num] -> getTotalCourses ();
}

char* University :: getCourseCode (int departmentNum, int courseNum) const
{
	return listOfDepartments[departmentNum] -> getCourseCode (courseNum);
}

char* University :: getDepartmentName (int num) const
{
	return listOfDepartments[num] ->getDepartmentName ();
}

void University :: assignDepartmentTeacher (int departmentNum, Teacher *ptr, int num)
{
	listOfDepartments[departmentNum] -> assignDepartmentTeacher (ptr, num);
}
	
void University :: assignDepartmentHod (int departmentNum, HOD *ptr)
{
	listOfDepartments[departmentNum] -> assignDepartmentHod (ptr);
}

void University :: assignDepartmentStudent (int departmentNum, Student *ptr, int num)
{
	listOfDepartments[departmentNum] -> assignDepartmentStudent (ptr, num);
}

void University :: makeTeachersList (int departmentNum, int totalFaculty)
{
	listOfDepartments[departmentNum] -> makeTeachersList (totalFaculty - 1);
}
	
void University ::  makeStudentsList (int departmentNum, int totalStudents)
{
	listOfDepartments[departmentNum] -> makeStudentsList (totalStudents);
}

void University :: assignDepartmentIT_Manager (int departmentNum, IT_Manager *ptr)
{
	listOfDepartments[departmentNum] -> assignDepartmentIT_Manager (ptr);
}

Course* University :: compareCourseCode (const char *sentence, int departmentNum) const
{
	return (listOfDepartments[departmentNum] ->compareCourseCode (sentence)	);
}

Teacher* University :: compareEmployeeNum (int num, int departmentNum) const
{
	return (listOfDepartments[departmentNum] -> compareEmployeeNum(num));
}

Student* University :: compareStudentRollNo (int num, int departmentNum) const
{
	return (listOfDepartments[departmentNum] -> compareStudentRollNo(num)); 
}

bool University :: compareTeacherCourses (Course *ptr, Teacher *pointer, int departmentNum) const
{
	return (listOfDepartments[departmentNum] ->compareTeacherCourses (ptr, pointer));
}

void University :: incrementTotalStudents (int departmentNum)
{
	listOfDepartments[departmentNum] -> incrementTotalStudents ();
}

void University :: incrementTotalFaculty (int departmentNum)
{
	listOfDepartments[departmentNum] -> incrementTotalFaculty ();
}