#include <set>

#include "AcademicClass.h"
#include "Schedule.h"
#include "Schedule.h"


namespace ScheduleGeneration {
    Schedule* generateRandomSchedule(const std::vector<AcademicClass*> classList, unsigned int periodCount);

    Schedule* AnalyzeAndGenerateSchedule(const std::vector<AcademicClass*> classList, unsigned int periodCount, const std::set<StudentPreference>& preferences);
}