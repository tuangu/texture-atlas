/** \file png_image.cpp
 *  \brief Png image implementation
 */

#include <dlib/image_io.h>
#include <exception>

#include "png_image.h"

PngImage::PngImage(const std::string& path, point_type& origin)
    : Image{path}, origin{origin}, parent{} {
    image_type rawImage;
    dlib::load_png(rawImage, path);
    width = rawImage.nc();
    height = rawImage.nr();
}

Image::meta_type PngImage::metadata() { 
    point_type extent{origin.X() + width - 1, origin.Y() + height - 1};
    meta_type meta{origin, extent, path};
    return meta;
}

void PngImage::setOrigin(point_type& newOrigin) {
    origin = newOrigin;
}

void PngImage::save(image_type& texture) {
    image_type rawImage;
    long startCol = origin.X();
    long startRow = origin.Y();

    dlib::load_png(rawImage, path);

    if (rawImage.nc() != width ||
        rawImage.nr() != height) {
        throw std::runtime_error("error: image dimension should be matched with loaded data");
    }

    if ((texture.nc() < (rawImage.nc() + startCol - 1)) ||
        (texture.nr() < (rawImage.nr() + startRow - 1))) {
        throw std::out_of_range("error: out of range");
    }

    for (long row = 0; row < rawImage.nr(); row++) {
        for (long col = 0; col < rawImage.nc(); col++) {
            texture[row + startRow][col + startCol] = rawImage[row][col];
        }
    }
}

void PngImage::save(const std::string& destPath) {
    image_type rawImage;
    dlib::load_png(rawImage, path);
    dlib::save_png(rawImage, destPath);
}

bool PngImage::addChild(std::shared_ptr<Image> child) { 
    return false; 
}

void PngImage::setParent(std::shared_ptr<Image> parent) {
    this->parent = parent;
}

void PngImage::report(Report& reporter) {
    reporter.visitImage(this);
}
