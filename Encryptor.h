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

    std::string createFullLengthKey(const std::string& text,const std::string& key);
    std::string encryptLine(const std::string& plaintext,const std::string& key);
    std::string createReversedKey(const std::string& key) const;
    int getLetterNum(const char& letter) const;
    char getChar(const int& num) const;
    void readFromFile(std::fstream& file);
    
    
    public:
    Encryptor(){createAlphabetMatrix();}

    void encrypt(const std::string& fileName, const std::string& key);
    void  decrypt(const std::string& fileName, const std::string& key);
};

#endif