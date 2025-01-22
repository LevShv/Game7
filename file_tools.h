#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream> 
#include <filesystem>
#include <vector>

class file_tools
{
public:
    std::vector<std::string> getPlayerSaveFiles(std::string& directory);
    void delete_save(std::string filename);
    std::string new_file_name();
};

