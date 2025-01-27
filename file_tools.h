#pragma once

#include <vector>
#include <sstream> 
#include <my_boy.h>
#include <filesystem>



class file_tools
{
public:

    std::filesystem::path def_path;

    file_tools();

    std::string save_directory();
    std::string maps_directory();

    std::vector<std::string> getPlayerSaveFiles();
    void delete_save(std::string filename);
    std::string new_file_name();
    void save_boy(my_boy &boy, std::string path);
    int load_boy(my_boy& boy, std::string path);

    void get_data_ff(std::vector<std::vector<char>>& mapobj, std::string name);
};

