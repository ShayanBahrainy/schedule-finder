#include <ostream>

#include "AcademicClass.h"
#include "StudentPreference.h"


struct ClassPairWithFrequency {
    std::vector<AcademicClass*> pair;
    int frequency;
    bool operator<(ClassPairWithFrequency& otherPair) {
        return frequency < otherPair.frequency;
    }
};

#pragma once
class Schedule {

    public:
        Schedule(const std::vector<std::vector<AcademicClass*>>& initialSchedule);

        std::vector<AcademicClass*> getClasses(unsigned int period);


        int score(const std::vector<StudentPreference>& preferences);

        friend std::ostream& operator<<(std::ostream& os, const Schedule& sched);

        static std::vector<ClassPairWithFrequency> analyzePreferences(const std::vector<AcademicClass*>& classes, const std::vector<StudentPreference>& preferences);
    private:
        std::vector<std::vector<AcademicClass*>> schedule;

};

std::ostream& operator<<(std::ostream& os, const Schedule& sched);