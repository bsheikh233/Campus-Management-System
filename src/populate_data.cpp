#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "University.h"
#include "Department.h"
#include "Student.h"
#include "Teacher.h"
#include "TA.h"
#include "IT_Manager.h"
#include "HOD.h"
#include "Course.h"

int main() {
    std::srand(std::time(0));
    University univ("Test University");
    
    // 1. Create Departments
    Department cs("Computer Science");
    Department ee("Electrical Engineering");
    
    // 2. Create Courses
    cs.addCourse(Course("CS101", "Introduction to Computing"));
    cs.addCourse(Course("CS102", "Object Oriented Programming"));
    cs.addCourse(Course("CS201", "Data Structures"));
    cs.addCourse(Course("CS205", "Database Systems"));
    
    ee.addCourse(Course("EE101", "Basic Electronics"));
    ee.addCourse(Course("EE102", "Circuit Analysis"));
    
    // 3. Create Admin/IT
    auto superAdmin = std::make_shared<IT_Manager>(1, "SuperAdmin");
    superAdmin->setPassword("admin");
    
    // 4. Create HODs
    auto hodCS = std::make_shared<HOD>(101, "Dr. Alan Turing");
    hodCS->setPassword("1234");
    
    auto hodEE = std::make_shared<HOD>(102, "Dr. Tesla");
    hodEE->setPassword("1234");
    
    // 5. Create Teachers
    auto t1 = std::make_shared<Teacher>(301, "Prof. Knuth"); t1->assignCourse("CS201");
    auto t2 = std::make_shared<Teacher>(302, "Prof. Ritchie"); t2->assignCourse("CS101");
    auto t3 = std::make_shared<Teacher>(303, "Prof. Stroustrup"); t3->assignCourse("CS102");
    
    auto t4 = std::make_shared<Teacher>(304, "Prof. Maxwell"); t4->assignCourse("EE101");
    
    // 6. Create Students (CS)
    for (int i = 1; i <= 20; ++i) {
        int id = 2000 + i;
        auto s = std::make_shared<Student>(id, "Student " + std::to_string(i));
        s->setPassword("1234");
        
        // Register for random courses
        if (std::rand() % 2 == 0) s->registerCourse("CS101", "Introduction to Computing");
        if (std::rand() % 2 == 0) s->registerCourse("CS102", "Object Oriented Programming");
        if (std::rand() % 2 == 0) s->registerCourse("CS201", "Data Structures");
        
        // Add random grades
        if (auto reg = s->getRegistration("CS101")) {
             reg->addAttendance(true);
             reg->addAttendance(true);
             reg->addAttendance(false); // 66%
             s->addAssessmentResult("CS101", Assessment("Quiz 1", 10, 5 + (std::rand()%6), 10));
             s->addAssessmentResult("CS101", Assessment("Midterm", 50, 20 + (std::rand()%31), 40));
        }
        
        cs.addPerson(s);
    }
    
    // 7. Create Students (EE)
     for (int i = 1; i <= 10; ++i) {
        int id = 3000 + i;
        auto s = std::make_shared<Student>(id, "EE Student " + std::to_string(i));
        s->setPassword("1234");
        s->registerCourse("EE101", "Basic Electronics");
        ee.addPerson(s);
    }
    
    // Add People to Depts
    // Admin goes to CS just to be somewhere, or create Admin dept.
    Department admin("Administration");
    admin.addPerson(superAdmin);
    
    cs.addPerson(hodCS);
    cs.addPerson(t1);
    cs.addPerson(t2);
    cs.addPerson(t3);
    
    ee.addPerson(hodEE);
    ee.addPerson(t4);
    
    // Add Depts to Univ
    univ.addDepartment(admin);
    univ.addDepartment(cs);
    univ.addDepartment(ee);
    
    // Save
    univ.saveData("university_data.dat");
    std::cout << "Data populated successfully!" << std::endl;
    
    return 0;
}
