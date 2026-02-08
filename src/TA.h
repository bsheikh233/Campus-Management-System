#ifndef TA_H
#define TA_H

#include "Student.h"
#include "Teacher.h"

class TA : public Student, public Teacher {
public:
    TA(int id = 0, std::string name = "") 
        : Person(id, name), Employee(id, name), Student(id, name), Teacher(id, name) {}

    int getType() const override { return 3; }
    void display() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
