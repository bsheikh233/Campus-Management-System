#include "Course.h"

void Course::save(std::ofstream& out) const {
    size_t len = code.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(code.c_str(), len);

    len = name.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(name.c_str(), len);
}

void Course::load(std::ifstream& in) {
    size_t len;
    
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    code.resize(len);
    in.read(&code[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    name.resize(len);
    in.read(&name[0], len);
}
