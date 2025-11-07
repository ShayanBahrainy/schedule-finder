#include "AcademicClass.h"

#include "Student.h"

#pragma once
class StudentPreference {
    public:
        StudentPreference(Student* student, AcademicClass** preferenceList, int numPreferences);
        Student* getStudent() const;
        AcademicClass* getPreference(int num) const;
    private:
        AcademicClass** preferenceList;
        Student* student;
        int numPreferences;
};