#include <cstddef>
#include <unordered_set>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <cstdlib>

#include "Schedule.h"
#include "AcademicClass.h"
#include "StudentPreference.h"
#include "Utils.h"

std::ostream& operator<<(std::ostream& os, const Schedule& sched) {
    os << std::endl;
    for (unsigned int i = 0; i < sched.schedule.size(); ++i) {
        os << "Period " << i + 1 << ": ";
        const std::vector<AcademicClass*>& period = sched.schedule.at(i);

        if (period.size() == 1) {
            std::cout << period.at(0)->getName() << std::endl;
            continue;
        }

        if (period.size() == 0) {
            std::cout << std::endl;
            continue;
        }

        for (unsigned int j = 0; j < period.size() - 1; ++j) {
            os << period.at(j)->getName() << ", ";
        }
        os << "and, " << period.at(period.size() - 1)->getName() << std::endl;
    }
    return os;
}

Schedule::Schedule(const std::vector<std::vector<AcademicClass*>>& initialSchedule) {
    schedule = initialSchedule;
}

std::vector<AcademicClass*> Schedule::getClasses(unsigned int period) {
    if (period >= schedule.size()) {
        std::cout << "Error: " << period << " is not a valid period. (There are " << schedule.size() << " )" << std::endl;
    }

    return schedule.at(period);
}

Schedule::Schedule(const Schedule& other) {
    schedule = std::vector<std::vector<AcademicClass*>>(other.schedule.size());

    for (size_t i = 0; i < schedule.size(); ++i) {
        for (size_t j = 0; j < other.schedule.at(i).size(); ++j) {
            schedule.at(i).push_back(other.schedule.at(i).at(j));
        }
    }
}

void Schedule::mutate() {
    int period = rand() % schedule.size();
    while (schedule.at(period).size() == 0) {
        period = rand() % schedule.size();
    }

    int classIndex = rand() % schedule.at(period).size();

    AcademicClass* classPointer = schedule.at(period).at(classIndex);

    schedule.at(period).erase(schedule.at(period).begin() + classIndex);

    int periodTo = rand() % schedule.size();

    schedule.at(periodTo).push_back(classPointer);
}

int Schedule::score(const std::set<StudentPreference>& preferences) {
    int score = 0;

    for (auto& pref : preferences) {
        for (auto& period : schedule) {
            int collisions = -1;
            for (auto& academicClass : period) {
                if (pref.contains(academicClass)) {
                    collisions++;
                }
            }
            score += std::max(collisions, 0);
        }
    }

    return score;
}

bool isAvailable(const AcademicClass*& classPointer, const std::vector<AcademicClass*>& availableClasses) {
    for (AcademicClass* p : availableClasses) {
        if (classPointer == p) return true;
    }
    return false;
}

Schedule* Schedule::breed(const Schedule& otherSchedule, std::vector<AcademicClass*> availableClasses) {
    if (schedule.size() != otherSchedule.schedule.size()) {
        std::cout << "Error! Attempt to breed schedules with different period counts " << std::endl;
    }

    std::vector<std::vector<AcademicClass*>> init(schedule.size());

    int periodNum = 0;
    while (periodNum < init.size()) {
        for (int i = 0; i < schedule.size(); ++i) {
            bool allAvailable = true;
            for (const AcademicClass* classPointer : schedule.at(i)) {
                if (!isAvailable(classPointer, availableClasses))  {
                    allAvailable = false;
                    break;
                }
            }

            if (allAvailable) {
                for (AcademicClass* classPointer : schedule.at(i)) {
                    removeValFromVector(availableClasses, classPointer);
                }

                //Put this period into the schedule
                init.at(periodNum).insert(init.at(i).begin(), schedule.at(i).begin(), schedule.at(i).end());

                periodNum++;
                break;
            }
        }

        for (int i = 0; i < otherSchedule.schedule.size(); ++i) {
            bool allAvailable = true;
            for (const AcademicClass* classPointer : otherSchedule.schedule.at(i)) {
                if (!isAvailable(classPointer, availableClasses))  {
                    allAvailable = false;
                    break;
                }
            }

            if (allAvailable) {
                for (AcademicClass* classPointer : otherSchedule.schedule.at(i)) {
                    removeValFromVector(availableClasses, classPointer);
                }

                //Put this period into the schedule
                init.at(periodNum).insert(init.at(i).begin(), otherSchedule.schedule.at(i).begin(), otherSchedule.schedule.at(i).end());

                periodNum++;
                break;
            }
        }
    }

    for (int i = 0; i < availableClasses.size(); ++i) {
        init.at(periodNum % init.size()).push_back(availableClasses.at(i));
        availableClasses.erase(availableClasses.begin() + i);

        periodNum++;
    }


    Schedule* child = new Schedule(init);

    return child;
}


std::vector<ClassPairWithFrequency> Schedule::analyzePreferences(const std::vector<AcademicClass*>& classes, const std::set<StudentPreference>& preferences) {

    std::unordered_map<AcademicClass*, Counter<AcademicClass*>> connected;
    for (auto& classPointer : classes) {
        connected[classPointer] = Counter<AcademicClass*>();
    }

    for (const StudentPreference& pref : preferences) {
        for (int i = 0; i < pref.getPreferenceCount(); ++i ) {
            connected[pref.getPreference(i)].add(pref.preferenceList);
        }
    }

    std::vector<std::vector<AcademicClass*>> matches;

    std::unordered_set<ClassPairWithFrequency, ClassPairWithFrequency::HashFunction> pairs;

    for ( std::pair<AcademicClass*, Counter<AcademicClass*>> pair : connected) {
        std::vector<ObjectWithFrequency<AcademicClass*>> pairedClasses = pair.second.getSorted();

        for (ObjectWithFrequency<AcademicClass*>& obj : pairedClasses) {
            if (obj.t == pair.first) {
                continue;
            }

            std::array<AcademicClass*, 2> paired;

            //Some ternaries that will result in a sorted paired
            paired[0] = pair.first < obj.t ? pair.first : obj.t;
            paired[1] = obj.t < pair.first ? pair.first : obj.t;

            ClassPairWithFrequency pairWithFreq = ClassPairWithFrequency{paired, obj.frequency};
            pairs.insert(pairWithFreq);
        }
    }

    std::vector<ClassPairWithFrequency> sortedPairs(pairs.begin(), pairs.end());

    std::sort(sortedPairs.begin(), sortedPairs.end());

    return sortedPairs;

}