#include "Note.h"

void Note::encryptNote()
{
    std::string key="";
    std::cout<<"Please insert key:"<<std::endl;
    std::getline(std::cin,key);
    encryptor.encrypt(fullDirectory,key);
}

void Note::decryptNote()
{
    std::string key="";
    std::cout<<"Please insert key:"<<std::endl;
    std::getline(std::cin,key);
    encryptor.decrypt(fullDirectory,key);

}

void Note::openFile()
{
    system("cls");
    decryptNote();
    system("cls");

    std::ifstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to abort."<<std::endl;
    else
    {
        std::cout<<"File opened sucessfully! Type \":exit\" to exit."<<std::endl;
        std::cout<<"------------------------------------------------"<<std::endl;
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;  
        std::cout<<"------------------------------------------------"<<std::endl<<std::endl;
    }

    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    file.close();
    encryptNote();
    commandBuffer="";
}

bool Note::checkIfNameCorrect(std::string newFileName)
{
    for(size_t i=0;i<newFileName.size();++i)
    {
        if((std::isalnum(newFileName.at(i))==false)and(newFileName.at(i)!='.')) return false;
    }
    return true;
}

void Note::createFile(std::string newFileName)
{
   if(checkIfNameCorrect(newFileName)==false)
   {
        std::cout<<"File name can contain only letters and numbers. Type \":ack\" to acknowledge."<<std::endl;
        while(commandBuffer!=":ack") std::getline(std::cin,commandBuffer);
        return;
   }

    fileName=newFileName;
    fullDirectory=directory+fileName;

    std::ofstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot create file. Type \":exit\" to abort."<<std::endl;
    else
    {
        system("cls");
        std::cout<<"New file was created succesfully!"<<std::endl;
        std::cout<<"You can write to file. Type \":save\" to save and exit the file"<<std::endl;
        std::cout<<"---------------------------------------------------------------"<<std::endl;
    }

    while(commandBuffer!=":save")
    {
        std::getline(std::cin,commandBuffer);
        if(commandBuffer!=":save")file<<commandBuffer<<std::endl;
    }
    file.close();

    encryptNote();

    commandBuffer="";
}


void Note::clearFile()
{
    std::ofstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot clear file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File cleared sucessfully!. Type \":exit\" to go back"<<std::endl;
    }
    file.close();
    
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    } 
    commandBuffer="";
}


void Note::writeToFile()
{
    system("cls");
    decryptNote();
    system("cls");

    std::fstream file(fullDirectory,std::ios::in);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File opened sucessfully!. You can write changes at the end of file."<<std::endl;
        std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
        std::cout<<"------------------------------------------------------------------"<<std::endl;
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;
    }
    std::cout<<"------------------------------------------------------------------"<<std::endl;
    file.close();

    std::vector<std::string> newLines;
    while((commandBuffer!=":exit")and(commandBuffer!=":save"))
    {
        std::getline(std::cin,commandBuffer);
        if((commandBuffer!=":exit")and(commandBuffer!=":save")) newLines.push_back(commandBuffer);
    }

    if(commandBuffer==":save")
    {
      file.open(fullDirectory, std::ios::out|std::ios::app);
      if(!file)
      {
        std::cout<<"Error, cannot save file. Type \":exit\" to go back"<<std::endl;
        while(commandBuffer!=":exit") std::getline(std::cin,commandBuffer);
      } 
      else 
      {
        for(size_t i=0;i<newLines.size();++i) file<<newLines.at(i)<<std::endl;
        file.close();
      }
    }
    encryptNote();
    commandBuffer="";
}


void Note::deleteFile()
{
    system("cls");
    std::cout<<"Are you sure you want to delete "<<fileName<<" (:yes/:no)?"<<std::endl;
    
    while((commandBuffer!=":no")and(commandBuffer!=":yes")) std::getline(std::cin,commandBuffer);
    
    if(commandBuffer==":yes")
    {
      const char *fileChar = fullDirectory.c_str(); 

      int result=remove(fileChar);    
      if(result==0) std::cout<<"File deleted succesfully! Type \":exit\" to go back."<<std::endl;
      else std::cout<<"Error. Cannot delete file."<<std::endl;
    }
    else std::cout<<"Canceled. Type \":exit\" to go back."<<std::endl;
    
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }   
    commandBuffer="";
}


