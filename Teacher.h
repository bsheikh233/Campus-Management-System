#ifndef TEACHER_H
#define TEACHER_H
#include "Employee.h"
#include "Course.h"

class Teacher : public Employee
{
protected:
	char *password;
	int maxNoOfCourses;
	int currentCourse;
	Course **listOFCourses; 
	char *file;

public:
	Teacher ();
	Teacher (const char*, int&, const char*);
	Teacher (int, const char*);
	Teacher (const Teacher&);
	~Teacher ();
	int getEmployeeNum () const;
	char* getPassword () const;
	int checkEmployeeNum (int) const;
	void createAccount (const char*);
	void deleteAccount (const char*);
	void assignCourse (Course*, int = 0);
	bool compareCourse (Course*) const;
	int compareCourseByIndexes (Course*) const;
	void numberToTextFile ();
	char* getFile () const;
	void setMaxcourses (int);
};

#endif