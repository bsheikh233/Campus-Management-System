#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <vector>
#include <string>
#include "Department.h"

class University {
private:
    std::string name;
    std::vector<Department> departments;

public:
    University(std::string name = "My University") : name(name) {}

    void addDepartment(const Department& dept);
    bool removeDepartment(const std::string& name);
    Department* getDepartment(const std::string& name);
    std::vector<Department>& getDepartments() { return departments; } // Exposed for Main Search
    
    // Centralized Persistence
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

    void display() const;
};

#endif
