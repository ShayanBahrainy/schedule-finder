#include <vector>
#include <iostream>

#include "AcademicClass.h"
#include "Schedule.h"
#include "generate_schedule.h"


Schedule* generateRandomSchedule(const std::vector<AcademicClass*> classList, unsigned int periodCount) {

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