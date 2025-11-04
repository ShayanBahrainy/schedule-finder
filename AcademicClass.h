#include <string>
#include <vector>

#include "Student.h"

#pragma once
class AcademicClass {
    public:
        AcademicClass(std::string className);
        const std::string getName();
    private:
        std::string className;
        std::vector<Student*> requiredStudents; //List of students that must be in this class
};
