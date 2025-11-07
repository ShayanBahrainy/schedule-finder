#include <iostream>

#include "StudentPreference.h"
#include "AcademicClass.h"


StudentPreference::StudentPreference(Student* student, AcademicClass** preferenceList, int numPreferences) {
    this->numPreferences = numPreferences;
    this->preferenceList = new AcademicClass*[numPreferences]();
    for (int i = 0; i < numPreferences; ++i) {
        this->preferenceList[i] = preferenceList[i];
    }
    this->student = student;
}

Student* StudentPreference::getStudent() const {
    return this->student;
}

AcademicClass* StudentPreference::getPreference(int num) const {
    if (num > numPreferences - 1 || num < 0) {
        std::cout << "Invalid preference number " << num << std::endl;
    }
    return this->preferenceList[num];
}

bool StudentPreference::contains(const AcademicClass academicClass) const {
    for (int i = 0; i < numPreferences; ++i) {
        //std::cout << preferenceList[i]->getName() << " =? " << academicClass.getName() << " ";
        if (*preferenceList[i] == academicClass) {
            return true;
        }
    }

    return false;
}

int StudentPreference::getPreferenceCount() const {
    return numPreferences;
}