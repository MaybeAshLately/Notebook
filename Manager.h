#ifndef MANAGER_H
#define MANAGER_H
#include "Note.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <algorithm>


class Manager
{
    std::string directory;
    std::vector<std::string> filesNames;
    std::string commandBuffer;

    void displayHelp();
    bool checkIfFileExist(std::string command);
    void openFile(std::string command);
    public:
    Manager();

    void display();
};

#endif