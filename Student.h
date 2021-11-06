#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
#include "Registration.h"
#include "Course.h"
class Student : public virtual Person
{
private:
	int rollNo;
	char *password;
	Registration **listOfRegistration;
	int currentRegistration;
	char *studentFile;

public:
	Student ();
	Student (const Student&);
	Student (int, const char*);
	Student (const char*, int&, const char*);
	~Student ();
	int getRollNo() const;
	int checkRollNo (int) const;
	void createAccount (const char*);
	void deleteAccount (const char*);
	int getCurrentRegistration () const;
	bool compareRegistration (const char*, int) const;
	void assignRegistration (Registration*);
	void registrationHeapDeletion ();
	bool compareRegistration (const char*, int, int&) const;
	bool deleteRegistration (const char*, int);
	char* getPassword () const;
	bool withDrawCourse (const char*, int);
	void showAttendance (int) const;
	void showMarksheet (int) const;
	void numberToTextFile (char*&) const;
	Registration* checkGrades (int);
};

#endif