#ifndef NOTE_H
#define NOTE
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Encryptor.h"

class Note
{
    const std::string directory;
    std::string fileName;
    std::string fullDirectory;
    std::string commandBuffer;

    bool isNumber(std::string txt);
    bool checkIfNameCorrect(std::string newFileName);
    void displayEditInfo(std::fstream& file, std::vector<std::string>& fileLinesBuffer);
    void handleEditCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer);
    void handleInsertCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer);



    public:
    Note()=delete;
    Note(std::string directory): directory(directory)
    {
        fileName="";
        fullDirectory="";
        commandBuffer="";
    }

    Note(std::string directory, std::string newFileName ): directory(directory)
    {
        commandBuffer="";
        fileName=newFileName;
        fullDirectory=directory+fileName;
    }

    void openFile();
    void createFile(std::string newfileName);
    void clearFile();
    void writeToFile();
    void deleteFile();
    void editFile();

    std::string getName(){return fileName;}
};

#endif