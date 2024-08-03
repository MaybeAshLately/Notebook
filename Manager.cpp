#include "Manager.h"
Manager::Manager(): directory("../../../Notes/")
{
    getFilesInDirectory();
    commandBuffer="";
}

void Manager::getFilesInDirectory()
{
    filesNames.clear();
    for(const auto & i: std::filesystem::directory_iterator(directory))
    {
        filesNames.push_back(i.path().filename().string());
    }
}

std::string Manager::extractFileNameFromCommand(std::string command, int number)
{
    command.erase(command.begin(),command.begin()+number);
    return command;
}

void Manager::display()
{
    system("cls");
    std::cout<<"Welcome in Notebook!"<<std::endl;
    std::cout<<"For help write \":help\""<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<filesNames.size();++i)
    {
        std::cout<<filesNames.at(i)<<" ";
    }
    std::cout<<std::endl<<std::endl;
  
        
        
    while(commandBuffer!=":end")
    {
        std::getline(std::cin,commandBuffer);
        if(commandBuffer==":help") displayHelp();
        else if((commandBuffer.size()>=5)and(commandBuffer.compare(0,5,":open")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,6);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else openFile(fileName);
        }
        else if((commandBuffer.size()>=7)and(commandBuffer.compare(0,7,":create")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,8);
            if(checkIfFileExist(fileName)==true)  std::cout<<"This file already exist. You can open it with \":open\" command."<<std::endl;
            else createFile(fileName);
        }
        else if((commandBuffer.size()>=6)and(commandBuffer.compare(0,6,":clear")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,7);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file."<<std::endl;
            else clearFile(fileName);
        }
        else if((commandBuffer.size()>=6)and(commandBuffer.compare(0,6,":write")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,7);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else writeToFile(fileName);
        }
        else if((commandBuffer.size()>=7)and(commandBuffer.compare(0,7,":delete")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,8);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file."<<std::endl;
            else deleteFile(fileName);
        }
        else if((commandBuffer.size()>=5)and(commandBuffer.compare(0,5,":edit")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,6);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else editFile(fileName);
        }
        else if(commandBuffer!=":end")
        {
            std::cout<<"Command unrecognized. You can display list of commands with \":help\"."<<std::endl;
        }
    }
}



void Manager::displayHelp()
{
    constexpr int size=20;
    system("cls");
    std::cout<<std::left;
    std::cout<<std::setw(size)<<":create file.txt"<<"Creates file.txt (if it does not exist already)"<<std::endl;
    std::cout<<std::setw(size)<<":delete file.txt"<<"Deletes file.txt (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<":edit file.txt"<<"Opens file.txt in edit mode (if it have not existed creates it). You can modify the content."<<std::endl;
    std::cout<<std::setw(size)<<":end"<<"Ends program"<<std::endl;
    std::cout<<std::setw(size)<<":exit"<<"Exits manual/file (in modify mode without saving changes)"<<std::endl;
    std::cout<<std::setw(size)<<":help"<<"Displays manual"<<std::endl;
    std::cout<<std::setw(size)<<":open file.txt"<<"Opens file.txt in read only mode (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<":save"<<"Save changes in current file and exits"<<std::endl;
    std::cout<<std::setw(size)<<":write file.txt"<<"Opens file.txt in write mode (if it have not existed creates it). You can write new content at the end of file."<<std::endl;
    std::cout<<std::endl;

    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    display();

}

bool Manager::checkIfFileExist(std::string fileName)
{
    if(std::find(filesNames.begin(),filesNames.end(),fileName)==filesNames.end()) return false;
    return true;
}


void Manager::openFile(std::string fileName)
{
    system("cls");
    fileName=directory+fileName;
    std::ifstream file(fileName);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to abort."<<std::endl;
    else
    {
        std::cout<<"File opened sucessfully! Type \":exit\" to exit."<<std::endl;
        std::cout<<"------------------------------------------------"<<std::endl<<std::endl;
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;  
        std::cout<<std::endl; 
    }


    
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    file.close();
    display();
}



void Manager::createFile(std::string fileName)
{
    fileName=directory+fileName;

    std::ofstream file(fileName);
    if(!file) std::cout<<"Error, cannot create file. Type \":exit\" to abort."<<std::endl;
    else
    {
        system("cls");
        std::cout<<"New file was created succesfully!"<<std::endl;
        std::cout<<"You can write to file. Type \":exit\" to save and exit the file"<<std::endl;
        std::cout<<"---------------------------------------------------------------"<<std::endl;
        std::cout<<std::endl;
    }

    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
        if(commandBuffer!=":exit")file<<commandBuffer<<std::endl;
    }
    file.close();
    getFilesInDirectory();
    display();
}


void Manager::clearFile(std::string fileName)
{
    fileName=directory+fileName;

    std::ofstream file(fileName);
    if(!file) std::cout<<"Error, cannot clear file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File cleared sucessfully!. Type \":exit\" to go back"<<std::endl;
    }

    
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    
    file.close();
    display();
}



void Manager::writeToFile(std::string fileName)
{
    system("cls");

    fileName=directory+fileName;

    std::fstream file(fileName,std::ios::in);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File opened sucessfully!. You can write changes at the end of file."<<std::endl;
        std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
        std::cout<<"------------------------------------------------------------------"<<std::endl<<std::endl;
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;
    }
    file.close();

    std::vector<std::string> newLines;
    while((commandBuffer!=":exit")and(commandBuffer!=":save"))
    {
        std::getline(std::cin,commandBuffer);
        if((commandBuffer!=":exit")and(commandBuffer!=":save")) newLines.push_back(commandBuffer);
    }

    if(commandBuffer==":save")
    {
      file.open(fileName, std::ios::out|std::ios::app);
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

    display();
}



