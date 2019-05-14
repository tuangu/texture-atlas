/** \file App.cpp
 *  \brief App implementation
 */

#include <algorithm>
#include <exception>
#include "app.h"
#include "point.h"
#include "image.h"
#include "png_image.h"
#include "jpeg_image.h"
#include "texture.h"
#include "file_loader.h"

App::App(Report& reporter, const std::string& folderPath,
         const std::string& imageOutPath,
         const std::string& metaOutPath)
    : reporter{reporter},
      folderPath{folderPath},
      imageOutPath{imageOutPath},
      metaOutPath{metaOutPath},
      paths{} {

}

void App::run() {
    loadImage();
    long imageSize = findOptimalSize();
    if (imageSize < 0)
        throw std::runtime_error("error: image size should be positive");

    Point zero{};
    Texture texture{zero, imageSize, imageSize};
    addChild(&texture);
    texture.report(reporter);
    reporter.toFile(metaOutPath);
    texture.save(imageOutPath);
}

void App::loadImage() {
    FileLoader imageDir(folderPath);
    while (imageDir.next()) {
        paths.push_back(imageDir.get());
    }
}

bool App::addChild(Image* texture) {
    if (paths.empty())
        return false;

    Point origin{};
    for (const auto& path : paths) {
        auto [fullpath, ext] = path;
        if (ext == ".png") {
            if (!texture->addChild(std::make_shared<PngImage>(fullpath, origin))) {
                return false;
            }
        } else if (ext == ".jpeg") {
            if (!texture->addChild(std::make_shared<JpegImage>(fullpath, origin))) {
                return false;
            }
        }
    }

    return true;
}

long App::findOptimalSize(long distance) {
    if (distance < 0 || paths.empty())
        return -1;

    long imageSize = getMaxDimension();
    if (imageSize < 0)
        return -1;

    Point origin{};
    bool isDone = false;
    while (!isDone) {
        Texture texture{origin, imageSize, imageSize};
        if (addChild(&texture)) {
            imageSize = imageSize / 2;
            continue;
        } else {
            isDone = true;
        }
    }

    imageSize = imageSize * 2;
    for (;; imageSize -= distance) {
        Texture texture{origin, imageSize, imageSize};
        if (!addChild(&texture)) {
            break;
        }
    }

    return imageSize + distance;
}

long App::getMaxDimension() {
    if (paths.empty())
        return -1;

    long totalWidth = 0;
    long totalHeight = 0;
    Point zero{};

    for (const auto& path : paths) {
        auto [fullpath, ext] = path;
        if (ext ==  ".png") {
            PngImage pngImg(fullpath, zero);
            totalWidth += pngImg.metadata().width();
            totalHeight += pngImg.metadata().height();
        } else if (ext == ".jpeg") {
            JpegImage jpegImg(fullpath, zero);
            totalWidth += jpegImg.metadata().width();
            totalHeight += jpegImg.metadata().height();
        }
    }

    return totalWidth + totalHeight;
}

