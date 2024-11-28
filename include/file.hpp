#ifndef FILE_UTILS
#define FILE_UTILS 1

#include <fstream>

namespace File
{
    bool open(std::fstream &file, const std::string &path, std::ios_base::openmode mode);
    bool close(std::fstream &file);
    bool write(std::fstream &file, const std::string &data);
    bool read(std::fstream &file, std::string &data);
    void remove(const std::string &path);
    void rename(const std::string &oldPath, const std::string &newPath);
}

#endif