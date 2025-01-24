#pragma once

#include <vector>
#include <sstream> 

class file_tools
{
public:
    std::vector<std::string> getPlayerSaveFiles(std::string& directory);
    void delete_save(std::string filename);
    std::string new_file_name();
    void get_data_ff(std::vector<std::vector<char>>& mapobj, std::string name);
};

