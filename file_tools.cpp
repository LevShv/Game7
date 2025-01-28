#include "file_tools.h"

#include <chrono>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

file_tools::file_tools() {

    def_path = fs::current_path();

}

std::string file_tools::save_directory() {


    fs::path saveDirectory = def_path / "Saves";

    if (!fs::exists(saveDirectory)) {
        fs::create_directory(saveDirectory);
    }

    return saveDirectory.string();
}

std::string file_tools::maps_directory()
{
    return (def_path / "Maps").string();
}

std::vector<std::string> file_tools::getPlayerSaveFiles()
{
    std::vector<std::string> saveFiles;

    for (auto& entry : fs::directory_iterator(save_directory()))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            if (filename.find("player_save_") == 0) {
                saveFiles.push_back(filename);
            }
        }
    }

    return saveFiles;
}

void file_tools::delete_save(std::string filename)
{

    if (fs::exists(filename))
        fs::remove(filename);
}

std::string file_tools::new_file_name()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm tm;

    localtime_s(&tm, &now_time_t);

    std::ostringstream filename_stream;

    filename_stream << "player_save_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".txt";
    fs::path default_path = save_directory();
    return (default_path / filename_stream.str()).string();
}

void file_tools::save_boy(my_boy &boy, std::string path) {

    if (path != "0") {

        std::ofstream file(path);
        if (!file.is_open()) {

            return;
        }

        file << "level: " << boy.where << "\n";

        file << "hp: " << boy.hp << "\n";

        file << "x: " << boy.x << "\n";
        file << "y: " << boy.y << "\n";

        file << "invent_size: " << boy.invent.size() << "\n";

        for (const auto& item : boy.invent) {
            file << item.name << " " << item.icon << " " << item.count << " " << item.color << " " << item.usage << "\n";
        }

        file.close();
    }
}

int file_tools::load_boy(my_boy& boy, std::string path)
{


    if (path == "0") {
        return -1; // Неверный путь
    }
    fs::path dir = save_directory();

    std::ifstream file(dir / path);

    if (!file.is_open()) {
        return -2; // Файл не удалось открыть
    }
    boy.invent.clear();
    std::string line;

    while (std::getline(file, line)) {

        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "level:") {
            iss >> boy.where;
        }
        else if (key == "hp:") {
            iss >> boy.hp;
        }
        else if (key == "x:") {
            iss >> boy.x;
        }
        else if (key == "y:") {
            iss >> boy.y;
        }
        else if (key == "invent_size:") {
            int invent_size;
            iss >> invent_size;
        /*    boy.invent.resize(invent_size);*/ // Изменяем размер вектора
        }
        else {
            // Чтение данных предмета
            invent_thing item;
            iss >> item.name >> item.icon >> item.count >> item.color >> item.usage;
            boy.invent.push_back(item);
        }
    }

    file.close();

    boy.x++;
    boy.loaded_boy = true;

    return boy.where; // Успешное чтение
}

void file_tools::get_data_ff(std::vector<std::vector<char>>& mapobj, std::string name)
{

    fs::path def = maps_directory();
    std::ifstream inputFile(def / name);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row;

        for (char ch : line) {
            row.push_back(ch);
        }
        mapobj.push_back(row);
    }
    inputFile.close();
}

