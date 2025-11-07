#include <vector>
#include <iostream>

#include "Schedule.h"
#include "AcademicClass.h"
#include "StudentPreference.h"

std::ostream& operator<<(std::ostream& os, const Schedule& sched) {
    os << std::endl;
    for (unsigned int i = 0; i < sched.schedule.size(); ++i) {
        os << "Period " << i + 1 << ": ";
        const std::vector<AcademicClass>& period = sched.schedule.at(i);
        for (unsigned int j = 0; j < period.size() - 1; ++j) {
            os << period.at(j).getName() << ", ";
        }
        os << "and, " << period.at(period.size() - 1).getName() << std::endl;
    }
    return os;
}

Schedule::Schedule(const std::vector<std::vector<AcademicClass>>& initialSchedule) {
    schedule = initialSchedule;
}

std::vector<AcademicClass> Schedule::getClasses(unsigned int period) {
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
                if (pref.contains(academicClass)) {
                    collisions++;
                }
            }
            score += std::max(collisions, 0);
        }
    }

    return score;
}