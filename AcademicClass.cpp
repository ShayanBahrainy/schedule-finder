#include "AcademicClass.h"

AcademicClass::AcademicClass(std::string name) {
    this->className = name;
}

std::string AcademicClass::getName() const {
    return this->className;
}

bool AcademicClass::operator==(AcademicClass otherClass) const {
    if (otherClass.className == this->className) {
        return true;
    }
    return false;
}