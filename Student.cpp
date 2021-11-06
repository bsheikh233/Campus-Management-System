#include "Student.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

Student :: Student()
{
	rollNo = 0;
}

Student :: Student(int rollNo, const char *name) : Person (name)
{
	this -> rollNo = rollNo;
	password = nullptr;
	currentRegistration = 0;
	listOfRegistration = new Registration*[5];
	numberToTextFile (studentFile);
}

Student :: Student (const Student& obj) : Person (obj)
{
	this -> rollNo = rollNo;	
}

Student :: ~Student()
{
	ofstream fout (studentFile);
	fout << currentRegistration << endl;
	fout.close ();
	if (password != nullptr)
	{
		delete [] password;
		password = nullptr;
	}
	registrationHeapDeletion ();
	delete [] studentFile;
	studentFile = nullptr;
}

Student :: Student (const char *infoFile, int& ignore, const char *studentAccountLogin)
{
	studentFile = nullptr;
	int temp;
	password = nullptr;
	currentRegistration = 0;
	listOfRegistration = new Registration*[5];
	name = new char [30];
	ifstream fin (infoFile);
	for (int i = 0; i < ignore; i++)
	{
		fin.ignore (40, '\n');
	}

	fin >> rollNo;
	fin.clear ();
	fin.ignore (2);
	//cout << rollNo; // comment this
	
	fin.getline (name, 30);
	fin.clear();
	//cout << ", "<< name << endl; // comment this
	
	ignore++;
	fin.close ();
	fin.open (studentAccountLogin);
	if(!fin)
	{
		fin.clear();
	}
	else
	{
		while (fin >> temp)
		{
			fin.ignore();
			if (temp == rollNo)
			{
				password = new char [30];
				fin.getline (password, 30);
				fin.clear();
				break;
			}
			fin.ignore (40, '\n');
		}
		fin.clear();
	}
	fin.close();
	numberToTextFile (studentFile);
	

	int number;
	char line[30];
	Registration *tempRegistration;
	fin.open (studentFile);
	if (!fin)
	{
		fin.clear();
	}
	else
	{
		fin >> number;
		fin.ignore ();
		for (int i = 0; i < number; i++)
		{
			while (fin.getline (line, 30))
			{
				if (strcmp(line, "*") == 0)
					break;
			}
			fin.clear();
			fin.getline (line, 30);
			fin.clear();
			tempRegistration = new Registration (line, rollNo, studentFile);
			assignRegistration (tempRegistration);
		}
		tempRegistration = nullptr;
		fin.close ();
	}
}

Registration* Student :: checkGrades (int num)
{
	return (listOfRegistration[num] -> checkGrades ());
}

void Student :: numberToTextFile (char *&ptr) const
{

	int count = 0, temp = rollNo;
	while (!temp == 0)
	{
		temp /= 10;
		count++;
	}
	temp = rollNo;
	ptr = new char[count + 5];
	for (int i = count - 1; i >= 0; i--)
	{
		ptr[i] = (temp % 10) + 48;
		temp /= 10;
	}
	ptr[count] = '.';
	ptr[count + 1] = 't';
	ptr[count + 2] = 'x';
	ptr[count + 3] = 't';
	ptr[count + 4] = '\0';
}

int Student :: checkRollNo (int num) const
{
	if (num == rollNo)
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

int Student :: getRollNo() const
{
	return rollNo;
}

void Student :: createAccount (const char *studentAccountLogin)
{
	password = new char[30];
	ofstream fout (studentAccountLogin, ios :: app);
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
	fout << rollNo << endl << password << endl;
	fout.close();
}

void Student :: deleteAccount (const char *studentAccountLogin)
{
	if (password == nullptr)
	{
		cout << "Cannot perform this action as account does not exist :(" << endl;
	}
	else
	{
		int temp;
		char ch[40];
		ifstream fin (studentAccountLogin);
		ofstream fout ("temp.txt");
		while (fin >> temp)
		{
			fin.ignore();
			if (temp == rollNo)
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
		remove (studentAccountLogin);
		rename ("temp.txt", studentAccountLogin);

	}
}

int Student :: getCurrentRegistration () const
{
	return currentRegistration;
}

bool Student :: compareRegistration (const char *code, int num) const
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

void Student :: assignRegistration (Registration *ptr)
{
	listOfRegistration [currentRegistration++] = ptr;
}

void Student :: registrationHeapDeletion ()
{
	for (int i = 0; i < currentRegistration; i++)
	{
		delete listOfRegistration[i];
	}
	delete [] listOfRegistration;
	listOfRegistration = nullptr;
}


bool Student :: compareRegistration (const char *code, int num, int& index) const
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

bool Student :: deleteRegistration (const char *code, int num)
{
	int index = 0;
	if (compareRegistration (code, num, index))
	{
		delete listOfRegistration[index];
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


char* Student :: getPassword () const
{
	return password;
}

bool Student :: withDrawCourse (const char *code, int num)
{
	int index = 0;
	if (compareRegistration (code, num, index))
	{
		listOfRegistration[index] -> setGrade("W");
		return true;
	}
	return false;
}

void Student:: showAttendance (int i) const
{
		listOfRegistration[i] -> showAttendance ();
}

void Student :: showMarksheet (int num) const
{
	listOfRegistration [num] -> showEvaluations ();
}