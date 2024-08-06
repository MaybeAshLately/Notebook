#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <string>
#include <vector>
#include <cctype>
#include <fstream>

class Encryptor
{
    const int size=91;
    const char startChar=32;
    const char endChar=122;
    std::vector<std::vector<char>> alphabetTable;
    std::vector<std::string> buffer;

    void createAlphabetMatrix();
    std::string createFullLengthKey(std::string text,std::string key);
    std::string encryptLine(std::string plaintext,std::string key);
    std::string createReversedKey(std::string key);
    int getLetterNum(char letter);
    char getChar(int num);
    void readFromFile(std::fstream& file);
    
    
    
    public:
    Encryptor(){createAlphabetMatrix();}

    void encrypt(std::string fileName,std::string key);
    void  decrypt(std::string fileName, std::string key);
};


#endif