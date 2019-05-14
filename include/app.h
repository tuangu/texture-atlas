/** \file app.h
 *  \brief App header
 */

#ifndef __APP_H__
#define __APP_H__

#include <string>
#include <vector>
#include <utility>
#include "report.h"

class App {
public:
    App(Report& reporter, 
        const std::string& folderPath, 
        const std::string& imageOutPath = "final.png",
        const std::string& metaOutPath = "metadata.txt");

    void run();

private:
    void loadImage();

    bool addChild(Image*);

    long findOptimalSize(long distance = 128);

    long getMaxDimension();

private:
    Report reporter;
    std::string folderPath;
    std::string imageOutPath;
    std::string metaOutPath;
    std::vector<std::pair<std::string, std::string>> paths;
};

#endif /* define __APP_H__ */