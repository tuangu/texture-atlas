/** \file jpeg_image.h
 *  \brief Jpeg image header
 */

#ifndef __JPEG_IMAGE_H__
#define __JPEG_IMAGE_H__

#include "image.h"

class JpegImage : public Image {
public:
    JpegImage(const std::string& path, point_type& origin);

    meta_type metadata() override;
    
    void setOrigin(point_type& newOrigin) override;

    void save(image_type& texture) override;

    void save(const std::string& destPath) override;

    bool addChild(std::shared_ptr<Image> child) override;

    void setParent(std::shared_ptr<Image> parent) override;

private:
    point_type origin;
    long width;
    long height;
    std::weak_ptr<Image> parent;
};

#endif /* define __JPEG_IMAGE_H__ */