#include <vector>

#include "AcademicClass.h"
#include "Student.h"

class ClassSection {
    public:
        ClassSection(AcademicClass* Class, int maxPeople, std::vector<Student*> currentStudents);
        void addStudent(Student* student);
        void removeStudent(Student* student);
        int size();
        bool canAddStudent();
    private:
        AcademicClass* Class;
        int maxPeople;
        std::vector<Student*> currentStudents;
};