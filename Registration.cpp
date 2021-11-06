#include "Registration.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Registration :: Registration ()
{
	rollNo = 0;
	GPA = 0;
	courseCode = nullptr;
}

Registration ::	Registration (char *code, int num, const char *studentFile)
{
	grade[0] = '-';
	grade[1] = '\0';
	marks = 0;
	totalObtainedMarks = 0;
	int temp = strlen(code);
	courseCode = new char [temp + 1];
	strcpy (courseCode, code);
	rollNo = num;
	GPA = 0;
	currentAttendance = 0;
	maxAttendance = 32;
	attendance = new char[maxAttendance];
	currentAssessment = 0;
	listOfAssessments = new Assessment* [12];

	int number, marks[4];
	char line[30], attendance;
	if (studentFile != nullptr)
	{
		ifstream fin (studentFile);
		if (!fin)
		{
			fin.clear();
		}
		else
		{
			while (fin.getline(line, 30))
			{
				if (strcmp (line, code) == 0)
					break;
			}
			fin.clear ();
			fin.ignore (40, '\n'); // gnoring attendance
			fin >> temp;
			fin.ignore();
			for (int i = 0; i < temp; i++)
			{
				fin >> attendance;
				takeAttendance (attendance);
				fin.ignore();
			}
			fin.ignore (40, '\n');
			fin.getline(line, 30);
			fin.clear ();
			setGrade (line);

			fin.ignore (40, '\n'); //ignoring word Assesments
			fin >> temp;
			fin.ignore();
			for (int i = 0; i < temp; i++)
			{
				fin.getline(line, 30);
				fin.clear ();
				for (int j = 0; j < 4; j++)
				{
					fin >> marks[j];
					fin.ignore();
				}
				manageEvaluation (line, marks[0], marks[1], marks[2], marks[3]);
			}
		}

		fin.close ();
	}
}

void Registration :: numberToTextFile (char *& ptr) const
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

Registration :: ~Registration ()
{
	char *ch;
	numberToTextFile (ch);
	ofstream fout (ch, ios :: app);
	fout << "*" << endl;
	fout << courseCode << endl;
	fout << "Attendance" << endl;
	fout << currentAttendance << endl;
	for (int i = 0; i < currentAttendance; i++)
	{
		fout << attendance[i] << endl;
	}
	fout << "grades" << endl;
	fout << grade << endl;
	fout << "Assessments" << endl;
	fout << currentAssessment << endl;
	for (int i = 0; i < currentAssessment; i++)
	{
		fout << listOfAssessments[i] -> getName () << endl;
		fout << listOfAssessments[i] -> getTotalMarks () << ' ' << listOfAssessments[i] -> getObtainedMarks () << ' ' << listOfAssessments[i] -> getWeightage () << ' ' << listOfAssessments[i] -> getObtainedWeightage () << endl;
	}
	fout.close ();


	delete [] ch;
	ch = nullptr;
	delete [] courseCode;
	courseCode = nullptr;
	delete [] attendance;
	attendance = nullptr;
	for (int i = 0; i < currentAssessment; i++)
	{
		delete listOfAssessments[i];
	}
	delete [] listOfAssessments;
	listOfAssessments = nullptr;
}

char* Registration :: getCourseCode () const
{
	return courseCode;
}

Registration* Registration :: checkGrades ()
{
	if (strcmp (grade, "W") == 0)
		return nullptr;
	return this;
}

bool Registration :: compareRegistration (const char *code, int num) const
{
	if (rollNo == num)
	{
		if (!strcmp (code, courseCode))
		{
			return true;
		}
	}
	return false;
}

void Registration :: showGrade () const
{
	cout << rollNo << "               ";
	if (grade == nullptr)
	{
		cout << "No Grade" << endl;
	}
	else
	{
		cout << grade << endl;
	}
}

void Registration :: setGrade (const char *ptr)
{
	try
	{
		if (strlen(ptr) > 2)
			throw 10;
		throw 'e';
	}
	catch (int)
	{
		cout << "String length is greater than grade :(" << endl;
	}
	catch (char)
	{
		strcpy(grade, ptr);
	}
}

void Registration :: growArray ()
{
	maxAttendance += 32;
	char *temp = new char [maxAttendance];
	for (int i = 0; i < currentAttendance; i++)
	{
		temp[i] = attendance[i];
	}
	delete [] attendance;
	attendance = temp;
	temp = nullptr;
}

void Registration :: takeAttendance (char ch)
{
	if (ch == '\0')
	{
		if (currentAttendance == maxAttendance)
		{
			growArray ();
		}
		char temp;
		cout << rollNo << "?" << endl;
		cin >> temp;
		while (!( temp == 'p' || temp == 'P' || temp == 'a' || temp == 'A' || temp == 'l' || temp == 'L'))
		{
			cin.clear ();
			cout << "Please press P or A or L" << endl;
			cin >> temp;
			cin.ignore ();
		}
		attendance[currentAttendance++] = temp;
	}
	else
	{
		attendance[currentAttendance++] = ch;
	}
}
	
void Registration :: showAttendance ()
{
	if (currentAttendance == 0)
	{
		cout << "No attendance has been marked :(" << endl;
	}
	else
	{
		cout << "Roll Number : " << rollNo << endl;
		int date = 16, month = 6, year = 2020;
		for (int i = 0; i < currentAttendance; i++)
		{
			if (date == 31)
			{
				date = 1;
				month++;
			}
			if (date >= 1 && date <= 9)
			{
				cout << "0";
			}
			if (month == 13)
			{
				month = 1;
				year++;
			}
			cout << date <<  "/" << month <<  "/" << year << "               " << attendance[i] << endl;
			date++;
		}
	}
}

int Registration :: getRollNo () const
{
	return rollNo;
}

void Registration :: manageEvaluation (const char *ch, float i, float j, float k, float l)
{
	if (i == 0)
	{
		if (currentAssessment < 12)
		{
			listOfAssessments[currentAssessment++] = new Assessment (marks, totalObtainedMarks);
		}
	}
	else
	{
		listOfAssessments[currentAssessment++] = new Assessment (ch, i, j, k, l, marks, totalObtainedMarks);
	}
}

bool Registration :: compareRollNo (int num) const
{
	if (rollNo == num)
		return true;
	return false;
}

void Registration :: showEvaluations () const
{
	if (currentAssessment == 0)
	{
		cout << "No evaluation has been taken yet for " << rollNo << endl;
	}
	else
	{
		for (int i = 0; i < currentAssessment; i++)
		{
			if (i == 0)
			{
				cout << "Roll Number = " << rollNo << endl;
			}
			listOfAssessments[i] -> showAssesment ();
		}
	}
}

void Registration :: showMarksheet () const
{
	cout << "Roll Number = " << rollNo << "\nGrand Total = " << marks << "\nObtained Marks = " << totalObtainedMarks << endl; 
}

bool Registration :: isWithdrawn () const
{
	if (strcmp(grade, "W"))
		return true;
	return false;
}