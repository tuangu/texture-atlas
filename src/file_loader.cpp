/** \file file_loader.cpp
 *  \brief File loader implementation
 */

#include "file_loader.h"
#include <filesystem>

namespace fs = std::filesystem;

FileLoader::FileLoader(const std::string& folderPath)
    : folderPath{folderPath},
      isLoaded(false),
      imagePaths{},
      iterator{},
      currentFilePath{} {}

void FileLoader::reset(const std::string& newPath) {
    folderPath = newPath;
    isLoaded = false;
    imagePaths.clear();
}

bool FileLoader::next() {
    if (!isLoaded) load();

    if (iterator != imagePaths.cend()) {
        currentFilePath = *iterator;
        ++iterator;
        return true;
    }

    return false;
}

const std::pair<std::string, std::string>& FileLoader::get() const { 
    return currentFilePath; 
}

void FileLoader::load() {
    fs::path path(folderPath);

    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            auto filename = entry.path().filename();
            if (filter(filename)) {
                auto fullPath = path/filename;
                auto ext = filename.extension();
                imagePaths.push_back(std::make_pair<std::string, std::string>(
                    fullPath.string(), ext.string()
                ));
            }
        }

        isLoaded = true;
        iterator = imagePaths.cbegin();
    }
}

bool FileLoader::filter(const fs::path& path) const {
    const fs::path JPEG(".jpeg");
    const fs::path JPG(".jpg");
    const fs::path PNG(".png");

    auto ext = path.extension();
    if (ext == JPEG || ext == PNG || ext == JPG) 
        return true;

    return false;
}