#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include "Department.h"
#include "HOD.h"
#include "Student.h"
class University
{
private:
	char *name;
	int totalNoOfDepartments;
	Department **listOfDepartments;
public:
	University ();
	University (const char*);
	University (const University&);
	~University ();
	int getTotalFaculty (int) const;
	int getTotalStudents (int) const;
	int getTotalITManager (int) const;
	int getTotalDepartments () const;
	int getTotalCourses (int) const;
	char* getCourseCode (int, int) const;
	char* getDepartmentName (int) const;
	void assignDepartmentTeacher (int, Teacher*, int);
	void assignDepartmentIT_Manager (int, IT_Manager*);
	void assignDepartmentHod (int, HOD*);
	void assignDepartmentStudent (int, Student*, int);
	void makeTeachersList (int, int);
	void makeStudentsList (int, int);
	Course* compareCourseCode (const char*, int) const;
	Teacher* compareEmployeeNum (int, int) const;
	Student* compareStudentRollNo (int, int) const;
	bool compareTeacherCourses (Course*, Teacher*, int) const;
	void incrementTotalStudents (int);
	void incrementTotalFaculty (int);
};

#endif