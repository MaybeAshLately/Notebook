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
        std::string fileBuffer= i.path().filename().string();
        filesNames.push_back(fileBuffer);
        files.push_back(Note(directory,fileBuffer));
    }
}

void Manager::displayFiles()
{
    for(size_t i=0;i<filesNames.size();++i)
    {
        std::cout<<filesNames.at(i)<<" ";
    }
}

void Manager::intro()
{
    system("cls");
    std::cout<<"Welcome in Notebook!"<<std::endl;
    std::cout<<"For help write \":help\""<<std::endl;
    std::cout<<std::endl;
    displayFiles();
    std::cout<<std::endl<<std::endl;
}


void Manager::display()
{

    intro();
        
    while(commandBuffer!=":end")
    {
        std::getline(std::cin,commandBuffer);

        if((commandBuffer.size()>=1)and(commandBuffer.at(0)!=':'))
        {
            std::cout<<"Command unrecognized. You can display list of commands with \":help\"."<<std::endl;
            continue;
        } 

        if(commandBuffer==":help") displayHelp();
        else if(commandBuffer!=":end")
        {
            std::string command=extractCommandNameFromCommand(commandBuffer);
            std::string fileName=extractFileNameFromCommand(commandBuffer, command);
            
            handleCommand(command,fileName);
        }   
    }
}




void Manager::handleCommand(std::string command, std::string fileName)
{
        if(command==":open")
        {
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else openFile(fileName);
        }
        else if(command==":create")
        {
            if(checkIfFileExist(fileName)==true)  std::cout<<"This file already exist. You can open it with \":open\" command."<<std::endl;
            else createFile(fileName);
        }
        else if(command==":clear")
        {
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file."<<std::endl;
            else clearFile(fileName);
        }
        else if(command==":write")
        {
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else writeToFile(fileName);
        }
        else if(command==":delete")
        {
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file."<<std::endl;
            else deleteFile(fileName);
        }
        else if(command==":edit")
        {
            if(checkIfFileExist(fileName)==false)  std::cout<<"There is no such file. You can create it with \":create\" command."<<std::endl;
            else editFile(fileName);
        }
        else if(commandBuffer!=":end")
        {
            std::cout<<"Command unrecognized. You can display list of commands with \":help\"."<<std::endl;
        }
}



std::string Manager::extractCommandNameFromCommand(std::string command)
{
    std::string answer="";
    int count=1;
    while(std::isalpha(command.at(count)))
    {
        answer.push_back(command.at(count));
       
        if(command.size()-1>count) ++count;
        else break;
        
    } 
    return (":"+answer);
}




std::string Manager::extractFileNameFromCommand(std::string wholeCommand, std::string command)
{
    std::string answer="";
    if((wholeCommand.size()-command.size())<1) return answer;
    for(size_t i=command.size()+1;i<wholeCommand.size();++i)
    {
        answer+=wholeCommand.at(i);
    }
    
    return answer;
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
    auto matchesFile=[fileName](Note note){return (note.getName()==fileName);};

    if(std::find_if(files.begin(),files.end(),matchesFile)==files.end()) return false;
    return true;
}

std::vector<Note>::iterator Manager::findFile(std::string fileName)
{
    auto matchesFile=[fileName](Note note){return (note.getName()==fileName);};

  return std::find_if(files.begin(),files.end(),matchesFile);
    
}



void Manager::openFile(std::string fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).openFile();
    
    intro();
}



void Manager::createFile(std::string fileName)
{
    Note temp(directory);
    temp.createFile(fileName);

    getFilesInDirectory();
    intro();
}


void Manager::clearFile(std::string fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).clearFile();
    
    intro();
}



void Manager::writeToFile(std::string fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).writeToFile();
    
    intro();
}



void Manager::deleteFile(std::string fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).deleteFile();

    getFilesInDirectory();
    intro();
}


void Manager::editFile(std::string fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).editFile();

    intro();

}
