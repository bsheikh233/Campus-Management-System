#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include <memory>
#include "Student.h"
#include "Teacher.h"
#include "TA.h"
#include "Course.h"

class Department {
private:
    std::string name;
    std::vector<std::shared_ptr<Person>> people; // Can hold Student, Teacher, TA
    std::vector<Course> courses;

public:
    Department(std::string name = "") : name(name) {}

    std::string getName() const { return name; }
    
    bool addPerson(std::shared_ptr<Person> person);
    bool removePerson(int id);
    
    bool addCourse(const Course& course);
    bool removeCourse(const std::string& code);

    std::shared_ptr<Person> findPerson(int id);
    Course* findCourse(const std::string& code);

    const std::vector<std::shared_ptr<Person>>& getPeople() const { return people; }
    const std::vector<Course>& getCourses() const { return courses; }

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
};

#endif
