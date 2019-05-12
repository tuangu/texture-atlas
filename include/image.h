/** \file image.h
 *  \brief Image header
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <memory>
#include <string>
#include <dlib/array2d.h>
#include <dlib/pixel.h>
#include "rect.h"
#include "point.h"

class Image {
public:
    using image_type = dlib::array2d<dlib::rgb_alpha_pixel>;
    using point_type = Point;
    using meta_type = Rect;

    virtual ~Image() {};

    virtual meta_type metadata() = 0;

    virtual void setOrigin(point_type&) = 0;

    virtual void save(image_type&) = 0;

    virtual void save(const std::string&) = 0;

    virtual bool isEnoughSpace(long) = 0;

    virtual bool addChild(std::unique_ptr<Image>) = 0;

protected:
    Image(const std::string& path = "") : path{path} {};

protected:
    std::string path;
};

#endif /* define __IMAGE_H__ */