void Note::displayEditInfo(std::fstream& file, std::vector<std::string>& fileLinesBuffer)
{
    std::cout<<"File opened sucessfully! You can:"<<std::endl;
    std::cout<<"A. Edit line with \":edit number_of_line\" command,"<<std::endl;
    std::cout<<"B. Insert line with \":insert number_of_line\" command (after said line)."<<std::endl;
    std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
    std::cout<<"------------------------------------------------------------------"<<std::endl;
        
    std::string buffer;
    while(std::getline(file,buffer)) fileLinesBuffer.push_back(buffer);
    for(size_t i=0;i<fileLinesBuffer.size();++i) std::cout<<(i+1)<<" "<<fileLinesBuffer.at(i)<<std::endl;
    std::cout<<"------------------------------------------------------------------"<<std::endl;
    std::cout<<std::endl;
}

void Note::handleEditCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer)
{
    commandBuffer.erase(commandBuffer.begin(),commandBuffer.begin()+6);
    std::string num=commandBuffer;
    if(isNumber(num)==false) std::cout<<"Error. Please ensure that you use the correct command."<<std::endl;
    else
    {
        int location=std::stoi(num);
        if(location<0) location=0;
        else if(location>fileLinesBuffer.size()) location=fileLinesBuffer.size()-1;

        std::cout<<"Type the line you want to edit."<<std::endl;
        std::cout<<"--------------------------------------------------------------------------"<<std::endl;

        std::getline(std::cin,commandBuffer);
        fileLinesBuffer.at(location-1)=commandBuffer;
        
        system("cls");
        displayEditInfo(file,fileLinesBuffer);
    } 

}

void Note::handleInsertCommand(std::fstream& file, std::vector<std::string>& fileLinesBuffer)
{
    commandBuffer.erase(commandBuffer.begin(),commandBuffer.begin()+8);
    std::string num=commandBuffer;
    if(isNumber(num)==false) std::cout<<"Error. Please ensure that you use the correct command."<<std::endl;
    else
    {
        int location=std::stoi(num);
        if(location<0) location=0;
        else if(location>fileLinesBuffer.size()) location=fileLinesBuffer.size()-1;

        std::cout<<"Type the line/lines you want to insert. You can stop with \":ok\" command."<<std::endl;
        std::cout<<"--------------------------------------------------------------------------"<<std::endl;
        while(commandBuffer!=":ok")
        {
            std::getline(std::cin,commandBuffer);
            if(commandBuffer!=":ok")
            {
                fileLinesBuffer.insert(fileLinesBuffer.begin()+location,commandBuffer);
                ++location;
            }
            else
            {
                system("cls");
                displayEditInfo(file,fileLinesBuffer);
            }  
        }
    } 
}

void Note::editFile()
{
    system("cls");
    decryptNote();
    system("cls");

    std::vector<std::string> fileLinesBuffer;
    std::fstream file(fullDirectory,std::ios::in);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        displayEditInfo(file,fileLinesBuffer);

        while((commandBuffer!=":exit")and(commandBuffer!=":save"))
        {
           std::getline(std::cin,commandBuffer);
           if((commandBuffer.size()>=5)and(commandBuffer.compare(0,5,":edit")==0))
           {
            handleEditCommand(file,fileLinesBuffer);
           }
           else if((commandBuffer.size()>=7)and(commandBuffer.compare(0,7,":insert")==0))
           {
            handleInsertCommand(file,fileLinesBuffer);
           }
        }

        if(commandBuffer==":save")
        {
            std::ofstream file(fullDirectory);
            if(!file) std::cout<<"Error, cannot save file. Type \":exit\" to go back"<<std::endl;
            else 
            {
              for(size_t i=0;i<fileLinesBuffer.size();++i) file<<fileLinesBuffer.at(i)<<std::endl;
              std::cout<<"Changes saved succesfully! Type \":exit\" to go back."<<std::endl;
            }
            file.close();
        }
    }

    while(commandBuffer!=":exit") std::getline(std::cin,commandBuffer);

    file.close();
    encryptNote();
    commandBuffer="";
}


bool Note::isNumber(std::string txt)
{
    for(size_t i=0;i<txt.size();++i)
    {
        if(std::isdigit(txt.at(i))==false) return false;
    }
    return true;
}