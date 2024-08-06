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


    void handleCommand(const std::string& command,const std::string& file);
    
    std::string extractFileNameFromCommand(const std::string& wholeCommand,const std::string& command) const;
    std::string extractCommandNameFromCommand(const std::string& command) const;

    void intro() const;
    void getFilesInDirectory();
    void displayFiles() const;
    bool checkIfFileExist(const std::string& command) const;
    void displayHelp();

    std::vector<Note>::iterator findFile(const std::string& fileName);
    void openFile(const std::string& fileName);
    void createFile(const std::string& fileName);
    void clearFile(const std::string& fileName);
    void writeToFile(const std::string& fileName);
    void deleteFile(const std::string& fileName);
    void editFile(const std::string& fileName);
    
    
    public:
    Manager();
    void display();
};

#endif