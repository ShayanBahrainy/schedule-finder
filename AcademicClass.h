#include <ostream>
#include <string>
#include <vector>

#include "Student.h"

#pragma once
class AcademicClass {
    public:
        AcademicClass(std::string className);
        std::string getName() const;
        bool operator==(AcademicClass otherClass) const;
    private:
        std::string className;
        std::vector<Student*> requiredStudents; //List of students that must be in this class
};

std::ostream& operator<<(std::ostream& os, const AcademicClass& cls);