void Manager::deleteFile(std::string fileName)
{
    system("cls");
    std::cout<<"Are you sure you want to delete "<<fileName<<" (:yes/:no)?"<<std::endl;
    
    while((commandBuffer!=":no")and(commandBuffer!=":yes"))
    {
        std::getline(std::cin,commandBuffer);
    }

    if(commandBuffer==":yes")
    {
      fileName=directory+fileName;
      const char *fileChar = fileName.c_str(); 

      int result=remove(fileChar);    
      if(result==0) std::cout<<"File deleted succesfully! Type \":exit\" to go back."<<std::endl;
      else std::cout<<"Error. Cannot delete file."<<std::endl;
    }
    else std::cout<<"Canceled. Type \":exit\" to go back."<<std::endl;


    
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    
    getFilesInDirectory();
    display();
}


void Manager::editFile(std::string fileName)
{
    system("cls");

    fileName=directory+fileName;

    
    std::vector<std::string> fileLinesBuffor;
    std::fstream file(fileName,std::ios::in);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File opened sucessfully! You can:"<<std::endl;
        std::cout<<"A. Edit line with \":edit number_of_line\" command,"<<std::endl;
        std::cout<<"B. Insert line with \":insert number_of_line\" command (after said line)."<<std::endl;
        std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
        std::cout<<"------------------------------------------------------------------"<<std::endl<<std::endl;
        
        std::string buffor;
        while(std::getline(file,buffor)) fileLinesBuffor.push_back(buffor);
        for(size_t i=0;i<fileLinesBuffor.size();++i) std::cout<<(i+1)<<" "<<fileLinesBuffor.at(i)<<std::endl;
        std::cout<<std::endl;


        while((commandBuffer!=":exit")and(commandBuffer!=":save"))
        {
           std::getline(std::cin,commandBuffer);
           if((commandBuffer.size()>=5)and(commandBuffer.compare(0,5,":edit")==0))
           {
            commandBuffer.erase(commandBuffer.begin(),commandBuffer.begin()+6);
            std::string num=commandBuffer;
            if(isNumber(num)==false) std::cout<<"Error. Please ensure that you use the correct command."<<std::endl;
            else
            {
                int location=std::stoi(num);
                std::cout<<"Type the line you want to edit."<<std::endl;
                std::cout<<"--------------------------------------------------------------------------"<<std::endl;
            
                std::getline(std::cin,commandBuffer);
                fileLinesBuffor.at(location+1)=commandBuffer;
          
                    system("cls");
                     std::cout<<"File opened sucessfully! You can:"<<std::endl;
                     std::cout<<"A. Edit line with \":edit number_of_line\" command,"<<std::endl;
                     std::cout<<"B. Insert line with \":insert number_of_line\" command (after said line)."<<std::endl;
                     std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
                     std::cout<<"------------------------------------------------------------------"<<std::endl<<std::endl;
        
                     std::string buffor;
                     while(std::getline(file,buffor)) fileLinesBuffor.push_back(buffor);
                     for(size_t i=0;i<fileLinesBuffor.size();++i) std::cout<<(i+1)<<" "<<fileLinesBuffor.at(i)<<std::endl;
                     std::cout<<std::endl;
            } 
           }
           else if((commandBuffer.size()>=7)and(commandBuffer.compare(0,7,":insert")==0))
           {
            commandBuffer.erase(commandBuffer.begin(),commandBuffer.begin()+8);
            std::string num=commandBuffer;
            if(isNumber(num)==false) std::cout<<"Error. Please ensure that you use the correct command."<<std::endl;
            else
            {
                int location=std::stoi(num);
                std::cout<<"Type the line/lines you want to insert. You can stop with \":ok\" command."<<std::endl;
                std::cout<<"--------------------------------------------------------------------------"<<std::endl;
                while(commandBuffer!=":ok")
                {
                  std::getline(std::cin,commandBuffer);
                  if(commandBuffer!=":ok")
                  {
                    fileLinesBuffor.insert(fileLinesBuffor.begin()+location,commandBuffer);
                    ++location;
                  }
                  else
                  {
                    system("cls");
                     std::cout<<"File opened sucessfully! You can:"<<std::endl;
                     std::cout<<"A. Edit line with \":edit number_of_line\" command,"<<std::endl;
                     std::cout<<"B. Insert line with \":insert number_of_line\" command (after said line)."<<std::endl;
                     std::cout<<"Type \":save\" to save changes or \":exit\" to exit without saving."<<std::endl;
                     std::cout<<"------------------------------------------------------------------"<<std::endl<<std::endl;
        
                     std::string buffor;
                     while(std::getline(file,buffor)) fileLinesBuffor.push_back(buffor);
                     for(size_t i=0;i<fileLinesBuffor.size();++i) std::cout<<(i+1)<<" "<<fileLinesBuffor.at(i)<<std::endl;
                     std::cout<<std::endl;
                  }  
                }
            } 
           }
        }

        if(commandBuffer==":save")
        {
            std::ofstream file(fileName);
            if(!file) std::cout<<"Error, cannot save file. Type \":exit\" to go back"<<std::endl;
            else 
            {
              for(size_t i=0;i<fileLinesBuffor.size();++i) file<<fileLinesBuffor.at(i)<<std::endl;
              std::cout<<"Changes saved succesfully! Type \":exit\" to go back."<<std::endl;
            }
            file.close();

        }



    }

    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }


    file.close();
    display();
}

bool Manager::isNumber(std::string txt)
{
    for(size_t i=0;i<txt.size();++i)
    {
        if(std::isdigit(txt.at(i))==false) return false;
    }
    return true;
}