#include "AcademicClass.h"
#include "StudentPreference.h"
#include <ostream>

#pragma once
class Schedule {

    public:
        Schedule(const std::vector<std::vector<AcademicClass*>>& initialSchedule);

        std::vector<AcademicClass*> getClasses(unsigned int period);


        int score(const std::vector<StudentPreference>& preferences);

        friend std::ostream& operator<<(std::ostream& os, const Schedule& sched);

    private:
        std::vector<std::vector<AcademicClass*>> schedule;

};

std::ostream& operator<<(std::ostream& os, const Schedule& sched);