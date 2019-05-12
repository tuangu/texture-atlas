/** \file texture.cpp
 *  \brief Texture implementation
 */

#include <utility>
#include <dlib/image_io.h>
#include "texture.h"

Texture::Texture(point_type& origin, long width, long height):
    Image{},
    origin{origin},
    width{width},
    height{height},
    freeArea{width*height},
    meta{origin, point_type{width - 1, height - 1}},
    textures{} {
    
}

Image::meta_type Texture::metadata() {
    return meta;
}

void Texture::setOrigin(point_type& newOrigin) {
    point_type newExtent = meta.extent();

    newExtent.X(newOrigin.X() + width - 1);
    newExtent.Y(newOrigin.Y() + height - 1);
    meta.origin(newOrigin);
    meta.extent(newExtent);
}

void Texture::save(image_type& image) try {
    if (textures.empty())
        return;

    for (auto& texture : textures) {
        texture->save(image);
    }
} catch (std::exception& e) {
    throw e;
}

void Texture::save(const std::string& destPath) try {
    image_type image{height, width};

    if (textures.empty())
        return;

    for (auto& texture : textures) {
        texture->save(image);
    }
    dlib::save_png(image, destPath);
} catch (std::exception& e) {
    throw e;
}

bool Texture::isEnoughSpace(long area) {
    return area <= freeArea;
}

bool Texture::addChild(std::unique_ptr<Image> child) {
    if (child == nullptr)
        return false;

    meta_type childMeta = child->metadata();
    auto childArea = childMeta.area();
    auto childWidth = childMeta.width();
    auto childHeight = childMeta.height();
    
    if (!isEnoughSpace(childArea))
        return false;

    // The texture is now empty and the image can be fit into.
    // So we insert the image into the texture and split the texture accordingly.
    // There are 4 cases that may happen:
    // (1) if the image size perfectly fit the texture (image width == texture 
    //     width, image height == texture height), we simply place the image 
    //     into the texture.
    // (2) if the image width equals to the texture width and the image height is 
    //     smaller than the texture height, we insert the image and create a new
    //     empty texture below the image.
    // (3) similarly, if the image height equals to the texture height and the image
    //     width is smaller than the texture width, we insert the image and create a
    //     new empty texture to the right of the image.
    // (4) lastly, if the both dimensions of the image are less the dimensions of the
    //     texture, we insert the image in top-left of the texture and create two
    //     new empty textures to the right and below the inserted image.
    if (textures.empty()) {
        child->setOrigin(origin);
        textures.push_back(std::move(child));
        
        if (childWidth == width && childHeight == height) {
            freeArea = 0;
        } else if (childWidth == width) {
            point_type newTextureOrigin{origin.X(), origin.Y() + childHeight};
            long newTextureHeight = height - childHeight;
            textures.emplace_back(
                std::make_unique<Texture>(newTextureOrigin, width, newTextureHeight)
            );
            freeArea = newTextureHeight * width;
        } else if (childHeight == height) {
            point_type newTextureOrigin{origin.X() + childWidth, origin.Y()};
            long newTextureWidth = width - childWidth;
            textures.emplace_back(
                std::make_unique<Texture>(newTextureOrigin, newTextureWidth, height)
            );
            freeArea = height * newTextureWidth;
        } else {
            point_type rightTextureOrigin{origin.X() + childWidth, origin.Y()};
            long rightTextureWidth = width - childWidth;
            long rightTextureHeight = childHeight;
            point_type bottomTextureOrigin{origin.X(), origin.Y() + childHeight};
            long bottomTextureWidth = width;
            long bottomTextureHeight = height - childHeight;
            auto rightTexture = std::make_unique<Texture>(
                rightTextureOrigin, rightTextureWidth, rightTextureHeight
            );
            auto bottomTexture = std::make_unique<Texture>(
                bottomTextureOrigin, bottomTextureWidth, bottomTextureHeight
            );

            // The smaller texture (in size) should be placed first.
            if (rightTexture->metadata().area() < bottomTexture->metadata().area()) {
                textures.push_back(std::move(rightTexture));
                textures.push_back(std::move(bottomTexture));
            } else {
                textures.push_back(std::move(bottomTexture));
                textures.push_back(std::move(rightTexture));
            }
            freeArea = rightTextureWidth * rightTextureHeight +
                       bottomTextureWidth * bottomTextureHeight;
        }
        return true;
    }

    // Else, we recursively find the empty texture that the image can be fit.
    for (auto& texture : textures) {
        if (texture->addChild(std::move(child)))
            return true;
    }

    return false;
}