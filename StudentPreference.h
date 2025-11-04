#include "AcademicClass.h"

#include "Student.h"

#pragma once
class StudentPreference {
    public:
        StudentPreference(Student* student, AcademicClass** preferenceList, int numPreferences);
        Student* getStudent();
        AcademicClass* getPreference(int num);
    private:
        AcademicClass** preferenceList;
        Student* student;
        int numPreferences;
};