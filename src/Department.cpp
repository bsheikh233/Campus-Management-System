#include "Department.h"
#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "TA.h"
#include "IT_Manager.h"
#include "HOD.h"
#include "Course.h"

bool Department::addPerson(std::shared_ptr<Person> person) {
    // Check for duplicate ID
    for (const auto& p : people) {
        if (p->getId() == person->getId()) {
            std::cout << "Error: User with ID " << person->getId() << " already exists!" << std::endl;
            return false;
        }
    }
    people.push_back(person);
    return true;
}

bool Department::addCourse(const Course& course) {
    // Check for duplicate course code
    for (const auto& c : courses) {
        if (c.getCode() == course.getCode()) {
            std::cout << "Error: Course with code " << course.getCode() << " already exists!" << std::endl;
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

bool Department::removePerson(int id) {
    for (auto it = people.begin(); it != people.end(); ++it) {
        if ((*it)->getId() == id) {
            people.erase(it);
            return true;
        }
    }
    return false;
}

bool Department::removeCourse(const std::string& code) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (it->getCode() == code) {
            courses.erase(it);
            return true;
        }
    }
    return false;
}

std::shared_ptr<Person> Department::findPerson(int id) {
    for (auto& p : people) {
        if (p->getId() == id) return p;
    }
    return nullptr;
}

Course* Department::findCourse(const std::string& code) {
    for (auto& c : courses) {
        if (c.getCode() == code) return &c;
    }
    return nullptr;
}

void Department::save(std::ofstream& out) const {
    size_t len = name.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(name.c_str(), len);

    // Save Courses
    size_t courseCount = courses.size();
    out.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
    for (const auto& c : courses) {
        c.save(out);
    }

    // Save People with Type Tag
    size_t peopleCount = people.size();
    out.write(reinterpret_cast<const char*>(&peopleCount), sizeof(peopleCount));
    for (const auto& p : people) {
        int type = p->getType();
        out.write(reinterpret_cast<const char*>(&type), sizeof(type));
        p->save(out);
    }
}

void Department::load(std::ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);

    // Load Courses
    size_t courseCount;
    in.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
    courses.clear();
    for (size_t i = 0; i < courseCount; ++i) {
        Course c;
        c.load(in);
        courses.push_back(c);
    }

    // Load People
    size_t peopleCount;
    in.read(reinterpret_cast<char*>(&peopleCount), sizeof(peopleCount));
    people.clear();
    for (size_t i = 0; i < peopleCount; ++i) {
        int type;
        in.read(reinterpret_cast<char*>(&type), sizeof(type));
        
        std::shared_ptr<Person> p;
        if (type == 1) p = std::make_shared<Student>();
        else if (type == 2) p = std::make_shared<Teacher>();
        else if (type == 3) p = std::make_shared<TA>();
        else if (type == 4) p = std::make_shared<IT_Manager>();
        else if (type == 5) p = std::make_shared<HOD>();
        
        if (p) {
            p->load(in);
            people.push_back(p);
        }
    }
}
