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
    const std::string directory;
    std::vector<std::string> filesNames;
    std::string commandBuffer;

    void getFilesInDirectory();
    void displayHelp();
    bool checkIfFileExist(std::string command);
    void openFile(std::string command);
    void createFile(std::string command);
    void clearFile(std::string fileName);
    void writeToFile(std::string fileName);
    void deleteFile(std::string fileName);
    void editFile(std::string fileName);
    std::string extractFileNameFromCommand(std::string command, int number);
    bool isNumber(std::string txt);
    public:
    Manager();

    void display();
};

#endif