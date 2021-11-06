#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "Assessment.h"

class Registration
{
private:
	int rollNo;
	char *courseCode;
	float GPA;
	char grade[3];
	int currentAttendance;
	int maxAttendance;
	char *attendance;
	Assessment **listOfAssessments;
	int currentAssessment;
	int marks;
	int totalObtainedMarks;
	char *studentFile;
public:
	Registration ();
	Registration (char*, int, const char* = nullptr);
	~Registration ();
	bool compareRegistration (const char*, int) const;
	void showGrade () const;
	void setGrade (const char*);
	void growArray ();
	void takeAttendance (char = '\0');
	void showAttendance ();
	int getRollNo () const;
	void manageEvaluation (const char* = nullptr, float = 0, float = 0, float = 0, float = 0);
	bool compareRollNo (int) const;
	void showEvaluations () const;
	void showMarksheet () const;
	bool isWithdrawn () const;
	void numberToTextFile (char*&) const;
	Registration* checkGrades ();
	char* getCourseCode () const;
};

#endif