#include "Assessment.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Assessment :: Assessment ()
{
	name = new char [30];
	cout << "Enter name of assessment (i.e quiz, assignment, sessionals etc)" << endl;
	cin.getline (name, 30);
	cin.clear ();
	cout << "Enter total marks?" << endl;
	cin >> totalMarks;
	cin.ignore ();
	cout << "Enter obtained marks?" << endl;
	cin >> obtainedMarks;
	cin.ignore ();
	cout << "Enter weightage?" << endl;
	cin >> weightage;
	cin.ignore ();
	obtainedWeightage = (obtainedMarks / totalMarks) * weightage;
}


Assessment :: ~Assessment ()
{
	delete [] name;
	name = nullptr;
}
	
	
void Assessment :: showAssesment () const
{
	cout  << name << "\nTotal Marks = " << totalMarks << "\nObtained Marks = " << obtainedMarks << "\nWeightage = " << weightage << "\nObtained Weightage = " << obtainedWeightage << "\n" <<endl;   
}

Assessment :: Assessment (int &numTotal, int &numObtained)
{
	name = new char [30];
	cout << "Enter name of assessment (i.e quiz, assignment, sessionals etc)" << endl;
	cin.getline (name, 30);
	cin.clear ();
	cout << "Enter total marks?" << endl;
	cin >> totalMarks;
	cin.ignore ();
	cout << "Enter obtained marks?" << endl;
	cin >> obtainedMarks;
	cin.ignore ();
	cout << "Enter weightage?" << endl;
	cin >> weightage;
	cin.ignore ();
	obtainedWeightage = (obtainedMarks / totalMarks) * weightage;
	numTotal += weightage;
	numObtained += obtainedWeightage;
}

Assessment :: Assessment (const char *Name, float total, float obtained, float weight, float obtainedWeight, int &numTotal, int &numObtained)
{
	name = new char [30];
	strcpy(name, Name);
	totalMarks = total;
	obtainedMarks = obtained;
	weightage = weight;
	obtainedWeightage = obtainedWeight;
	numTotal += weightage;
	numObtained += obtainedWeightage;
}

char* Assessment :: getName () const
{
	return name;
}
	
float Assessment :: getTotalMarks () const
{
	return totalMarks;
}
	
float Assessment :: getObtainedMarks () const
{
	return obtainedMarks;
}
	
float Assessment :: getWeightage () const
{
	return weightage;
}
	
float Assessment :: getObtainedWeightage () const
{
	return obtainedWeightage;
}