#ifndef HOD_H
#define HOD_H

#include "Teacher.h"

class HOD : public Teacher {
public:
    HOD(int id = 0, std::string name = "") : Person(id, name), Employee(id, name), Teacher(id, name) {}

    int getType() const override { return 5; }

    void manageDepartment() {
        std::cout << name << " is managing the department." << std::endl;
    }

    void display() const override {
        Teacher::display();
        std::cout << " [HOD]" << std::endl;
    }

    void save(std::ofstream& out) const override {
        Teacher::save(out);
    }

    void load(std::ifstream& in) override {
        Teacher::load(in);
    }
};

#endif
