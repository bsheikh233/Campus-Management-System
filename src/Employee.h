#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : virtual public Person {
protected:
    int employeeId; // Special employee ID separate from Person ID? Or just use same?
    // Let's assume Person ID is the SSN/CNIC, and Employee ID is internal. 
    // For simplicity refactoring, we'll keep it simple.

public:
    Employee(int id = 0, std::string name = "") : Person(id, name), employeeId(id) {}
    
    virtual void work() const {
        std::cout << name << " is working." << std::endl;
    }

    void display() const override {
        Person::display();
        std::cout << " [Employee]";
    }

    void save(std::ofstream& out) const override {
        Person::save(out);
        // Save specific employee data if any
    }

    void load(std::ifstream& in) override {
        Person::load(in);
        // Load specific employee data
    }
};

#endif
