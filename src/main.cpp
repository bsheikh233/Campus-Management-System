#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <vector>
#include "University.h"
#include "Department.h"
#include "Student.h"
#include "Teacher.h"
#include "TA.h"
#include "IT_Manager.h"
#include "HOD.h"
#include "Course.h"
#ifdef _WIN32
    #include <conio.h>
#endif

// --- Helper Functions ---
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

std::string getPassword(const std::string& prompt) {
    std::string password = "";
    char ch;
    std::cout << prompt;
#ifdef _WIN32
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else if (ch >= 32 && ch <= 126) {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
#else
    std::getline(std::cin, password); // Fallback for non-windows
#endif
    return password;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

University univ("My University");
const std::string DATA_FILE = "university_data.dat";

// --- Forward Declarations ---
void loginMenu();
void studentPanel(std::shared_ptr<Student> s, Department* dept);
void teacherPanel(std::shared_ptr<Teacher> t, Department* dept);
void hodPanel(std::shared_ptr<HOD> h, Department* dept);
void itManagerPanel(std::shared_ptr<IT_Manager> it, Department* dept);
void taChoicePanel(std::shared_ptr<TA> ta, Department* dept);

int main() {
    std::cout << "Loading data..." << std::endl;
    univ.loadData(DATA_FILE);

    // Initial Setup if empty
    if (univ.getDepartments().empty()) {
        Department admin("Administration");
        auto defaultIT = std::make_shared<IT_Manager>(1, "SuperAdmin");
        defaultIT->setPassword("admin");
        admin.addPerson(defaultIT);
        univ.addDepartment(admin);
        std::cout << "Initialized default Admin (ID: 1, Pass: admin)" << std::endl;
    }

    while (true) {
        clearScreen();
        std::cout << "\n=== CAMPUS MANAGEMENT SYSTEM ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Save & Exit" << std::endl;
        std::cout << "Select: ";
        
        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();

        if (choice == 1) {
            loginMenu();
        } else if (choice == 2) {
            univ.saveData(DATA_FILE);
            std::cout << "Goodbye!" << std::endl;
            return 0;
        } else {
            std::cout << "Invalid choice." << std::endl;
            pause();
        }
    }
}

void loginMenu() {
    clearScreen();
    int id;
    std::cout << "=== LOGIN ===" << std::endl;
    std::cout << "User ID: "; 
    if (!(std::cin >> id)) { clearInput(); return; }
    clearInput();
    std::string pass = getPassword("Password: ");

    std::shared_ptr<Person> user = nullptr;
    Department* userDept = nullptr;

    // Search all departments
    for (auto& dept : univ.getDepartments()) {
        user = dept.findPerson(id);
        if (user) {
            userDept = &dept;
            break;
        }
    }

    if (!user) {
        std::cout << "User not found!" << std::endl;
        return;
    }

    if (!user->authenticate(pass)) {
        std::cout << "Invalid Password!" << std::endl;
        pause();
        return;
    }

    std::cout << "Welcome, " << user->getName() << "!" << std::endl;

    // Dispatch based on type
    int type = user->getType();
    if (type == 1) studentPanel(std::dynamic_pointer_cast<Student>(user), userDept);
    else if (type == 2) teacherPanel(std::dynamic_pointer_cast<Teacher>(user), userDept);
    else if (type == 3) taChoicePanel(std::dynamic_pointer_cast<TA>(user), userDept);
    else if (type == 4) itManagerPanel(std::dynamic_pointer_cast<IT_Manager>(user), userDept);
    else if (type == 5) hodPanel(std::dynamic_pointer_cast<HOD>(user), userDept);
    else std::cout << "Unknown Role." << std::endl;
}

// --- STUDENT PANEL ---
void studentPanel(std::shared_ptr<Student> s, Department* dept) {
    while (true) {
        clearScreen();
        std::cout << "\n--- Student Menu (" << s->getName() << ") ---" << std::endl;
        std::cout << "1. Register Course" << std::endl;
        std::cout << "2. View My Courses" << std::endl;
        std::cout << "3. Drop Course" << std::endl;
        std::cout << "4. View Report (GPA & Attendance)" << std::endl;
        std::cout << "5. Change Password" << std::endl;
        std::cout << "6. Logout / Go Back" << std::endl;
        std::cout << "Select: ";
        
        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();

        if (choice == 6) break;

        if (choice == 1) {
            std::cout << "Available Courses in " << dept->getName() << ":" << std::endl;
            for (const auto& c : dept->getCourses()) {
                std::cout << c.getCode() << " - " << c.getName() << std::endl;
            }
            std::string code;
            std::cout << "Enter Course Code: "; std::getline(std::cin, code);
            Course* c = dept->findCourse(code);
            if (c) {
                s->registerCourse(c->getCode(), c->getName());
                std::cout << "Registered successfully." << std::endl;
            } else {
                std::cout << "Course not found." << std::endl;
            }
            pause();
        } else if (choice == 2) {
            // View enrolled courses
            std::cout << "\n=== Your Enrolled Courses ===" << std::endl;
            s->display();
            pause();
        } else if (choice == 3) {
             // Show enrolled courses before dropping
             std::cout << "\nYour enrolled courses:" << std::endl;
             s->display();
             std::string code;
             std::cout << "Enter Course Code to Drop: "; std::getline(std::cin, code);
             if (s->dropCourse(code)) {
                 std::cout << "Course Dropped." << std::endl;
             } else {
                 std::cout << "Not registered for this course." << std::endl;
             }
             pause();
        } else if (choice == 4) {
            s->display();
            pause();
        } else if (choice == 5) {
            std::string newPass = getPassword("Enter new password: ");
            s->setPassword(newPass);
            std::cout << "Password changed." << std::endl;
            pause();
        }
    }
}

// --- TEACHER PANEL ---
void teacherPanel(std::shared_ptr<Teacher> t, Department* dept) {
    while (true) {
        clearScreen();
        std::cout << "\n--- Teacher Menu (" << t->getName() << ") ---" << std::endl;
        std::cout << "1. Mark Attendance" << std::endl;
        std::cout << "2. Assign Marks" << std::endl;
        std::cout << "3. View Assigned Courses" << std::endl;
        std::cout << "4. View Enrolled Students" << std::endl;
        std::cout << "5. Change Password" << std::endl;
        std::cout << "6. Logout / Go Back" << std::endl;
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();
        if (choice == 6) break;

        if (choice == 1) {
             std::string code;
             std::cout << "Course Code: "; std::getline(std::cin, code);
             int stId;
             std::cout << "Student ID: "; std::cin >> stId; clearInput();
             
             auto p = dept->findPerson(stId);
             auto stu = std::dynamic_pointer_cast<Student>(p);
             if (stu) {
                 auto reg = stu->getRegistration(code);
                 if (reg) {
                     char pChar;
                     std::cout << "Present? (y/n): "; std::cin >> pChar; clearInput();
                     reg->addAttendance(pChar == 'y' || pChar == 'Y');
                     std::cout << "Attendance Marked." << std::endl;
                 } else std::cout << "Student not registered for this course." << std::endl;
             } else std::cout << "Student not found." << std::endl;
             pause();

        } else if (choice == 2) {
             std::string code, aName;
             std::cout << "Course Code: "; std::getline(std::cin, code);
             std::cout << "Assessment Name: "; std::getline(std::cin, aName);
             
             double total, obt, w;
             std::cout << "Total: "; std::cin >> total;
             std::cout << "Obtained: "; std::cin >> obt;
             std::cout << "Weightage: "; std::cin >> w; clearInput();

             int stId;
             std::cout << "Student ID: "; std::cin >> stId; clearInput();
             auto p = dept->findPerson(stId);
             auto stu = std::dynamic_pointer_cast<Student>(p);
             if (stu) {
                 stu->addAssessmentResult(code, Assessment(aName, total, obt, w));
                 std::cout << "Marks assigned." << std::endl;
             } else std::cout << "Student not found." << std::endl;
             pause();
        } else if (choice == 3) {
            t->display();
            pause();
        } else if (choice == 4) {
            // View enrolled students in teacher's courses
            std::cout << "\nStudents in your courses:\n";
            for (const auto& courseCode : t->getAssignedCourses()) {
                std::cout << "\n  Course: " << courseCode << std::endl;
                bool found = false;
                for (const auto& p : dept->getPeople()) {
                    auto stu = std::dynamic_pointer_cast<Student>(p);
                    if (stu && stu->getRegistration(courseCode)) {
                        std::cout << "    - ID: " << stu->getId() << ", Name: " << stu->getName() << std::endl;
                        found = true;
                    }
                }
                if (!found) std::cout << "    (No students enrolled)" << std::endl;
            }
            pause();
        } else if (choice == 5) {
            std::string newPass = getPassword("Enter new password: ");
            t->setPassword(newPass);
            std::cout << "Password changed successfully." << std::endl;
            pause();
        }
    }
}

// --- HOD PANEL ---
void hodPanel(std::shared_ptr<HOD> h, Department* dept) {
    while (true) {
        clearScreen();
        std::cout << "\n--- HOD Menu (" << h->getName() << " - " << dept->getName() << ") ---" << std::endl;
        std::cout << "1. Add Course" << std::endl;
        std::cout << "2. Assign Course to Teacher" << std::endl;
        std::cout << "3. Remove Course" << std::endl;
        std::cout << "4. Remove Person" << std::endl;
        std::cout << "5. View Dept Stats" << std::endl;
        std::cout << "6. View Department Members" << std::endl;
        std::cout << "7. Change Password" << std::endl;
        std::cout << "8. Logout / Go Back" << std::endl;
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();
        if (choice == 8) break;

        if (choice == 1) {
            std::string cCode, cName;
            std::cout << "Code: "; std::getline(std::cin, cCode);
            std::cout << "Name: "; std::getline(std::cin, cName);
            if (dept->addCourse(Course(cCode, cName))) {
                std::cout << "Course Added." << std::endl;
            }
            pause();
        } else if (choice == 2) {
            int tId;
            std::cout << "Teacher ID (in this dept): "; std::cin >> tId; clearInput();
            auto p = dept->findPerson(tId);
            auto teacher = std::dynamic_pointer_cast<Teacher>(p);
            if (teacher) {
                std::string cCode;
                std::cout << "Course Code: "; std::getline(std::cin, cCode);
                teacher->assignCourse(cCode);
            } else {
                std::cout << "Teacher not found in this department." << std::endl;
            }
            pause();
        } else if (choice == 3) {
             std::string code;
             std::cout << "Course Code: "; std::getline(std::cin, code);
             if (dept->removeCourse(code)) std::cout << "Course Removed." << std::endl;
             else std::cout << "Course not found." << std::endl;
             pause();
        } else if (choice == 4) {
             int id;
             std::cout << "Person ID: "; std::cin >> id; clearInput();
             if (dept->removePerson(id)) std::cout << "Person Removed." << std::endl;
             else std::cout << "Person not found." << std::endl;
             pause();
        } else if (choice == 5) {
            std::cout << "Department: " << dept->getName() << std::endl;
            std::cout << "Total People: " << dept->getPeople().size() << std::endl;
            std::cout << "Total Courses: " << dept->getCourses().size() << std::endl;
            pause();
        } else if (choice == 6) {
            // View all department members
            std::cout << "\n=== Department Members ===\n";
            for (const auto& p : dept->getPeople()) {
                std::cout << "  ";
                p->display();
            }
            pause();
        } else if (choice == 7) {
            std::string newPass = getPassword("Enter new password: ");
            h->setPassword(newPass);
            std::cout << "Password changed successfully." << std::endl;
            pause();
        }
    }
}

// --- IT MANAGER PANEL ---
void itManagerPanel(std::shared_ptr<IT_Manager> it, Department* /*dept*/) {
    // IT Manager can access ALL departments
    while (true) {
        clearScreen();
        std::cout << "\n--- IT Manager Menu (" << it->getName() << ") ---" << std::endl;
        std::cout << "1. Add Department" << std::endl;
        std::cout << "2. Remove Department" << std::endl;
        std::cout << "3. Add User" << std::endl;
        std::cout << "4. Remove User" << std::endl;
        std::cout << "5. Reset User Password" << std::endl;
        std::cout << "6. List All Users" << std::endl;
        std::cout << "7. Change My Password" << std::endl;
        std::cout << "8. Logout / Go Back" << std::endl;
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();
        if (choice == 8) break;

        if (choice == 1) {
            std::string name;
            std::cout << "Dept Name: "; std::getline(std::cin, name);
            univ.addDepartment(Department(name));
            std::cout << "Department Added." << std::endl;
            pause();
        } else if (choice == 2) {
            std::string name;
            std::cout << "Dept Name to Remove: "; std::getline(std::cin, name);
            if (univ.removeDepartment(name)) std::cout << "Department Removed." << std::endl;
            else std::cout << "Department not found." << std::endl;
            pause();
        } else if (choice == 3) {
            std::string dName;
            std::cout << "Target Dept: "; std::getline(std::cin, dName);
            Department* d = univ.getDepartment(dName);
            if (!d) { std::cout << "Dept not found." << std::endl; continue; }

            int type, id;
            std::string name;
            std::cout << "Type (1=Stu, 2=Tchr, 3=TA, 4=IT, 5=HOD): "; std::cin >> type;
            std::cout << "ID: "; std::cin >> id; clearInput();
            std::cout << "Name: "; std::getline(std::cin, name);

            if (type == 1) d->addPerson(std::make_shared<Student>(id, name));
            else if (type == 2) d->addPerson(std::make_shared<Teacher>(id, name));
            else if (type == 3) d->addPerson(std::make_shared<TA>(id, name));
            else if (type == 4) d->addPerson(std::make_shared<IT_Manager>(id, name));
            else if (type == 5) d->addPerson(std::make_shared<HOD>(id, name));
            else std::cout << "Invalid Type." << std::endl;
            pause();
        } else if (choice == 4) {
             int id;
             std::cout << "ID to remove: "; std::cin >> id; clearInput();
             bool found = false;
             for (auto& d : univ.getDepartments()) {
                 if (d.removePerson(id)) {
                     std::cout << "User removed from " << d.getName() << std::endl;
                     found = true;
                     break;
                 }
             }
             if (!found) std::cout << "User not found." << std::endl;
             pause();
        } else if (choice == 5) {
            int id;
            std::cout << "User ID: "; std::cin >> id; clearInput();
            std::shared_ptr<Person> victim = nullptr;
            for (auto& d : univ.getDepartments()) {
                victim = d.findPerson(id);
                if (victim) break;
            }
            if (victim) {
                it->resetUserPassword(*victim, "1234"); 
            } else {
                std::cout << "User not found." << std::endl;
            }
            pause();
        } else if (choice == 6) {
            // List all users across all departments
            std::cout << "\n=== All System Users ==="<< std::endl;
            for (const auto& d : univ.getDepartments()) {
                std::cout << "\nDepartment: " << d.getName() << std::endl;
                for (const auto& p : d.getPeople()) {
                    std::cout << "  ";
                    p->display();
                }
            }
            pause();
        } else if (choice == 7) {
            std::string newPass = getPassword("Enter new password: ");
            it->setPassword(newPass);
            std::cout << "Password changed successfully." << std::endl;
            pause();
        }
    }
}

// --- TA PANEL ---
void taChoicePanel(std::shared_ptr<TA> ta, Department* dept) {
    while (true) {
        clearScreen();
        std::cout << "\n--- TA Menu (" << ta->getName() << ") ---" << std::endl;
        std::cout << "1. Student View" << std::endl;
        std::cout << "2. Teacher View" << std::endl;
        std::cout << "3. Logout / Go Back" << std::endl;
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) { clearInput(); continue; }
        clearInput();

        if (choice == 3) break;
        if (choice == 1) studentPanel(ta, dept);
        if (choice == 2) teacherPanel(ta, dept);
    }
}
