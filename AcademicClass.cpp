#include "AcademicClass.h"

AcademicClass::AcademicClass(std::string name) {
    this->className = name;
}

const std::string AcademicClass::getName() {
    return this->className;
}