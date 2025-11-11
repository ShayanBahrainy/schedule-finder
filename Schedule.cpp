#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>

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

int Schedule::score(const std::vector<StudentPreference>& preferences) {
    int score = 0;

    for (auto& pref : preferences) {
        for (auto& period : schedule) {
            int collisions = -1;
            for (auto& academicClass : period) {
                if (pref.contains(*academicClass)) {
                    collisions++;
                }
            }
            score += std::max(collisions, 0);
        }
    }

    return score;
}




std::vector<ClassPairWithFrequency> Schedule::analyzePreferences(const std::vector<AcademicClass*>& classes, const std::vector<StudentPreference>& preferences) {

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



    std::vector<ClassPairWithFrequency> pairs;

    for ( std::pair<AcademicClass*, Counter<AcademicClass*>> pair : connected) {
        std::vector<ObjectWithFrequency<AcademicClass*>> pairedClasses = pair.second.getSorted();

        for (ObjectWithFrequency<AcademicClass*>& obj : pairedClasses) {
            pairs.push_back(ClassPairWithFrequency{std::vector<AcademicClass*>{pair.first, obj.t}, obj.frequency});
        }
    }

    std::sort(pairs.begin(), pairs.end());

    return pairs;

}