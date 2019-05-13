#include "catch2/catch.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "file_loader.h"

namespace fs = std::filesystem;

TEST_CASE("FileLoader functionalities", "[file_loader]") {
    std::string folder_path = "test_file_loader";
    std::string jpeg_1 = folder_path + "/" + "img_1.jpeg";
    std::string png_1 = folder_path + "/" + "img_2.png";
    std::string other = folder_path + "/" + "other.txt";
    fs::create_directories(folder_path);
    std::ofstream _jpeg_1(jpeg_1);
    std::ofstream _png_1(png_1);
    std::ofstream _other(other);

    FileLoader img_dir(folder_path);

    SECTION("FileLoader can return filtered filepaths") {
        std::vector<std::string> paths{};
        while (img_dir.next()) {
            paths.push_back(img_dir.get());
        }

        REQUIRE(paths.size() == 2);
        
        bool hasExpectedPaths = true;
        for (const auto& path : paths) {
            if (path != jpeg_1 && path != png_1)
                hasExpectedPaths = false;
        }
        REQUIRE(hasExpectedPaths);
    }

    fs::remove_all(folder_path);
}