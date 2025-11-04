#include "Student.h"


Student::Student(std::string name, int grade) {
    this->name = name;
    this->grade = grade;
}

int Student::getGrade() {
   return this->grade;
}

std::string Student::getName() {
    return this->name;
}

