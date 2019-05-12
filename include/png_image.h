/** \file png_image.h
 *  \brief Png image header
 */

#ifndef __PNG_IMAGE_H__
#define __PNG_IMAGE_H__

#include "image.h"

class PngImage : public Image {
public:
    explicit PngImage(const std::string& path, point_type& origin);

    meta_type metadata() override;
    
    void setOrigin(point_type& newOrigin) override;

    void save(image_type& texture) override;

    void save(const std::string& destPath) override;

    bool isEnoughSpace(long area) override;

    bool addChild(std::unique_ptr<Image> child) override;

private:
    point_type origin;
    meta_type meta;
};

#endif /* define __PNG_IMAGE_H__ */