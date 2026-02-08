#include "Student.h"
#include <iostream>
#include <iomanip>

double Student::calculateGPA() const {
    if (registrations.empty()) return 0.0;
    
    double totalPoints = 0.0;
    int coursesWithGrades = 0;
    
    for (const auto& r : registrations) {
        const auto& assessments = r.getAssessments();
        if (assessments.empty()) continue;
        
        // Calculate weighted percentage for this course
        double weightedScore = 0.0;
        double totalWeightage = 0.0;
        
        for (const auto& a : assessments) {
            // Get percentage for this assessment and apply its weightage
            double percentage = (a.getTotalMarks() > 0) ? 
                (a.getObtainedMarks() / a.getTotalMarks()) * 100.0 : 0.0;
            weightedScore += (percentage * a.getWeightage()) / 100.0;
            totalWeightage += a.getWeightage();
        }
        
        // Normalize if weightage doesn't sum to 100
        double courseScore = (totalWeightage > 0) ? 
            (weightedScore / totalWeightage) * 100.0 : 0.0;
        
        // Convert score to grade points
        double gp = 0.0;
        if (courseScore >= 85) gp = 4.0;
        else if (courseScore >= 80) gp = 3.7;
        else if (courseScore >= 75) gp = 3.3;
        else if (courseScore >= 70) gp = 3.0;
        else if (courseScore >= 65) gp = 2.7;
        else if (courseScore >= 60) gp = 2.3;
        else if (courseScore >= 55) gp = 2.0;
        else if (courseScore >= 50) gp = 1.7;
        else gp = 0.0;
        
        totalPoints += gp;
        coursesWithGrades++;
    }
    
    return (coursesWithGrades > 0) ? totalPoints / coursesWithGrades : 0.0;
}

void Student::registerCourse(const std::string& courseCode, const std::string& courseName) {
    // Check if already registered
    for (const auto& r : registrations) {
        if (r.getCourseCode() == courseCode) {
            std::cout << "Already registered for course " << courseCode << std::endl;
            return;
        }
    }
    registrations.emplace_back(courseCode, courseName);
}

bool Student::dropCourse(const std::string& courseCode) {
    for (auto it = registrations.begin(); it != registrations.end(); ++it) {
        if (it->getCourseCode() == courseCode) {
            registrations.erase(it);
            return true;
        }
    }
    return false;
}

Registration* Student::getRegistration(const std::string& courseCode) {
    for (auto& r : registrations) {
        if (r.getCourseCode() == courseCode) return &r;
    }
    return nullptr;
}

void Student::addAssessmentResult(const std::string& courseCode, const Assessment& assessment) {
    Registration* r = getRegistration(courseCode);
    if (r) {
        r->addAssessment(assessment);
    }
}

void Student::display() const {
    Person::display();
    std::cout << " [Student] GPA: " << std::fixed << std::setprecision(2) << calculateGPA() << std::endl;
    std::cout << "  Registrations: " << std::endl;
    for (const auto& r : registrations) {
        r.display();
    }
}

void Student::save(std::ofstream& out) const {
    Person::save(out);
    
    size_t count = registrations.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& r : registrations) {
        r.save(out);
    }
}

void Student::load(std::ifstream& in) {
    Person::load(in);

    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    registrations.clear();
    for (size_t i = 0; i < count; ++i) {
        Registration r;
        r.load(in);
        registrations.push_back(r);
    }
}
