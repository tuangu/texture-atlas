/** \file png_image.cpp
 *  \brief Png image implementation
 */

#include <exception>
#include <dlib/image_io.h>
#include "png_image.h"

PngImage::PngImage(const std::string& path, point_type& origin):
    Image{path},
    origin{origin},
    meta{} {
    image_type rawImage;
    dlib::load_png(rawImage, path);
    point_type extent{origin.X() + rawImage.nc() - 1, origin.Y() + rawImage.nr() - 1};
    meta = meta_type{origin, extent, path};
}

Image::meta_type PngImage::metadata() {
    return meta;
}

void PngImage::setOrigin(point_type& newOrigin) {
    long height = meta.height();
    long width = meta.width();
    point_type newExtent = meta.extent();

    newExtent.X(newOrigin.X() + width - 1);
    newExtent.Y(newOrigin.Y() + height - 1);
    meta.origin(newOrigin);
    meta.extent(newExtent);
}

void PngImage::save(image_type& texture) {
    image_type rawImage;
    long startCol = origin.X();
    long startRow = origin.Y();

    dlib::load_png(rawImage, path);

    if ((texture.nc() < (rawImage.nc() + startCol)) 
        || (texture.nr() < (rawImage.nr() + startRow))) {
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

bool PngImage::isEnoughSpace(long area) {
    return false;
}

bool PngImage::addChild(std::unique_ptr<Image> child) {
    return false;
}

