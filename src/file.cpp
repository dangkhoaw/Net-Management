#include "../include/file.hpp"
#include <filesystem>

namespace File
{
    bool open(std::fstream &file, const std::string &path, std::ios_base::openmode mode)
    {
        file.open(path, mode);
        return file.is_open();
    }

    bool close(std::fstream &file)
    {
        file.close();
        return !file.is_open();
    }

    bool write(std::fstream &file, const std::string &data)
    {
        if (file.is_open())
        {
            file << data << std::endl;
            return true;
        }
        return false;
    }

    bool read(std::fstream &file, std::string &data)
    {
        if (file.is_open())
        {
            if (!std::getline(file, data))
                return false;
            return true;
        }
        return false;
    }

    void remove(const std::string &path)
    {
        if (std::filesystem::exists(path))
            std::remove(path.c_str());
    }

    void rename(const std::string &oldPath, const std::string &newPath)
    {
        if (std::filesystem::exists(oldPath))
            std::rename(oldPath.c_str(), newPath.c_str());
    }
}