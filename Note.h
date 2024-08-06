#ifndef NOTE_H
#define NOTE
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Encryptor.h"

class Note
{
    Encryptor encryptor;
    const std::string directory;
    std::string fileName;
    std::string fullDirectory;
    std::string commandBuffer;

    bool isNumber(const std::string& txt) const;
    bool checkIfNameCorrect(const std::string& newFileName) const;
    void displayEditInfo(std::fstream& file, std::vector<std::string>& fileLinesBuffer);
    void handleEditCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer);
    void handleInsertCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer);
    void handleEraseCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer);

    void encryptNote();
    void decryptNote();

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
    void createFile(const std::string& newfileName);
    void clearFile();
    void writeToFile();
    void deleteFile();
    void editFile();

    std::string getName() const {return fileName;}
};

#endif