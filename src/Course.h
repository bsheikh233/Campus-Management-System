#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <fstream>
#include <iostream>

class Course {
private:
    std::string code;
    std::string name;

public:
    Course(std::string code = "", std::string name = "") : code(code), name(name) {}

    std::string getCode() const { return code; }
    std::string getName() const { return name; }

    void display() const {
        std::cout << "Course Code: " << code << ", Name: " << name << std::endl;
    }

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);
};

#endif
