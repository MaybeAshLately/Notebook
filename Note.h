#ifndef NOTE_H
#define NOTE
#include <string>

class Note
{
    const std::string file;

    bool createAndOpenFile(){return false;}
    public:
    Note()=delete;
    Note(std::string fileName): file(fileName)
    {

    } 

    bool openFile(){return false;}
    bool closeFile(){return false;}
    bool eraseFile(){return false;}
    bool deleteFile(){return false;}
    void saveToFile(){}

};

#endif