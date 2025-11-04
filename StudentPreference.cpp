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

Student* StudentPreference::getStudent () {
    return this->student;
}

AcademicClass* StudentPreference::getPreference(int num) {
    if (num > numPreferences - 1 || num < 0) {
        std::cout << "Invalid preference number " << num << std::endl;
    }
    return this->preferenceList[num];
}