#include "Search.h"
#include "StudentPreference.h"
#include "generate_schedule.h"

#include <chrono>
#include <cstdlib>
#include <limits>
#include <iostream>

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
        //No use printing starting value
        if (i % 100000 == 0 && i != 1) {
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
            while (r < 25) {
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


int getMaxIndex(const std::vector<Schedule*>& schedules, const std::set<StudentPreference>& studentPrefs) {
    int maxScore = std::numeric_limits<int>::min();
    int index = -1;
    for (size_t i = 0; i < schedules.size(); ++i) {
        int score = schedules.at(i)->score(studentPrefs);
        if (score > maxScore) {
            maxScore = score;
            index = i;
        }
    }
    return index;
}

void performGeneticSearch(const int PERIOD_COUNT, const std::vector<AcademicClass*>& academicClasses, const std::set<StudentPreference>& studentPrefs) {
    std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();

    Schedule* minSchedule;
    int minScore = std::numeric_limits<int>::max();

    std::vector<Schedule*> pool;

    //Initialize pool
    for (int i = 0; i < 100; ++i) {
        Schedule* schedule = ScheduleGeneration::generateRandomSchedule(academicClasses, PERIOD_COUNT);
        pool.push_back(schedule);
    }

    for (int i = 0; i < 1000; ++i) {
        int parentOne = rand() % pool.size();
        int parentTwo = rand() % pool.size();

        while (parentOne == parentTwo) {
            parentTwo = rand() % pool.size();
        }

        Schedule* child = pool.at(parentOne)->breed(pool.at(parentTwo), academicClasses);

        int worst = getMaxIndex(pool, studentPrefs);

        delete pool.at(worst);

        pool.erase(pool.begin() + worst);

        pool.push_back(child);

    }

    for (size_t i = 0; i < pool.size(); ++i) {
        int score = pool.at(i)->score(studentPrefs);
        if (score < minScore) {
            minSchedule = pool.at(i);
            minScore = score;
        }
    }

    std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();


    std::cout << "Here is a schedule: " << *minSchedule << std::endl;

    std::cout << "And it has a score of " << minSchedule->score(studentPrefs) << std::endl;

    int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "That took " << (int) (milliseconds/1000 )<< " seconds." << std::endl;

    std::cout << "This was a genetic search" << std::endl;

}