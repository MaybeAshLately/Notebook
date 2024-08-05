#ifndef NOTE_H
#define NOTE
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class Note
{
    const std::string directory;
    std::string fileName;

    bool isNumber(std::string txt);

    public:
    Note()=delete;
    Note(std::string directory): directory(directory){fileName="";}

    Note(std::string directory, std::string newFileName ): directory(directory){fileName=newFileName;}



    void openFile();
    void createFile(std::string newfileName);

    void clearFile();

    void writeToFile();
    void deleteFile();
    void editFile();

    std::string getName(){return fileName;}


};

#endif