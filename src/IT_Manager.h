#ifndef IT_MANAGER_H
#define IT_MANAGER_H

#include "Employee.h"

class IT_Manager : public Employee {
public:
    IT_Manager(int id = 0, std::string name = "") : Person(id, name), Employee(id, name) {}

    void maintainSystems() {
        std::cout << name << " is maintaining campus systems..." << std::endl;
    }

    void resetUserPassword(Person& p, const std::string& newPass) {
        p.setPassword(newPass);
        std::cout << "Password reset for user " << p.getName() << std::endl;
    }

    int getType() const override { return 4; }

    void display() const override {
        Employee::display();
        std::cout << " [IT Manager]" << std::endl;
    }
    
    void save(std::ofstream& out) const override {
        Employee::save(out);
    }

    void load(std::ifstream& in) override {
        Employee::load(in);
    }
};

#endif
