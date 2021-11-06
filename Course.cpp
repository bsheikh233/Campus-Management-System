#include "Course.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Course :: Course ()
{
	courseCode = nullptr;
	courseName = nullptr;
}

Course :: Course (const char *infoFile, int &ignore)
{
	currentRegistration = 0;
	listOfRegistration = new Registration*[50];
	courseCode = new char [20];
	courseName = new char [30];
	ifstream fin (infoFile);
	for (int i = 0; i < ignore; i++)
	{
		fin.ignore (40, '\n');
	}

	fin.getline (courseCode, 20, ',');
	fin.clear ();
	//cout << courseCode; //comment this
	fin.ignore();
	
	fin.getline (courseName, 30);
	fin.clear ();
	//cout << ", "<< courseName << endl; //comment this
	ignore++;
	fin.close ();
}

int Course :: getCurrentRegistration () const
{
	return currentRegistration;
}


Course :: Course (const Course& obj)
{
	this -> courseName = new char [strlen(courseName) + 1];
	strcpy (this -> courseName, courseName);
	this -> courseCode = new char [strlen(courseCode) + 1];
	strcpy (this -> courseCode, courseCode);
}

Course :: ~Course ()
{
	delete [] courseCode;
	delete [] courseName;
	courseCode = nullptr;
	courseName = nullptr;
	delete [] listOfRegistration;
}

/*Course :: Course (const char *courseCode, const char *courseName)
{
	this -> courseName = new char [strlen(courseName) + 1];
	strcpy (this -> courseName, courseName);
	this -> courseCode = new char [strlen(courseCode) + 1];
	strcpy (this -> courseCode, courseCode);
}*/

char* Course :: getCourseCode () const
{
	return courseCode;
}

void Course :: assignRegistration (Registration *ptr)
{
	listOfRegistration [currentRegistration++] = ptr;
}

bool Course :: operator == (const Course &obj) const
{
	return (courseCode == obj.courseCode && courseName == obj.courseName && currentRegistration == obj.currentRegistration && listOfRegistration == obj.listOfRegistration);
}

bool Course :: compareRegistration (const char *code, int num, int& index) const
{
	for (index = 0; index < currentRegistration; index++)
	{
		if (listOfRegistration[index] -> compareRegistration (code, num))
		{
			return true;
		}
	}
	return false;
}

bool Course :: unassignRegistration (const char *code, int num)
{
	int index = 0;
	if (compareRegistration (code, num, index))
	{
		for (int i = index; i < currentRegistration; i++)
		{
			if (i != currentRegistration - 1)
			{
				listOfRegistration[i] = listOfRegistration[i + 1];
			}
			else
			{
				listOfRegistration[i] = nullptr;
			}
		}
		currentRegistration--;
		return true;
	}
	return false;
}

void Course :: showGrade () const
{
	if (currentRegistration == 0)
	{
		cout << "No registration has been done in this course :(" << endl;
	}
	else
	{
		for (int i = 0; i < currentRegistration; i++)
		{
			listOfRegistration[i] -> showGrade ();
		}
	}
}

bool Course :: compareRegistration (const char *code, int num) const
{
	for (int i = 0; i < currentRegistration; i++)
	{
		if (listOfRegistration[i] -> compareRegistration (code, num))
		{
			return true;
		}
	}
	return false;
}

void Course :: showAttendance () const
{
	for (int i = 0; i < currentRegistration; i++)
	{
		listOfRegistration[i] -> showAttendance ();
	}
}

void Course :: takeAttendance () const
{
	for (int i = 0; i < currentRegistration; i++)
	{
		listOfRegistration[i] -> takeAttendance ();
	}
}

void Course :: assignGrade ()
{
	int rollNo;
	char temp[3];
	for (int i = 0; i < currentRegistration; i++)
	{
		rollNo = listOfRegistration[i] -> getRollNo ();
		cout << rollNo << "?" << endl;
		cin.getline (temp, 3);
		cin.clear ();
		listOfRegistration[i] -> setGrade (temp);
	}
}

void Course :: manageEvaluation ()
{
	if (currentRegistration == 0)
	{
		cout << "No Student has yet been registered in this account" << endl;
	}
	else
	{
		for (int i = 0; i < currentRegistration; i++)
		{
			cout << listOfRegistration[i] -> getRollNo () << "?" << endl;
			listOfRegistration[i] -> manageEvaluation ();
		}
	}
}

void Course :: manageEvaluation (int num)
{
	if (currentRegistration == 0)
	{
		cout << "No Student has yet been registered in this account" << endl;
	}
	else
	{
		int i;
		for (i = 0; i < currentRegistration; i++)
		{
			if (listOfRegistration[i] -> compareRollNo (num))
				break;
		}
		if (i == currentRegistration)
		{
			cout << "No student with this roll number is registered in this course :(" << endl;
		}
		else
		{
			listOfRegistration[i] -> manageEvaluation ();
		}
	}
}

void Course :: showEvaluations () const
{
	cout << courseName << endl;
	if (currentRegistration == 0)
	{
		cout << "No Student has yet been registered in this course" << endl;
	}
	else
	{
		for (int i = 0; i < currentRegistration; i++)
		{
			listOfRegistration[i] -> showEvaluations ();
		}
	}
}

