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
    }

}