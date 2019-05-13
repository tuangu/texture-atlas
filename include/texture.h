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

    bool addChild(std::shared_ptr<Image> child) override;

    void setParent(std::shared_ptr<Image> parent) override;

    void print_info(int level);

private:
    point_type origin;
    long width;
    long height;
    std::vector<std::shared_ptr<Image>> textures;
    std::weak_ptr<Image> parent;
};

#endif /* define __TEXTURE_H__ */