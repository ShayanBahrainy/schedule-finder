#include <iostream>

#include "StudentPreference.h"
#include "AcademicClass.h"


StudentPreference::StudentPreference(Student* student, std::vector<AcademicClass*> preferenceList) {
    this->preferenceList = preferenceList;
    this->student = student;
}

Student* StudentPreference::getStudent() const {
    return this->student;
}

AcademicClass* StudentPreference::getPreference(unsigned int i) const {
    if (i > preferenceList.size() - 1) {
        std::cout << "Invalid preference index " << i << std::endl;
    }
    return this->preferenceList[i];
}

bool StudentPreference::contains(const AcademicClass academicClass) const {
    for (unsigned int i = 0; i < preferenceList.size(); ++i) {
        if (*preferenceList[i] == academicClass) {
            return true;
        }
    }

    return false;
}

int StudentPreference::getPreferenceCount() const {
    return preferenceList.size();
}