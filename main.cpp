#include <cstddef>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include "file_loader.h"
#include "png_image.h"
#include "texture.h"

int main(int argc, char* argv[]) try {
    if (argc != 2) {
        throw std::invalid_argument("error: missing image folder paths");
    }
    
    FileLoader imageDir(argv[1]);
    Point origin;
    std::vector<std::string> paths;

    while (imageDir.next()) {
        paths.push_back(imageDir.get());
    }

    long dim = 4096;
    long distance = 32;
    bool isDone = false;
    while (!isDone) {
        Texture texture{origin, dim, dim};
        for (const auto& path : paths) {
            if (!texture.addChild(std::make_shared<PngImage>(path, origin))) {
                isDone = true;
                break;
            }
        }
        if (!isDone)
            dim = dim / 2;
    }

    long exactDim = dim * 2;
    isDone = false;
    for (; !isDone; exactDim -= distance) {
        Texture texture{origin, exactDim, exactDim};
        for (const auto& path : paths) {
            if (!texture.addChild(std::make_shared<PngImage>(path, origin))) {
                isDone = true;
                break;
            }
        }
    }
    
    exactDim += distance;
    std::cout << "Exact dim = " << exactDim << std::endl;
    Texture texture{origin, exactDim, exactDim};
    for (const auto& path : paths) {
        texture.addChild(std::make_shared<PngImage>(path, origin));
    }

    //texture.print_info(0);
    texture.save("final.png");

    // dlib::array2d<dlib::rgb_alpha_pixel> arr;
    // dlib::load_png(arr, "final.png");
    // dlib::image_window win;
    // win.set_image(arr);
    // std::cin.get();

    return 0;
} catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
}