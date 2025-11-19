#include "AcademicClass.h"
#include "StudentPreference.h"

#include <set>
#include <vector>

void performSearch(bool smart, const int SEARCH_COUNT, const int PERIOD_COUNT, const std::vector<AcademicClass*>& academicClasses, const std::set<StudentPreference>& studentPrefs);

void performGeneticSearch( const int PERIOD_COUNT, const std::vector<AcademicClass*>& academicClasses, const std::set<StudentPreference>& studentPrefs);
