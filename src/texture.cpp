/** \file texture.cpp
 *  \brief Texture implementation
 */

#include <dlib/image_io.h>
#include <utility>
#include <iostream>

#include "texture.h"

Texture::Texture(point_type& origin, long width, long height)
    : Image{}, origin{origin}, width{width}, height{height}, textures{} {

}

Image::meta_type Texture::metadata() { 
    point_type extent{origin.X() + width - 1, origin.Y() + height - 1};
    meta_type meta{origin, extent};
    return meta;
}

void Texture::setOrigin(point_type& newOrigin) {
    this->origin = newOrigin;
}

void Texture::save(image_type& image) try {
    if (textures.empty()) 
        return;

    for (auto& texture : textures) {
        texture->save(image);
    }
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
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
    std::cerr << e.what() << std::endl;
}

bool Texture::addChild(std::shared_ptr<Image> child) {
    if (child == nullptr) 
        return false;

    meta_type childMeta = child->metadata();
    auto childWidth = childMeta.width();
    auto childHeight = childMeta.height();

    // The texture is now empty and the image can be fit into.
    // So we insert the image into the texture and split the texture
    // accordingly. There are 4 cases that may happen: 
    // (1) if the image size perfectly fit the texture (image width == texture
    //     width, image height == texture height), we simply place the image
    //     into the texture.
    // (2) if the image width equals to the texture width and the image height
    //     is smaller than the texture height, we insert the image and create 
    //     a new empty texture below the image.
    // (3) similarly, if the image height equals to the texture height and the
    //     image width is smaller than the texture width, we insert the image 
    //     and create a new empty texture to the right of the image.
    // (4) lastly, if the both dimensions of the image are less the dimensions
    //     of the texture, we insert the image in top-left of the texture and 
    //     create two new empty textures to the right and below the inserted image.
    if ((childWidth <= width) &&
        (childHeight <= height) &&
        textures.empty()) {
        child->setOrigin(origin);
        textures.push_back(child);

        if (childWidth == width && childHeight == height) {
            child->setOrigin(origin);
            textures.push_back(child);
        } else if (childWidth == width) {
            point_type newTextureOrigin{origin.X(), origin.Y() + childHeight};
            long newTextureHeight = height - childHeight;
            textures.emplace_back(std::make_shared<Texture>(
                newTextureOrigin, width, newTextureHeight)
            );
        } else if (childHeight == height) {
            point_type newTextureOrigin{origin.X() + childWidth, origin.Y()};
            long newTextureWidth = width - childWidth;
            textures.emplace_back(std::make_shared<Texture>(
                newTextureOrigin, newTextureWidth, height)
            );
        } else {
            point_type rightTextureOrigin{origin.X() + childWidth, origin.Y()};
            long rightTextureWidth = width - childWidth;
            long rightTextureHeight = childHeight;
            point_type bottomTextureOrigin{origin.X(), origin.Y() + childHeight};
            long bottomTextureWidth = width;
            long bottomTextureHeight = height - childHeight;

            auto rightTexture = std::make_shared<Texture>(
                rightTextureOrigin, rightTextureWidth, rightTextureHeight
            );
            auto bottomTexture = std::make_shared<Texture>(
                bottomTextureOrigin, bottomTextureWidth, bottomTextureHeight
            );

            // The smaller texture (in size) should be placed first.
            if (rightTexture->metadata().area() <
                bottomTexture->metadata().area()) {
                textures.push_back(rightTexture);
                textures.push_back(bottomTexture);
            } else {
                textures.push_back(bottomTexture);
                textures.push_back(rightTexture);
            }
        }
        
        return true;
    }

    // If the textures is not empty, we recursively find the empty texture 
    // that the image can be fit.
    for (auto& texture : textures) {
        if (texture->addChild(child)) 
            return true;
    }

    return false;
}

void Texture::setParent(std::shared_ptr<Image> parent) {
    this->parent = parent;
}

void Texture::report(Report& reporter) {
    if (textures.empty())
        return;

    for (auto& texture : textures) {
        texture->report(reporter);
    }
}

void Texture::print_info(int level) {
    for (auto& texture : textures) {
        auto pTexture = dynamic_cast<Texture*>(texture.get());
        if (pTexture) {
            for (int i = 0; i < level; i++)
                std::cout << "\t";
            std::cout << "texture " << " "
                      << texture->metadata().origin() << " " 
                      << texture->metadata().extent() << " "
                      << "w=" << texture->metadata().width() << " " 
                      << "h=" << texture->metadata().height() << std::endl;
            pTexture->print_info(level + 1);
        } else {
            for (int i = 0; i < level; i++)
                std::cout << "\t";
            std::cout << texture->metadata().getName() << " "
                      << texture->metadata().origin() << " " 
                      << texture->metadata().extent() << " "
                      << "w=" << texture->metadata().width() << " " 
                      << "h=" << texture->metadata().height() << std::endl;
        }
    }
}