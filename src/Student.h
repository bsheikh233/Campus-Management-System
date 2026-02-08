#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Registration.h"
#include <vector>
#include <memory>

class Student : virtual public Person {
protected:
    std::vector<Registration> registrations;

public:
    Student(int id = 0, std::string name = "") : Person(id, name) {}

    double calculateGPA() const;
    void registerCourse(const std::string& courseCode, const std::string& courseName);
    bool dropCourse(const std::string& courseCode);
    void addAssessmentResult(const std::string& courseCode, const Assessment& assessment);
    
    // Helper to get registration
    Registration* getRegistration(const std::string& courseCode);

    int getType() const override { return 1; }
    void display() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
};

#endif
