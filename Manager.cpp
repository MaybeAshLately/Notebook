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
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \"create\" command."<<std::endl;
            else openFile(fileName);
        }
        else if((commandBuffer.size()>=7)and(commandBuffer.compare(0,7,":create")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,8);
            if(checkIfFileExist(fileName)==true)  std::cout<<"This file already exist. You can open it with \"open\" command."<<std::endl;
            else createFile(fileName);
        }
        else if((commandBuffer.size()>=6)and(commandBuffer.compare(0,6,":clear")==0))
        {
            std::string fileName=extractFileNameFromCommand(commandBuffer,7);
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file."<<std::endl;
            else clearFile(fileName);
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
    std::cout<<std::setw(size)<<":end"<<"Ends program"<<std::endl;
    std::cout<<std::setw(size)<<":exit"<<"Exits manual/file (in modify mode without saving changes)"<<std::endl;
    std::cout<<std::setw(size)<<":help"<<"Displays manual"<<std::endl;
    std::cout<<std::setw(size)<<":modify file.txt"<<"Opens file.txt in modify mode (if it have not existed creates it)"<<std::endl;
    std::cout<<std::setw(size)<<":open file.txt"<<"Opens file.txt in read only mode (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<":save"<<"Save changes in current file and exits"<<std::endl;
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