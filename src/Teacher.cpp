#include "Teacher.h"
#include <iostream>

void Teacher::assignCourse(const std::string& courseCode) {
    // Check for duplicate assignment
    for (const auto& c : assignedCourses) {
        if (c == courseCode) {
            std::cout << "Course " << courseCode << " is already assigned!" << std::endl;
            return;
        }
    }
    assignedCourses.push_back(courseCode);
}

const std::vector<std::string>& Teacher::getAssignedCourses() const {
    return assignedCourses;
}

void Teacher::display() const {
    Employee::display(); // Call Employee display
    std::cout << " [Teacher]" << std::endl;
    std::cout << "  Assigned Courses: ";
    for (const auto& c : assignedCourses) std::cout << c << " ";
    std::cout << std::endl;
}

void Teacher::save(std::ofstream& out) const {
    Employee::save(out); // Call Employee save
    
    size_t count = assignedCourses.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& c : assignedCourses) {
        size_t len = c.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(c.c_str(), len);
    }
}

void Teacher::load(std::ifstream& in) {
    Employee::load(in);

    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    assignedCourses.clear();
    for (size_t i = 0; i < count; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string c(len, ' ');
        in.read(&c[0], len);
        assignedCourses.push_back(c);
    }
}
