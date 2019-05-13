/** \file report.h
 *  \brief Report header
 */

#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include "image.h"
#include "rect.h"

class Image;

class Report{
public:
    Report();

    void visitImage(Image*);

    void toFile(const std::string& filename);

private:
    std::string shortenPath(std::string filename);

private:
    std::vector<Rect> metas;
};

#endif /* define __REPORT_H__ */