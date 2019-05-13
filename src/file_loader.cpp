/** \file file_loader.cpp
 *  \brief File loader implementation
 */

#include <filesystem>
#include "file_loader.h"

namespace fs = std::filesystem;

FileLoader::FileLoader(const std::string& folderPath):
    folderPath{folderPath},
    isLoaded(false),
    imagePaths{},
    iterator{},
    currentFilePath{} {

}

void FileLoader::reset(const std::string& newPath) {
    folderPath = newPath;
    isLoaded = false;
    imagePaths.clear();
}

bool FileLoader::next() {
    if (!isLoaded)
        load();

    if (iterator != imagePaths.cend()) {
        currentFilePath = *iterator;
        ++iterator;
        return true;
    }
    
    return false;
}

std::string const& FileLoader::get() const {
    return currentFilePath;
}

void FileLoader::load() {
    fs::path path(folderPath);

    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            auto filename = entry.path().filename();
            if (filter(filename)) {
                imagePaths.push_back(filename.string());
            }
        }
        
        isLoaded = true;
        iterator = imagePaths.cbegin();
    }
}

bool FileLoader::filter(fs::path path) {
    fs::path JPEG(".jpeg");
    fs::path PNG(".png");

    auto ext = path.extension();
    if (ext == JPEG || ext == PNG)
        return true;
    
    return false;
}