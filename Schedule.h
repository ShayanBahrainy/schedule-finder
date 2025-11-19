#include <ostream>
#include <unordered_set>
#include <array>
#include <set>

#include "AcademicClass.h"
#include "StudentPreference.h"


struct ClassPairWithFrequency {
    std::array<AcademicClass*, 2> pair;
    int frequency;
    bool operator<(const ClassPairWithFrequency& otherPair) {
        return frequency < otherPair.frequency;
    }
    bool operator==(const ClassPairWithFrequency& otherPair) const {
        return otherPair.frequency == frequency && (otherPair.pair[0] == pair[0] || otherPair.pair[0] == pair[1]) && (otherPair.pair[1] == pair[1] || otherPair.pair[1] == pair[0]);
    }
    struct HashFunction {
        size_t operator()(const ClassPairWithFrequency& classPair) const {
            size_t xHash = std::hash<AcademicClass*>()(classPair.pair[0]);
            size_t yHash = std::hash<AcademicClass*>()(classPair.pair[1]) << 1;
            return xHash ^ yHash ^ (std::hash<int>()(classPair.frequency) << 2);
        }
    };
};

#pragma once
class Schedule {

    public:
        Schedule(const std::vector<std::vector<AcademicClass*>>& initialSchedule);

        Schedule(const Schedule& other);

        std::vector<AcademicClass*> getClasses(unsigned int period);

        void mutate();

        int score(const std::set<StudentPreference>& preferences);

        Schedule* breed(const Schedule* otherSchedule, std::vector<AcademicClass*> availableClasses);

        static std::vector<ClassPairWithFrequency> analyzePreferences(const std::vector<AcademicClass*>& classes, const std::set<StudentPreference>& preferences);

        friend std::ostream& operator<<(std::ostream& os, const Schedule& sched);

    private:
        std::vector<std::vector<AcademicClass*>> schedule;

};

std::ostream& operator<<(std::ostream& os, const Schedule& sched);