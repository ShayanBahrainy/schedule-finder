#include <string>


#pragma  once
class Student {
    public:
        Student(std::string name, int grade);

        std::string getName();

        int getGrade();
    private:
        std::string name;
        int grade;
};
