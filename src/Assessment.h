#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <string>
#include <iostream>
#include <fstream>

class Assessment {
private:
    std::string name;
    double totalMarks;
    double obtainedMarks;
    double weightage;

public:
    Assessment(std::string name = "", double total = 0, double obtained = 0, double weight = 0)
        : name(name), totalMarks(total), obtainedMarks(obtained), weightage(weight) {}

    std::string getName() const { return name; }
    double getTotalMarks() const { return totalMarks; }
    double getObtainedMarks() const { return obtainedMarks; }
    double getWeightage() const { return weightage; }

    void display() const {
        std::cout << "    - " << name << ": " << obtainedMarks << "/" << totalMarks << " (Weight: " << weightage << "%)" << std::endl;
    }

    void save(std::ofstream& out) const {
        size_t len = name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(name.c_str(), len);
        out.write(reinterpret_cast<const char*>(&totalMarks), sizeof(totalMarks));
        out.write(reinterpret_cast<const char*>(&obtainedMarks), sizeof(obtainedMarks));
        out.write(reinterpret_cast<const char*>(&weightage), sizeof(weightage));
    }

    void load(std::ifstream& in) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        in.read(&name[0], len);
        in.read(reinterpret_cast<char*>(&totalMarks), sizeof(totalMarks));
        in.read(reinterpret_cast<char*>(&obtainedMarks), sizeof(obtainedMarks));
        in.read(reinterpret_cast<char*>(&weightage), sizeof(weightage));
    }
};

#endif
