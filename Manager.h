#ifndef MANAGER_H
#define MANAGER_H
#include "Note.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>


class Manager
{
    std::string directory;
    std::vector<std::string> filesNames;
    std::string commandBuffer;
    public:
    Manager();

    void display();
};

#endif