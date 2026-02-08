#include "University.h"
#include <iostream>
#include <fstream>

void University::addDepartment(const Department& dept) {
    departments.push_back(dept);
}

bool University::removeDepartment(const std::string& name) {
    for (auto it = departments.begin(); it != departments.end(); ++it) {
        if (it->getName() == name) {
            departments.erase(it);
            return true;
        }
    }
    return false;
}

Department* University::getDepartment(const std::string& name) {
    for (auto& d : departments) {
        if (d.getName() == name) return &d;
    }
    return nullptr;
}

void University::saveData(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return;
    }

    size_t deptCount = departments.size();
    out.write(reinterpret_cast<const char*>(&deptCount), sizeof(deptCount));
    for (const auto& d : departments) {
        d.save(out);
    }
    out.close();
    std::cout << "Data saved to " << filename << std::endl;
}

void University::loadData(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "No existing data found. Starting fresh." << std::endl;
        return;
    }

    size_t deptCount;
    in.read(reinterpret_cast<char*>(&deptCount), sizeof(deptCount));
    departments.clear();
    for (size_t i = 0; i < deptCount; ++i) {
        Department d;
        d.load(in);
        departments.push_back(d);
    }
    in.close();
    std::cout << "Data loaded from " << filename << std::endl;
}

void University::display() const {
    std::cout << "UNIVERSITY: " << name << std::endl;
    for (const auto& d : departments) {
        std::cout << "Department: " << d.getName() << std::endl;
        std::cout << "  Courses: " << d.getCourses().size() << std::endl;
        std::cout << "  People: " << d.getPeople().size() << std::endl;
        for (const auto& p : d.getPeople()) {
            std::cout << "    ";
            p->display();
        }
    }
}
