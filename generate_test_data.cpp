#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> loadClasses(const std::string& path) {
    std::ifstream inputFile(path);

    std::vector<std::string> classes;

    if (!inputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    while (inputFile.good()) {
        std::string className;
        inputFile >> className;

        classes.push_back(className);
    }

    if (!inputFile.eof()) {
        std::cout << "Error reading file " << path << std::endl;
    }

    inputFile.close();

    return classes;

}

std::vector<std::string> generateStudents(const std::string& path, int numStudents) {
    std::ifstream inputFile;

    inputFile.open(path);

    if (!inputFile.is_open()) {
        std::cout << "Failed to open file " << path << std::endl;
    }

    std::vector<std::string> names;

    std::string name;

    while (inputFile >> name) {
        names.push_back(name);
    }

    if (inputFile.bad()) {
        std::cout << "Error reading file " << path << std::endl;
    }

    std::vector<std::string> students;

    for (int i = 0; i < numStudents; ++i) {
        int pos = rand() % names.size();
        std::string name = names.at(pos);

        std::ostringstream student;
        student << name << " " << (rand() % 201) - 100;
        students.push_back(student.str());

        names.erase(names.begin() + pos);
    }

    return students;

}


int main() {
    srand(time(nullptr));

    int numStudents;
    std::cout << "How many students are in the class: ";
    std::cin >> numStudents;

    std::vector<std::string> students = generateStudents("Students.txt", numStudents);

    int classesPerStudent;
    std::cout << "How many classes does each student want to take: ";
    std::cin >> classesPerStudent;

    std::vector<std::string> possibleClasses = loadClasses("Classes.txt");

    if (classesPerStudent > possibleClasses.size()) {
        std::cout << "Error! There aren't " << classesPerStudent << " classes for people to take!" << std::endl;
    }

    std::string outputPath = "Preferences.txt";
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        std::cout << "Failed to open file " << outputPath << std::endl;
    }

    outputFile << classesPerStudent << std::endl;

    for (int i = 0; i < numStudents; ++i) {
        outputFile << students.at(i) << " ";
        for (int j = 0; j < classesPerStudent; ++j) {
            int i = random() % possibleClasses.size();
            outputFile << possibleClasses.at(i) << " ";
            possibleClasses.erase(possibleClasses.begin() + i);
        }
        outputFile << std::endl;
        possibleClasses = loadClasses("Classes.txt");
    }

    outputFile.close();

}