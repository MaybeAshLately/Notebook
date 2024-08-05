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

    std::vector<Note> files;
    void handleCommand(std::string command, std::string file);
    std::vector<Note>::iterator findFile(std::string fileName);

    void intro();
    void getFilesInDirectory();
    void displayHelp();
    bool checkIfFileExist(std::string command);
    void displayFiles();

    void openFile(std::string command);
    void createFile(std::string command);
    void clearFile(std::string fileName);
    void writeToFile(std::string fileName);
    void deleteFile(std::string fileName);
    void editFile(std::string fileName);

    std::string extractFileNameFromCommand(std::string wholeCommand, std::string command);
    std::string extractCommandNameFromCommand(std::string command);
    bool isNumber(std::string txt);
    public:
    Manager();

    void display();
};

#endif