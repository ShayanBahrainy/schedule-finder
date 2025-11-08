#include <vector>

#include "AcademicClass.h"
#include "Student.h"

#pragma once
class StudentPreference {
    public:
        StudentPreference(Student* student, std::vector<AcademicClass*> preferenceList);
        Student* getStudent() const;
        AcademicClass* getPreference(unsigned int i) const;
        int getPreferenceCount() const;
        bool contains(const AcademicClass academicClass) const;
    private:
        std::vector<AcademicClass*> preferenceList;
        Student* student;
};