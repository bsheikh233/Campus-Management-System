#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <fstream>

class Person {
protected:
    std::string name;
    int id;
    std::string password;

public:
    Person(int id = 0, std::string name = "", std::string pass = "1234") 
        : name(name), id(id), password(pass) {}
    virtual ~Person() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    
    bool authenticate(const std::string& inputPass) const {
        return password == inputPass;
    }

    void setPassword(const std::string& newPass) {
        password = newPass;
    }

    virtual int getType() const = 0;

    virtual void display() const {
        std::cout << "ID: " << id << ", Name: " << name;
    }

    virtual void save(std::ofstream& out) const {
        size_t len = name.size();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(name.c_str(), len);
        
        len = password.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(password.c_str(), len);
    }

    virtual void load(std::ifstream& in) {
        size_t len;
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        in.read(&name[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        password.resize(len);
        in.read(&password[0], len);
    }
};

#endif
