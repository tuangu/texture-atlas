/** \file file_loader.h
 *  \brief File loader header
 */

#ifndef __FILE_LOADER_H__
#define __FILE_LOADER_H__

#include <string>
#include <vector>
#include <utility>
#include <filesystem>

namespace fs = std::filesystem;

class FileLoader {
public:
    FileLoader(const std::string& folderPath);

    void reset(const std::string& newPath);

    bool next();

    const std::pair<std::string, std::string>& get() const;

private:
    void load();

    bool filter(const fs::path& path) const;

private:
    std::string folderPath;
    bool isLoaded;
    std::vector<std::pair<std::string, std::string>> imagePaths;
    std::vector<std::pair<std::string, std::string>>::const_iterator iterator;
    std::pair<std::string, std::string> currentFilePath;
};

#endif /* define __FILE_LOADER_H__ */