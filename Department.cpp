#include "Department.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Department :: Department ()
{
	name = nullptr;
	totalCourses = 0;
	totalFaculty = 0;
	totalITManagers = 0;
	totalStudents = 0;
	listOfCourses = nullptr;
}

/*Department :: Department (const char *name)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
}*/

Department :: Department (const char *infoFile, int& ignore)
{
	hod = nullptr;
	listOfTeachers = nullptr;
	listOfStudents = nullptr;
	ITManager = nullptr;
	name = new char [30];
	ifstream fin (infoFile);
	for (int i = 0; i < ignore; i++)
	{
		fin.ignore (40, '\n');
	}

	fin.getline (name, 30);
	fin.clear ();
	ignore++;
	//cout << name << endl; // comment this
	
	fin >> totalCourses;
	fin.ignore();
	fin.clear ();
	ignore++;
	//cout << totalCourses << endl; // comment this
	listOfCourses = new Course*[totalCourses];
	for (int i = 0; i < totalCourses; i++)
	{
		listOfCourses[i] = new Course (infoFile, ignore); 
	}

	for (int i = 0; i < totalCourses; i++)
	{
		fin.ignore (40, '\n');
	}

	fin >> totalFaculty;
	fin.ignore();
	fin.clear ();
	ignore++;
	//cout << totalFaculty << endl; // comment this

	for (int i = 0; i < totalFaculty; i++)
	{
		fin.ignore (40, '\n');
		ignore++;
	}

	fin >> totalITManagers;
	fin.ignore();
	fin.clear ();
	ignore++;
	//cout << totalITManagers << endl; //comment this

	for (int i = 0; i < totalITManagers; i++)
	{
		fin.ignore (40, '\n');
		ignore++;
	}

	fin >> totalStudents;
	//cout << totalStudents << endl; //comment this
	fin.ignore();
	fin.clear ();
	ignore++;
	for (int i = 0; i < totalStudents; i++)
	{
		ignore++;
	}

	fin.close ();
}

Department :: Department (const Department& obj)
{
	this -> name = new char [strlen(name) + 1];
	strcpy (this -> name, name);
	this -> listOfCourses = listOfCourses;
	this -> totalCourses = totalCourses;
	this -> totalFaculty = totalFaculty;
	this -> totalStudents = totalStudents;
	this -> totalITManagers = totalITManagers;
}
	
Department :: ~Department ()
{
	for (int i = 0; i < totalCourses; i++)
	{
		delete listOfCourses[i];
	}
	delete [] listOfCourses;
	delete [] listOfTeachers;
	delete [] listOfStudents;
	delete [] name;
	name = nullptr;
}


/*void Department :: makeTeachersList (Teacher **ptr, int size)
{
	listOfTeachers = new Teacher*[size];
}*/

int Department :: getTotalFaculty () const
{
	return totalFaculty;
}
	
int Department :: getTotalStudents () const
{
	return totalStudents;
}
	
int Department :: getTotalITManager () const
{
	return totalITManagers;
}

int Department :: getTotalCourses () const
{
	return totalCourses;
}

char* Department :: getCourseCode (int num) const
{
	return listOfCourses[num] -> getCourseCode ();
}

char* Department :: getDepartmentName () const
{
	return name;
}

void Department :: makeTeachersList (int num)
{
	if (listOfTeachers != nullptr)
	{
		delete [] listOfTeachers;
	}
	listOfTeachers = new Teacher*[num];
}
	
void Department :: makeStudentsList (int num)
{
	if (listOfStudents != nullptr)
	{
		delete [] listOfStudents;
	}
	listOfStudents = new Student*[num];
}
	
void Department :: assignDepartmentTeacher (Teacher *ptr, int num)
{
	listOfTeachers[num] = ptr;
}

void Department :: assignDepartmentHod (HOD *ptr)
{
	hod = ptr;
}
	
void Department :: assignDepartmentStudent (Student *ptr, int num)
{
	listOfStudents[num] = ptr;
}

void Department :: assignDepartmentIT_Manager (IT_Manager *ptr)
{
	ITManager = ptr;
}

Course* Department :: compareCourseCode (const char *sentence) const
{
	const char *temp;
	for (int i = 0; i < totalCourses; i++)
	{
		temp = listOfCourses[i] -> getCourseCode();
		if (strcmp(sentence, temp) == 0)
		{
			return listOfCourses[i];
		}
	}
	return nullptr;
}

Teacher* Department :: compareEmployeeNum (int num) const
{
	int temp;
	for (int i = 0; i < totalFaculty - 1; i++)
	{
		temp = listOfTeachers[i] -> getEmployeeNum();
		if (num == temp)
		{
			return listOfTeachers[i];
		}
	}
	return nullptr;
}

Student* Department :: compareStudentRollNo (int num) const
{
	int temp;
	for (int i = 0; i < totalStudents; i++)
	{
		temp = listOfStudents[i] ->getRollNo ();
		if (num == temp)
		{
			return listOfStudents[i];
		}
	}
	return nullptr;
}

bool Department :: compareTeacherCourses (Course *ptr, Teacher *pointer) const
{
	for (int i = 0; i < totalFaculty - 1; i++)
	{
		if (listOfTeachers[i] == pointer)
		{
			return (listOfTeachers[i] -> compareCourse (ptr));
		}
	}
	return false;
}

void Department :: incrementTotalStudents ()
{
	++totalStudents;
}

void Department :: incrementTotalFaculty ()
{
	++totalFaculty;
}