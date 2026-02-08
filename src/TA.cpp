#include "TA.h"
#include <iostream>

// Note: TA::display calls Person::display twice if we aren't careful?
// No, Person is virtual base.
// But Student::display calls Person::display() and Teacher::display calls Employee::display() which calls Person::display().
// We need to be careful with display to avoid duplicate Person output.
// We'll override display completely.

void TA::display() const {
    Person::display(); 
    std::cout << " [TA]" << std::endl;
    
    // Display Student part (Registrations)
    std::cout << "  [As Student]:" << std::endl;
    std::cout << "   Registrations: " << std::endl;
    for (const auto& r : registrations) {
        r.display();
    }

    // Display Teacher part (Assigned Courses)
    std::cout << "  [As Teacher]:" << std::endl;
    std::cout << "   Assigned Courses: ";
    for (const auto& c : assignedCourses) std::cout << c << " ";
    std::cout << std::endl;
}

void TA::save(std::ofstream& out) const {
    // Person is virtual base, so it should be saved once.
    // However, our save/load manual logic is tricky with virtual bases.
    // We already decided in previous steps to save components manually to avoid ambiguity/duplication in file format.

    Person::save(out); // Save ID, Name

    // Save Student specific data (registrations)
    size_t count = registrations.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& r : registrations) {
        r.save(out);
    }

    // Save Teacher/Employee specific data
    // Issue: Teacher has 'employeeId' (from Employee).
    // We should probably save that too? For now assuming employeeId == Person::id. which is already saved.
    
    // Save Assigned Courses (Teacher data)
    size_t tCount = assignedCourses.size();
    out.write(reinterpret_cast<const char*>(&tCount), sizeof(tCount));
    for (const auto& c : assignedCourses) {
        size_t len = c.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(c.c_str(), len);
    }
}

void TA::load(std::ifstream& in) {
    Person::load(in);

    // Load Student data
    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    registrations.clear();
    for (size_t i = 0; i < count; ++i) {
        Registration r;
        r.load(in);
        registrations.push_back(r);
    }

    // Load Teacher data
    size_t tCount;
    in.read(reinterpret_cast<char*>(&tCount), sizeof(tCount));
    assignedCourses.clear();
    for (size_t i = 0; i < tCount; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string c(len, ' ');
        in.read(&c[0], len);
        assignedCourses.push_back(c);
    }
}
