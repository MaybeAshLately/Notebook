#include "Encryptor.h"

std::string Encryptor::createFullLengthKey(const std::string& text,const std::string& key)
{
    std::string answer="";
    int j=0;
    for(size_t i=0;i<text.size();++i)
    {
        if((text.at(i)>=startChar)and(text.at(i)<=endChar))
        {
            answer+=key.at(j);
            if(j+1<key.size()) ++j;
            else j=0;
        }
        else answer+=text.at(i);
    } 
    return answer;
}

std::string Encryptor::encryptLine(const std::string& plaintext,const std::string& key)
{
    std::string answer;
    for(size_t i=0;i<plaintext.size();++i)
    {
        if((plaintext.at(i)>=startChar)and(plaintext.at(i)<=endChar))
        {
           int row=plaintext.at(i)-startChar;
           int col=key.at(i)-startChar;
           answer=answer+alphabetTable.at(row).at(col);   
        }
        else answer+=plaintext.at(i);
    }
    return answer;
}

void Encryptor::readFromFile(std::fstream& file)
{
    buffer.clear();
    std::string line;
    while(std::getline(file,line)) buffer.push_back(line);
}


void Encryptor::encrypt(const std::string& fileName,const std::string& key)
{

    std::fstream file(fileName,std::ios::in);
    if(!file) return;
    readFromFile(file);
    file.close();
        
    std::vector<std::string> fullKey;

    for(size_t i=0;i<buffer.size();++i)
    {
        std::string fullKeyLine=createFullLengthKey(buffer.at(i),key);
        fullKey.push_back(fullKeyLine);
    }

    std::vector<std::string> encryptedText;

    for(size_t i=0;i<buffer.size();++i)
    {
        std::string encryptedLine=encryptLine(buffer.at(i),fullKey.at(i));
        encryptedText.push_back(encryptedLine);
    }

    file.open(fileName,std::ios::out);
    if(!file) return;
    
    for(size_t i=0;i<encryptedText.size();++i) file<<encryptedText.at(i)<<std::endl;
    file.close();
}

int Encryptor::getLetterNum(const char& letter) const
{
    if((letter>=startChar)and(letter<=endChar)) return letter-startChar;
    return -1;
}

char Encryptor::getChar(const int& num) const
{   
    if((num>=0)and(num<=90)) return startChar+num;
    return ' ';  
}

std::string Encryptor::createReversedKey(const std::string& key) const
{
    std::string answer="";
    
    for(size_t i=0;i<key.size();++i)
    {
        if((key.at(i)>=startChar)and(key.at(i)<=endChar))
        {
            answer=answer+getChar((91-getLetterNum(key.at(i)))%91);
        }
        else answer+=key.at(i);
    }
    return answer;
}


void Encryptor::decrypt(const std::string& fileName, const std::string& key)
{
    std::fstream file(fileName,std::ios::in);
    if(!file) return;
    
    readFromFile(file);
    file.close();
     
    std::string reversedKey=createReversedKey(key);

    std::vector<std::string> fullReversedKey;
    for(size_t i=0;i<buffer.size();++i)
    {
        std::string fullReversedKeyLine=createFullLengthKey(buffer.at(i),reversedKey);
        fullReversedKey.push_back(fullReversedKeyLine);
    }

    std::vector<std::string> decryptedText;

    for(size_t i=0;i<buffer.size();++i)
    {
        std::string decryptedLine=encryptLine(buffer.at(i),fullReversedKey.at(i));
        decryptedText.push_back(decryptedLine);
    }

    file.open(fileName,std::ios::out);
    if(!file) return;
    
    for(size_t i=0;i<decryptedText.size();++i) file<<decryptedText.at(i)<<std::endl;
    file.close();
}


void Encryptor::createAlphabetMatrix()
{
    for (int i=0; i<size; ++i) 
    {
        alphabetTable.push_back(std::vector<char>());
        for (int j=0; j<size; ++j) 
        {
            alphabetTable.at(i).push_back(' ');
            alphabetTable.at(i).at(j)= startChar + (i+j)%size;
        }
    }
}