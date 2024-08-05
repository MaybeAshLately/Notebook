#include "Note.h"

void Note::openFile()
{
    system("cls");
    std::string fullDirectory=directory+fileName;
    
    std::ifstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot open file. Type \":exit\" to abort."<<std::endl;
    else
    {
        std::cout<<"File opened sucessfully! Type \":exit\" to exit."<<std::endl;
        std::cout<<"------------------------------------------------"<<std::endl<<std::endl;
        std::string line;
        while(std::getline(file,line)) std::cout<<line<<std::endl;  
        std::cout<<std::endl; 
    }


    std::string commandBuffer;
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    file.close();
    
}

void Note::createFile(std::string newfileName)
{
    fileName=newfileName;
    std::string fullDirectory=directory+fileName;

    std::ofstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot create file. Type \":exit\" to abort."<<std::endl;
    else
    {
        system("cls");
        std::cout<<"New file was created succesfully!"<<std::endl;
        std::cout<<"You can write to file. Type \":exit\" to save and exit the file"<<std::endl;
        std::cout<<"---------------------------------------------------------------"<<std::endl;
        std::cout<<std::endl;
    }

    std::string commandBuffer;
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
        if(commandBuffer!=":exit")file<<commandBuffer<<std::endl;
    }
    file.close();   
}


void Note::clearFile()
{
    std::string fullDirectory=directory+fileName;

    std::ofstream file(fullDirectory);
    if(!file) std::cout<<"Error, cannot clear file. Type \":exit\" to go back"<<std::endl;
    else 
    {
        std::cout<<"File cleared sucessfully!. Type \":exit\" to go back"<<std::endl;
    }

    std::string commandBuffer;
    while(commandBuffer!=":exit")
    {
        std::getline(std::cin,commandBuffer);
    }
    
    file.close();
}



void Note::writeToFile()
{
    system("cls");

    std::string fullDirectory=directory+fileName;

    std::fstream file(fullDirectory,std::ios::in);
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
    std::string commandBuffer;
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

    
}



void Note::deleteFile()
{
    system("cls");
    std::cout<<"Are you sure you want to delete "<<fileName<<" (:yes/:no)?"<<std::endl;
    
    std::string commandBuffer="";
    while((commandBuffer!=":no")and(commandBuffer!=":yes"))
    {
        std::getline(std::cin,commandBuffer);
    }

    if(commandBuffer==":yes")
    {
      std::string fullDirectory=directory+fileName;
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
    
}


void Note::editFile()
{
    system("cls");

    std::string fullDirectory=directory+fileName;

    std::string commandBuffer;
    std::vector<std::string> fileLinesBuffor;
    std::fstream file(fullDirectory,std::ios::in);
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
                fileLinesBuffor.at(location-1)=commandBuffer;
          

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
            std::ofstream file(fullDirectory);
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
    
}


bool Note::isNumber(std::string txt)
{
    for(size_t i=0;i<txt.size();++i)
    {
        if(std::isdigit(txt.at(i))==false) return false;
    }
    return true;
}