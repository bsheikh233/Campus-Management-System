#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "Course.h"
#include "HOD.h"
#include "Student.h"
#include "IT_Manager.h"
#include <cstring>
class Department
{
private:
	char *name;
	int totalCourses;
	int totalFaculty;
	int totalITManagers;
	int totalStudents;
	Course **listOfCourses;
	Teacher **listOfTeachers;
	HOD *hod;
	Student **listOfStudents;
	IT_Manager *ITManager;
public:
	Department ();
	void makeTeachersList (int);
	void makeStudentsList (int);
	void assignDepartmentTeacher (Teacher*, int);
	void assignDepartmentHod (HOD*);
	void assignDepartmentIT_Manager (IT_Manager*);
	void assignDepartmentStudent (Student*, int);
	Department (const char*, int&);
	Department (const Department&);
	~Department ();
	int getTotalFaculty () const;
	int getTotalStudents () const;
	int getTotalITManager () const;
	int getTotalCourses () const;
	char* getCourseCode (int) const;
	char* getDepartmentName () const;
	Course* compareCourseCode (const char*) const;
	Teacher* compareEmployeeNum (int) const;
	Student* compareStudentRollNo (int) const;
	bool compareTeacherCourses (Course*, Teacher*) const;
	void incrementTotalStudents ();
	void incrementTotalFaculty ();
};
#endif