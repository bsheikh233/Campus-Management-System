#include "Teacher.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

Teacher :: Teacher ()
{
	password = nullptr;
}

Teacher :: Teacher (const char *infoFile, int& ignore, const char *facultyAccountLogin)
{
	currentCourse = 0;
	maxNoOfCourses = 0;
	listOFCourses = nullptr;
	password = nullptr;
	int temp;
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
	fin.open (facultyAccountLogin);
	if(!fin)
	{
		fin.clear();
	}
	else
	{
		while (fin >> temp)
		{
			fin.ignore();
			if (temp == employeeNum)
			{
				password = new char [30];
				fin.getline (password, 30);
				//cout << password;
				//system ("pause");
				fin.clear();
				break;
			}
			fin.ignore (40, '\n');
		}
		fin.clear();
	}
	fin.close();
	numberToTextFile ();
}

int Teacher :: getEmployeeNum () const
{
	return employeeNum;
}

Teacher :: Teacher (int employeeNum, const char *name): Employee (employeeNum, name), Person (name)
{
	password = nullptr;
	listOFCourses = nullptr;
	currentCourse = 0;
	maxNoOfCourses = 0;
	numberToTextFile ();
}

char* Teacher :: getFile () const
{
	return file;
}

Teacher :: Teacher (const Teacher& obj): Employee (obj), Person (obj)
{

}

void Teacher :: numberToTextFile ()
{
	int count = 0, temp = employeeNum;
	while (!temp == 0)
	{
		temp /= 10;
		count++;
	}
	temp = employeeNum;
	file = new char[count + 5];
	for (int i = count - 1; i >= 0; i--)
	{
		file[i] = (temp % 10) + 48;
		temp /= 10;
	}
	file[count] = '.';
	file[count + 1] = 't';
	file[count + 2] = 'x';
	file[count + 3] = 't';
	file[count + 4] = '\0';
}

Teacher :: ~Teacher ()
{
	ofstream fout (file);
	fout << maxNoOfCourses << endl;
	fout << currentCourse << endl;
	for (int i = 0; i < currentCourse; i++)
	{
		fout << listOFCourses[i] ->getCourseCode () << endl;
	}
	fout.close ();
	if (password != nullptr)
	{
		delete [] password;
		password = nullptr;
	}
	if (listOFCourses != nullptr)
	{
		delete [] listOFCourses;
		listOFCourses = nullptr;
	}
	delete [] file;
	file = nullptr;
}

int Teacher :: checkEmployeeNum (int num) const
{
	if (num == employeeNum)
	{
		if (password == nullptr)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	return 0;
}

void Teacher :: createAccount (const char *facultyAccountLogin)
{
	password = new char[30];
	ofstream fout (facultyAccountLogin, ios :: app);
	int i = 0;
	char temp;
	cout << "Please create password." << endl;
	while (true)
	{
		temp = _getch();
		if ((int)temp != 8 && (int)temp != 13 && i < 29) //13 for enter key
		{
			password[i] = temp;
			cout << "*";
			i++;
		}
		else if ((int)temp == 13)
		{
			if (i == 0)
			{
				cout << "You cannot leave the password section empty!" << endl;
			}
			else
			{
				password[i] = '\0';
				break;
			}
		}
		else if (temp == '\b' && i >= 1)
		{
			cout << '\b' << " " << '\b';
			i--;
		}
	}
	fout << employeeNum << endl << password << endl;
	fout.close();
}

void Teacher :: deleteAccount (const char *facultyAccountLogin)
{
	if (password == nullptr)
	{
		cout << "Cannot perform this action as account does not exist :(" << endl;
	}
	else
	{
		int temp;
		char ch[40];
		ifstream fin (facultyAccountLogin);
		ofstream fout ("temp.txt");
		while (fin >> temp)
		{
			fin.ignore();
			if (temp == employeeNum)
			{
				fin.ignore (40, '\n');	
			}
			else
			{
				fin.getline (ch, 40);
				fin.clear();
				fout << temp << endl << ch << endl;
			}
		}
		fin.clear();
		fin.close ();
		fout.close();
		remove (facultyAccountLogin);
		rename ("temp.txt", facultyAccountLogin);

	}
}

void Teacher :: setMaxcourses (int num)
{
	maxNoOfCourses = num;
}

void Teacher :: assignCourse (Course *ptr, int temp)
{
	if (temp == 0)
	{
		if (maxNoOfCourses == 0)
		{
			cout << "Enter maximum number of courses that this teacher can teach?" << endl;
			cin >> maxNoOfCourses;
			cin.ignore();
			listOFCourses = new Course* [maxNoOfCourses];
		}
	}
	else if (temp == 1)
	{
		if (maxNoOfCourses != 0)
		{
			listOFCourses = new Course* [maxNoOfCourses];
		}
	}
	if (currentCourse == maxNoOfCourses)
	{
		cout << "This teacher has reached its maximum range of courses :(" << endl;
	}
	else
	{
		listOFCourses[currentCourse++] = ptr;
	}
}

bool Teacher :: compareCourse (Course *ptr) const
{
	for (int i = 0; i < currentCourse; i++)
	{
		if (listOFCourses[i] == ptr)
		{
			return true;
		}
	}
	return false;
}

char* Teacher :: getPassword () const
{
	return password;
}

int Teacher :: compareCourseByIndexes (Course *ptr) const
{
	for (int i = 0; i < currentCourse; i++)
	{
		if (listOFCourses[i] == ptr)
		{
			return i;
		}
	}
	return -1;
}