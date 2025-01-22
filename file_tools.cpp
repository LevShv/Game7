#include "file_tools.h"


std::vector<std::string> file_tools::getPlayerSaveFiles(std::string& directory)
{
    std::vector<std::string> saveFiles;
    namespace fs = std::filesystem;

    for (auto& entry : fs::directory_iterator(directory))
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
    namespace fs = std::filesystem;

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

    return filename_stream.str();
}
