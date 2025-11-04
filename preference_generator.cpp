#include <iostream>
#include <fstream>
#include <vector>

#include "AcademicClass.h"
#include "StudentPreference.h"
#include "Student.h"

std::vector<AcademicClass> loadClasses(const std::string path) {
    std::ifstream classInputFile(path);

    std::vector<AcademicClass> classes;

    if (!classInputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    while (classInputFile.good()) {
        std::string className;
        classInputFile >> className;

        classes.push_back(AcademicClass(className));
    }

    if (!classInputFile.eof()) {
        std::cout << "Error reading file " << path << std::endl;
    }

    classInputFile.close();

    return classes;

}

std::vector<StudentPreference> loadStudents(const std::string path, std::vector<AcademicClass>& academicClasses) {
    std::ifstream studentInputFile(path);

    std::vector<StudentPreference> preferences;

    if (!studentInputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    while (studentInputFile.good()) {
        std::string studentName;
        studentInputFile >> studentName;

        int grade;
        studentInputFile >> grade;

        Student* student = new Student(studentName, grade);

        AcademicClass* classPreferences[5];

        for (int i = 0; i < 5; ++i ){
            std::string className;
            studentInputFile >> className;
            for (AcademicClass& a : academicClasses) {
                if (a.getName() == className) {
                    classPreferences[i] = &a;
                    break;
                }
            }

        }

        preferences.push_back(StudentPreference(student, classPreferences, 5));
    }

    if (!studentInputFile.eof()) {
        std::cout << "Error reading file " << path << std::endl;
    }

    studentInputFile.close();

    return preferences;
}

int main() {

    std::vector<AcademicClass> aClasses = loadClasses("Classes.txt");

    std::vector<StudentPreference> studentPrefs = loadStudents("Students.txt", aClasses);

    for (auto& stuPref : studentPrefs) {
        Student* student = stuPref.getStudent();
        std::cout << student->getName() << ", grade " << student->getGrade() << " wants to be in ";
        for (int i = 0; i < 4; ++i) {
            std::cout << stuPref.getPreference(i)->getName() << ", ";
        }
        std::cout << "and, " << stuPref.getPreference(4)->getName() << "." << std::endl;
    }

    return 0;
}