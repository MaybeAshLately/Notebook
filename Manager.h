#ifndef MANAGER_H
#define MANAGER_H
#include "Note.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <iomanip>
#include <algorithm>


class Manager
{
    const std::string directory;
    std::vector<Note> files;
    std::string commandBuffer;


    void handleCommand(std::string command, std::string file);
    
    std::string extractFileNameFromCommand(std::string wholeCommand, std::string command);
    std::string extractCommandNameFromCommand(std::string command);

    void intro();
    void getFilesInDirectory();
    void displayFiles();
    bool checkIfFileExist(std::string command);
    void displayHelp();

    std::vector<Note>::iterator findFile(std::string fileName);
    void openFile(std::string fileName);
    void createFile(std::string fileName);
    void clearFile(std::string fileName);
    void writeToFile(std::string fileName);
    void deleteFile(std::string fileName);
    void editFile(std::string fileName);
    
    
    public:
    Manager();
    void display();
};

#endif