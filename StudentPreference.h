#include "AcademicClass.h"

#include "Student.h"

#pragma once
class StudentPreference {
    public:
        StudentPreference(Student* student, AcademicClass** preferenceList, int numPreferences);
        Student* getStudent() const;
        AcademicClass* getPreference(int num) const;
        int getPreferenceCount() const;
        bool contains(const AcademicClass academicClass) const;
    private:
        AcademicClass** preferenceList;
        Student* student;
        int numPreferences;
};