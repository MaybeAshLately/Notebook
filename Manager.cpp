#include "Manager.h"

Manager::Manager(): directory("../../../Notes/")
{
    getFilesInDirectory();
    commandBuffer="";
}

void Manager::getFilesInDirectory()
{
    files.clear();
    for(const auto & i: std::filesystem::directory_iterator(directory))
    {
        std::string fileBuffer= i.path().filename().string();
        files.push_back(Note(directory,fileBuffer));
    }
}

void Manager::displayFiles() const
{
    for(size_t i=0;i<files.size();++i)
    {
        std::cout<<files.at(i).getName()<<" ";
    }
}

void Manager::intro() const
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
        if(commandBuffer.size()<1) continue;
        if(commandBuffer.at(0)!=':')
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

std::string Manager::extractCommandNameFromCommand(const std::string& command) const
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

std::string Manager::extractFileNameFromCommand(const std::string& wholeCommand,const std::string& command) const
{
    std::string answer="";
    if((wholeCommand.size()-command.size())<1) return answer;
    for(size_t i=command.size()+1;i<wholeCommand.size();++i)
    {
        answer+=wholeCommand.at(i);
    }
    return answer;
}



void Manager::handleCommand(const std::string& command,const std::string& fileName)
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

bool Manager::checkIfFileExist(const std::string& fileName) const
{
    auto matchesFile=[fileName](Note note){return (note.getName()==fileName);};

    if(std::find_if(files.begin(),files.end(),matchesFile)==files.end()) return false;
    return true;
}

void Manager::displayHelp()
{
    constexpr int size=20;
    system("cls");
    std::cout<<std::left;
    std::cout<<std::setw(size)<<"This program uses following commands (attention, certain commands are available only in certain modules of program)"<<std::endl;
    std::cout<<std::setw(size)<<":ack"<<"Acknowledgement"<<std::endl;
    std::cout<<std::setw(size)<<":create file.txt"<<"Creates file.txt (if it does not already exist)"<<std::endl;
    std::cout<<std::setw(size)<<":delete file.txt"<<"Deletes file.txt (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<":edit file.txt"<<"Opens file.txt in edit mode. You can modify the content with \":edit\", \":erase\" and \":insert\" commands"<<std::endl;
    std::cout<<std::setw(size)<<":edit line_nr"<<"Allows editing of the specified line"<<std::endl;
    std::cout<<std::setw(size)<<":end"<<"Ends program"<<std::endl;
    std::cout<<std::setw(size)<<":erase line_nr"<<"Erase the specified line"<<std::endl;
    std::cout<<std::setw(size)<<":exit"<<"Exits manual/file (in modify mode without saving changes)"<<std::endl;
    std::cout<<std::setw(size)<<":help"<<"Displays manual"<<std::endl;
    std::cout<<std::setw(size)<<":insert line_nr"<<"Allows insertion of line(s) after the specified line"<<std::endl;
    std::cout<<std::setw(size)<<":ok"<<"Acknowledgement"<<std::endl;
    std::cout<<std::setw(size)<<":open file.txt"<<"Opens file.txt in read only mode (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<":save"<<"Saves changes in the current file"<<std::endl;
    std::cout<<std::setw(size)<<":write file.txt"<<"Opens file.txt in write mode. You can write new content at the end of file."<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::setw(size)<<"Please make sure that you remember the key used to encrypt your file. If you use the wrong key, the content of file will be unrecoverable. You can use the same or different key in different files. After decrypting a file, you can encrypt it with different key."<<std::endl;

    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    intro();
}

std::vector<Note>::iterator Manager::findFile(const std::string& fileName)
{
    auto matchesFile=[fileName](Note note){return (note.getName()==fileName);};

  return std::find_if(files.begin(),files.end(),matchesFile);
    
}


void Manager::openFile(const std::string& fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).openFile();
         
    intro();
}



void Manager::createFile(const std::string& fileName)
{
    Note temp(directory);
    temp.createFile(fileName);

    getFilesInDirectory();
    intro();
}


void Manager::clearFile(const std::string& fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).clearFile();
    
    intro();
}



void Manager::writeToFile(const std::string& fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).writeToFile();
    
    intro();
}



void Manager::deleteFile(const std::string& fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).deleteFile();

    getFilesInDirectory();
    intro();
}


void Manager::editFile(const std::string& fileName)
{
    auto it=findFile(fileName);
    if(it!=files.end()) (*it).editFile();

    intro();
}
