#include <cstddef>
#include <exception>
#include <string>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <algorithm>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include "png_image.h"
#include "texture.h"
#include "file_loader.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) try {
    // if (argc < 2) 
    //     throw std::invalid_argument("error: missing image paths");

    // Point origin{0, 0};
    // Point middle{500, 500};
    // Texture atlas{origin, 389, 1024};
    // // atlas.addChild(std::make_unique<PngImage>(argv[1], origin));
    // // atlas.addChild(std::make_unique<PngImage>(argv[2], middle));

    // for (int i = 1; i < argc; i++) {
    //     // dlib::array2d<dlib::rgb_alpha_pixel> _img;
    //     // dlib::load_png(_img, argv[i]);
    //     // dlib::image_window _win;
    //     // _win.set_background_color(255, 255, 255);
    //     // _win.set_image(_img);
    //     bool is_success = atlas.addChild(std::make_unique<PngImage>(argv[i], origin));
    // }

    // atlas.save("final.png");
    // atlas.print_info();

    // dlib::array2d<dlib::rgb_alpha_pixel> img;
    // dlib::load_png(img, "final.png");
    // dlib::image_window win;
    // win.set_background_color(255, 255, 255);
    // win.set_image(img);
    // std::cin.get();

    std::string folder_path = "file_loader";
    std::string jpeg_1 = folder_path + "/img_1.jpeg";
    std::string png_1 = folder_path + "/img_2.png";
    std::string other = folder_path + "/other.txt";
    fs::create_directories(folder_path);
    std::ofstream _jpeg_1(jpeg_1);
    std::ofstream _png_1(png_1);
    std::ofstream _other(other);

    FileLoader img_dir(folder_path);
    while (img_dir.next())
        std::cout << img_dir.get() << std::endl;

    return 0;
} catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
}