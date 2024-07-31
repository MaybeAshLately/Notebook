#include "Manager.h"

Manager::Manager()
{
    directory ="../../../Notes";
    for(const auto & i: std::filesystem::directory_iterator(directory))
    {
        filesNames.push_back(i.path().filename().string());
    }

    commandBuffer="";
}

void Manager::display()
{
    system("cls");
    std::cout<<"Welcome in Notebook!"<<std::endl;
    std::cout<<"For help write \"help\""<<std::endl;
    std::cout<<std::endl;
    for(size_t i=0;i<filesNames.size();++i)
    {
        std::cout<<filesNames.at(i)<<" ";
    }
    std::cout<<std::endl<<std::endl;
  
        
        
    while(commandBuffer!="end")
    {
        std::getline(std::cin,commandBuffer);
        if(commandBuffer=="help") displayHelp();
        else if((commandBuffer.size()>=4)and(commandBuffer.compare(0,3,"open")))
        {
            if(checkIfFileExist(commandBuffer)==false)  std::cout<<"There is no such file. You can create it with \"create\" command."<<std::endl;
            else openFile(commandBuffer);
        }
    }
}



void Manager::displayHelp()
{
    constexpr int size=20;
    system("cls");
    std::cout<<std::left;
    std::cout<<std::setw(size)<<"Create file.txt"<<"Creates file.txt (if it does not exist already)"<<std::endl;
    std::cout<<std::setw(size)<<"End"<<"Ends program"<<std::endl;
    std::cout<<std::setw(size)<<"Exit"<<"Exits manual/file (in modify mode without saving changes)"<<std::endl;
    std::cout<<std::setw(size)<<"Help"<<"Displays manual"<<std::endl;
    std::cout<<std::setw(size)<<"Modify file.txt"<<"Opens file.txt in modify mode (if it have not existed creates it)"<<std::endl;
    std::cout<<std::setw(size)<<"Open file.txt"<<"Opens file.txt in read only mode (if it exists)"<<std::endl;
    std::cout<<std::setw(size)<<"Save"<<"Save changes in current file and exits"<<std::endl;
    std::cout<<std::endl;

    while(commandBuffer!="exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    display();

}

bool Manager::checkIfFileExist(std::string command)
{
    command.erase(command.begin(),command.begin()+5);
    std::string fileName=command;
    
    if(std::find(filesNames.begin(),filesNames.end(),fileName)==filesNames.end()) return false;
    return true;
}


void Manager::openFile(std::string command)
{
    command.erase(command.begin(),command.begin()+5);
    std::string fileName=command;
    fileName="../../../Notes/"+fileName;


    std::ifstream file(fileName);
    if(!file) std::cout<<"Error, cannot open file"<<std::endl;
    else
    {
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;   
    }


    
    while(commandBuffer!="exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    display();
}