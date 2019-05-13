/** \file jpeg_image.cpp
 *  \brief Jpeg image implementation
 */

#include <dlib/image_io.h>
#include <exception>

#include "jpeg_image.h"

JpegImage::JpegImage(const std::string& path, point_type& origin)
    : Image{path}, origin{origin}, parent{} {
    image_type rawImage;
    dlib::load_jpeg(rawImage, path);
    width = rawImage.nc();
    height = rawImage.nr();
}

Image::meta_type JpegImage::metadata() { 
    point_type extent{origin.X() + width - 1, origin.Y() + height - 1};
    meta_type meta{origin, extent, path};
    return meta;
}

void JpegImage::setOrigin(point_type& newOrigin) {
    origin = newOrigin;
}

void JpegImage::save(image_type& texture) {
    image_type rawImage;
    long startCol = origin.X();
    long startRow = origin.Y();

    dlib::load_jpeg(rawImage, path);

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

void JpegImage::save(const std::string& destPath) {
    image_type rawImage;
    dlib::load_jpeg(rawImage, path);
    dlib::save_jpeg(rawImage, destPath);
}

bool JpegImage::addChild(std::shared_ptr<Image> child) { 
    return false; 
}

void JpegImage::setParent(std::shared_ptr<Image> parent) {
    this->parent = parent;
}

void JpegImage::report(Report& reporter) {
    reporter.visitImage(this);
}