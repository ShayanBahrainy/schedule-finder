#include <ctime>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <chrono>
#include <set>
#include <iomanip>

#include "AcademicClass.h"
#include "StudentPreference.h"
#include "Student.h"
#include "Schedule.h"
#include "generate_schedule.h"

std::vector<AcademicClass*> loadClasses(const std::string path) {
    std::ifstream classInputFile;

    classInputFile.open(path);

    std::vector<AcademicClass*> classes;

    if (!classInputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    while (classInputFile.good()) {
        std::string className;
        classInputFile >> className;

        classes.push_back(new AcademicClass(className));
    }

    if (!classInputFile.eof()) {
        std::cout << "Error reading file " << path << std::endl;
    }

    classInputFile.close();

    return classes;

}

std::set<StudentPreference> loadPreferences(const std::string path, std::vector<AcademicClass*>& academicClasses) {
    std::ifstream studentInputFile;

    studentInputFile.open(path);

    std::set<StudentPreference> preferences;

    if (!studentInputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    int NUM_PREFS;
    studentInputFile >> NUM_PREFS;


    std::string studentName;
    while (studentInputFile >> studentName) {
        int grade;
        studentInputFile >> grade;

        Student* student = new Student(studentName, grade);

        std::vector<AcademicClass*> classPreferences(NUM_PREFS, nullptr);

        for (int i = 0; i < NUM_PREFS; ++i ){
            std::string className;
            studentInputFile >> className;
            for (AcademicClass* a : academicClasses) {
                if (a->getName() == className) {
                    classPreferences[i] = a;
                    break;
                }
            }

        }

        preferences.insert(StudentPreference(student, classPreferences));
    }

    if (studentInputFile.bad()) {
        std::cout << "Error reading file " << path <<  " with error " << studentInputFile.badbit << std::endl;
    }

    studentInputFile.close();

    return preferences;
}

void performSearch(bool smart, const int SEARCH_COUNT, const int PERIOD_COUNT, const std::vector<AcademicClass*>& academicClasses, const std::set<StudentPreference>& studentPrefs) {

    Schedule* minSchedule;

    if (smart) {
        minSchedule = ScheduleGeneration::AnalyzeAndGenerateSchedule(academicClasses, PERIOD_COUNT, studentPrefs);
    }
    else {
        minSchedule = ScheduleGeneration::generateRandomSchedule(academicClasses, PERIOD_COUNT);
    }

    int minScore = std::numeric_limits<int>::max();

    std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < SEARCH_COUNT; ++i) {
        if (i % 100000 == 0) {
            std::cout << "Current lowest score: " << minScore << std::endl;
        }
        Schedule* schedule;
        if (smart) {
            schedule = ScheduleGeneration::AnalyzeAndGenerateSchedule(academicClasses, PERIOD_COUNT, studentPrefs);
        }
        else {
            schedule = ScheduleGeneration::generateRandomSchedule(academicClasses, PERIOD_COUNT);
        }
        int score = schedule->score(studentPrefs);
        if (score < minScore) {
            minScore = score;
            minSchedule = schedule;
        }
        else {
            delete schedule;
        }
    }
    if (smart) {
        //Check some mutations
        for (int i = 0; i < SEARCH_COUNT; ++i) {
            if (i % 100000 == 0) {
                std::cout << "Current lowest score: " << minScore << std::endl;
            }
            Schedule* schedule = new Schedule(*minSchedule);
            schedule->mutate();


            int r = rand() % 100;
            while (r < 50) {
                schedule->mutate();
                r = rand() % 100;
            }

            int score = schedule->score(studentPrefs);
            if (score < minScore) {
                minScore = score;
                minSchedule = schedule;
            }
            else {
                delete schedule;
            }
        }
    }

    std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();


    std::cout << "Here is a schedule: " << *minSchedule << std::endl;

    std::cout << "And it has a score of " << minSchedule->score(studentPrefs) << std::endl;


    int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    double rate = SEARCH_COUNT / (double) milliseconds;

    std::cout << "That took " << (int) (milliseconds/1000 )<< " seconds, that means they were computed at a rate of " << rate*1000 << " searches/second " << std::endl;

    std::cout << "This was" << (smart ? " " : " not ") << "a smart search" << std::endl;

}

int main() {
    const int SEARCH_COUNT = 100000;
    const int PERIOD_COUNT = 8;

    srand(time(nullptr));
    std::vector<AcademicClass*> academicClasses = loadClasses("ClassesShort.txt");

    std::set<StudentPreference> studentPrefs = loadPreferences("Preferences.txt", academicClasses);

    std::vector<ClassPairWithFrequency> matches = Schedule::analyzePreferences(academicClasses, studentPrefs);

    /*
    std::cout << "Here are the pairs of classes with ascending frequency: " << std::endl;
    for (auto& match : matches) {
        std::cout << match.pair.at(0)->getName() << " & " << match.pair.at(1)->getName() << " - " << match.frequency << std::endl;
    }*/

    performSearch(false, SEARCH_COUNT, PERIOD_COUNT, academicClasses, studentPrefs);
    std::cout << std::setw(25) << std::setfill('-') << "" << std::endl;
    performSearch(true, SEARCH_COUNT, PERIOD_COUNT, academicClasses, studentPrefs);

}