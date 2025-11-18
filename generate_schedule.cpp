#include <vector>
#include <iostream>
#include <set>
#include <map>

#include "AcademicClass.h"
#include "Schedule.h"
#include "generate_schedule.h"
#include "Schedule.h"
#include "Utils.h"

std::map<std::set<StudentPreference>, std::vector<ClassPairWithFrequency>> cache;

Schedule* ScheduleGeneration::generateRandomSchedule(const std::vector<AcademicClass*> classList, unsigned int periodCount) {

    if (periodCount > classList.size()) {
        std::cout << "Error: Not enough classes (" << classList.size() << ") to fill " << periodCount << " periods. ";
    }

    std::vector<AcademicClass*> availableClasses = classList;

    std::vector<std::vector<AcademicClass*>> init(periodCount);

    while (availableClasses.size() > 0) {
        for (unsigned int i = 0; i < periodCount; ++i) {
            if (availableClasses.size() == 0) {
                break;
            }

            int randClass = rand() % availableClasses.size();

            AcademicClass* classToAdd = availableClasses.at(randClass);

            availableClasses.erase(availableClasses.begin() + randClass);

            init.at(i).push_back(classToAdd);
        }
    }

    Schedule* schedule = new Schedule(init);

    return schedule;
}

std::vector<ClassPairWithFrequency> searchForClassPairs(const std::vector<ClassPairWithFrequency>& pairs, const AcademicClass* classPointer) {
    std::vector<ClassPairWithFrequency> result;

    for (ClassPairWithFrequency pair : pairs) {
        if (pair.pair[0] == classPointer || pair.pair[1] == classPointer) {
            result.push_back(pair);
        }
    }
    return result;
}


Schedule* ScheduleGeneration::AnalyzeAndGenerateSchedule(const std::vector<AcademicClass*> classList, unsigned int periodCount, const std::set<StudentPreference>& preferences) {

    if (periodCount > classList.size()) {
        std::cout << "Error: Not enough classes (" << classList.size() << ") to fill " << periodCount << " periods. ";
    }

    std::vector<ClassPairWithFrequency> analyzedPairs;
    if (cache.find(preferences) != cache.end()) {
        analyzedPairs = cache.at(preferences);
    }
    else {
        analyzedPairs = Schedule::analyzePreferences(classList, preferences);
        cache[preferences] = analyzedPairs;
    }

    std::vector<AcademicClass*> availableClasses(classList);

    std::vector<std::vector<AcademicClass*>> init(periodCount);

    int currentPeriod = 0;

    for (ClassPairWithFrequency classPair : analyzedPairs) {
        if (availableClasses.size() == 0) {
            break;
        }

        if (!contains(availableClasses, classPair.pair[0])) continue;
        if (!contains(availableClasses, classPair.pair[1])) continue;

        init.at(currentPeriod % periodCount).push_back(classPair.pair[0]);
        init.at(currentPeriod % periodCount).push_back(classPair.pair[1]);


        removeValFromVector(availableClasses, classPair.pair[0]);
        removeValFromVector(availableClasses, classPair.pair[1]);
        currentPeriod++;

    }

    while (availableClasses.size() > 0) {
        for (int i = periodCount - 1; i > -1; --i) {
            if (availableClasses.size() == 0) {
                break;
            }

            int randClass = rand() % availableClasses.size();

            AcademicClass* classToAdd = availableClasses.at(randClass);

            availableClasses.erase(availableClasses.begin() + randClass);

            init.at(i).push_back(classToAdd);
        }
    }

    Schedule* schedule = new Schedule(init);

    return schedule;


}