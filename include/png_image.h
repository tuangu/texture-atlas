/** \file png_image.h
 *  \brief Png image header
 */

#ifndef __PNG_IMAGE_H__
#define __PNG_IMAGE_H__

#include "image.h"

class PngImage : public Image {
public:
    PngImage(const std::string& path, point_type& origin);

    meta_type metadata() override;
    
    void setOrigin(point_type& newOrigin) override;

    void save(image_type& texture) override;

    void save(const std::string& destPath) override;

    bool addChild(std::shared_ptr<Image> child) override;

    void setParent(std::shared_ptr<Image> parent) override;

    void report(Report& reporter) override;

private:
    point_type origin;
    long width;
    long height;
    std::weak_ptr<Image> parent;
};

#endif /* define __PNG_IMAGE_H__ */