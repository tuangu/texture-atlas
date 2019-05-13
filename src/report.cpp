/** \file Report.cpp
 *  \brief Report implementation
 */

#include <filesystem>
#include <fstream>
#include <iostream>
#include "report.h"

namespace fs = std::filesystem;

Report::Report()
    : metas{} {

}

void Report::visitImage(Image* image) {
    metas.push_back(image->metadata());
}

void Report::toFile(const std::string& filename) {
    std::ofstream out{filename};
    out << "filename,origin,width,height" << std::endl;

    for (const auto& meta : metas) {
        auto imagePath = shortenPath(meta.getName());

        out << imagePath << ","
            << meta.origin() << ","
            << meta.width() << ","
            << meta.height() << std::endl;
    }
    out.close();
}

std::string Report::shortenPath(std::string filename) {
    fs::path path{filename};

    return path.filename();
}