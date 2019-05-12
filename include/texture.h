/** \file texture.h
 *  \brief Texture header
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <vector>
#include "image.h"

class Texture : public Image {
public:
    Texture(point_type& origin, long width, long height);

    meta_type metadata() override;
    
    void setOrigin(point_type& newOrigin) override;

    void save(image_type& image) override;

    void save(const std::string& destPath) override;

    bool isEnoughSpace(long area) override;

    bool addChild(std::unique_ptr<Image> child) override;

    std::size_t get_textures_size() {
        return textures.size();
    };

private:
    point_type origin;
    long width;
    long height;
    long freeArea;
    meta_type meta;
    std::vector<std::unique_ptr<Image>> textures;
};

#endif /* define __TEXTURE_H__ */