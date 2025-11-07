#include <ctime>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "AcademicClass.h"
#include "StudentPreference.h"
#include "Student.h"
#include "Schedule.h"
#include "generate_schedule.h"

std::vector<AcademicClass> loadClasses(const std::string path) {
    std::ifstream classInputFile;

    classInputFile.open(path);

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
    const int NUM_PREFERENCES = 7;

    std::ifstream studentInputFile;

    studentInputFile.open(path);

    std::vector<StudentPreference> preferences;

    if (!studentInputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }


    std::string studentName;
    while (studentInputFile >> studentName) {
        int grade;
        studentInputFile >> grade;

        Student* student = new Student(studentName, grade);

        AcademicClass* classPreferences[NUM_PREFERENCES];

        for (int i = 0; i < NUM_PREFERENCES; ++i ){
            std::string className;
            studentInputFile >> className;
            for (AcademicClass& a : academicClasses) {
                if (a.getName() == className) {
                    classPreferences[i] = &a;
                    break;
                }
            }

        }

        preferences.push_back(StudentPreference(student, classPreferences, NUM_PREFERENCES));
    }

    if (studentInputFile.bad()) {
        std::cout << "Error reading file " << path <<  " with error " << studentInputFile.badbit << std::endl;
    }

    studentInputFile.close();

    return preferences;
}

int main() {
    srand(time(nullptr));

    std::vector<AcademicClass> academicClasses = loadClasses("Classes.txt");

    std::vector<StudentPreference> studentPrefs = loadStudents("Students.txt", academicClasses);


    Schedule* minSchedule = generateRandomSchedule(academicClasses, 9);
    int maxScore = std::numeric_limits<int>::max();
    for (int i = 0; i < 10; ++i) {
        Schedule* schedule = generateRandomSchedule(academicClasses, 9);
        int score = schedule->score(studentPrefs);
        if (score < maxScore) {
            maxScore = score;
            minSchedule = schedule;
        }
        else {
            delete schedule;
        }
    }
    std::cout << "Here is a schedule I found: " << *minSchedule << std::endl;

    std::cout << "And it has a score of " << minSchedule->score(studentPrefs) << std::endl;
    return 0;
}