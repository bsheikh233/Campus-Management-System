#ifndef COURSE_H
#define COURSE_H
#include "Registration.h"

class Course
{
private:
	char *courseName;
	char *courseCode;
	Registration **listOfRegistration;
	int currentRegistration;

public:
	Course ();
	Course (const char*, int&);
	Course (const Course&);
	~Course ();
	char* getCourseCode () const;
	int getCurrentRegistration () const;
	void assignRegistration (Registration*);
	bool operator == (const Course&) const;
	bool compareRegistration (const char*, int) const;
	bool compareRegistration (const char*, int, int&) const;
	bool unassignRegistration (const char*, int);
	void showGrade () const;
	void showAttendance () const;
	void takeAttendance () const;
	void assignGrade ();
	void manageEvaluation (int);
	void showEvaluations () const;
	void manageEvaluation ();
};


#endif