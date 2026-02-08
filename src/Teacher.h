#ifndef TEACHER_H
#define TEACHER_H

#include "Employee.h"
#include <vector>

class Teacher : virtual public Employee {
protected:
    std::vector<std::string> assignedCourses;

public:
    Teacher(int id = 0, std::string name = "") : Person(id, name), Employee(id, name) {}

    void assignCourse(const std::string& courseCode);
    const std::vector<std::string>& getAssignedCourses() const;

    int getType() const override { return 2; }
    void display() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
