# Campus Management System (Refactored)

A modern C++ implementation of a Campus Management System using:
- **OOP Principles** (Inheritance, Polymorphism, Encapsulation)
- **Virtual Inheritance** (`TA` inherits from `Student` and `Teacher`)
- **Persistence** (Binary file I/O for saving/loading state)
- **STL Containers** (`std::vector`, `std::map`, `std::string`)
- **Smart Pointers** (`std::shared_ptr`)

## Structure
- `University`: Top-level manager.
- `Department`: Contains Students, Teachers, Courses.
- `Person`: Base class.
- `Student`, `Teacher`: derived from `Person`.
- `TA`: derived from both `Student` and `Teacher` (Diamond solution).

## How to Build and Run

### Windows (Quick Start)
Double-click `build.bat`. This will compile and run the application.

### Command Line (g++)
```sh
g++ -std=c++14 -o cms_app.exe main.cpp University.cpp Department.cpp Course.cpp Student.cpp Teacher.cpp TA.cpp
./cms_app.exe
```

### Using Makefile (Linux/WSL/MinGW)
```sh
make
./cms_app
```

## Features Verified
1. **Virtual Inheritance**: TA object is successfully created and managed as both Student and Teacher.
2. **Persistence**: Run the app once to create data. Run it again to see data loaded and modified.
