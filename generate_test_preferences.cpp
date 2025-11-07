#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> loadClasses(const std::string path) {
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


int main() {
    srand(time(nullptr));

    int numStudents;
    std::cout << "How many students are in the class: ";
    std::cin >> numStudents;

    int classesPerStudent;
    std::cout << "How many classes does each student want to take: ";
    std::cin >> classesPerStudent;

    std::vector<std::string> possibleClasses = loadClasses("Classes.txt");

    if (classesPerStudent > possibleClasses.size()) {
        std::cout << "Error! There aren't " << classesPerStudent << " classes for people to take!" << std::endl;
    }

    for (int i = 0; i < numStudents; ++i) {
        for (int j = 0; j < classesPerStudent; ++j) {
            int i = random() % possibleClasses.size();
            std::cout << possibleClasses.at(i) << " ";
            possibleClasses.erase(possibleClasses.begin() + i);
        }
        std::cout << std::endl;
        possibleClasses = loadClasses("Classes.txt");
    }
}