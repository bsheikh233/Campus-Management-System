#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Assessment.h"

class Registration {
private:
    std::string courseCode;
    std::string courseName; // Cache for display
    std::vector<Assessment> assessments;
    int totalClasses;
    int presentClasses;

public:
    Registration(std::string code = "", std::string name = "") 
        : courseCode(code), courseName(name), totalClasses(0), presentClasses(0) {}

    std::string getCourseCode() const { return courseCode; }
    std::string getCourseName() const { return courseName; }
    
    void addAssessment(const Assessment& assess) {
        assessments.push_back(assess);
    }

    void addAttendance(bool present) {
        totalClasses++;
        if (present) presentClasses++;
    }

    double getAttendancePercentage() const {
        if (totalClasses == 0) return 0.0;
        return (static_cast<double>(presentClasses) / totalClasses) * 100.0;
    }

    const std::vector<Assessment>& getAssessments() const { return assessments; }

    void display() const {
        std::cout << "  Course: " << courseCode << " (" << courseName << ")" << std::endl;
        std::cout << "   Attendance: " << getAttendancePercentage() << "% (" 
                  << presentClasses << "/" << totalClasses << ")" << std::endl;
        std::cout << "   Assessments:" << std::endl;
        for (const auto& a : assessments) {
            a.display();
        }
    }

    void save(std::ofstream& out) const {
        size_t len = courseCode.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(courseCode.c_str(), len);
        
        len = courseName.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(courseName.c_str(), len);

        out.write(reinterpret_cast<const char*>(&totalClasses), sizeof(totalClasses));
        out.write(reinterpret_cast<const char*>(&presentClasses), sizeof(presentClasses));

        size_t count = assessments.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& a : assessments) {
            a.save(out);
        }
    }

    void load(std::ifstream& in) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        courseCode.resize(len);
        in.read(&courseCode[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        courseName.resize(len);
        in.read(&courseName[0], len);

        in.read(reinterpret_cast<char*>(&totalClasses), sizeof(totalClasses));
        in.read(reinterpret_cast<char*>(&presentClasses), sizeof(presentClasses));

        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        assessments.clear();
        for (size_t i = 0; i < count; ++i) {
            Assessment a;
            a.load(in);
            assessments.push_back(a);
        }
    }
};

#endif
